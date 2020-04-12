#!/usr/bin/env python

# Select Theano as backend for Keras
from os import environ
environ['KERAS_BACKEND'] = 'theano'

# Set architecture of system (AVX instruction set is not supported on SWAN)
environ['THEANO_FLAGS'] = 'gcc.cxxflags=-march=corei7'

from ROOT import TMVA, TFile, TTree, TCut
from subprocess import call
from os.path import isfile

from keras import backend as K
import theano as T

from keras.models import Sequential, Model
from keras.layers.core import Dense
from keras.optimizers import Adam
from keras.layers.advanced_activations import LeakyReLU
from keras.layers.recurrent import LSTM, SimpleRNN
from keras.layers import Dense, Activation, BatchNormalization, Dropout, Input, Lambda
from keras.layers import Conv2D, MaxPooling2D, Flatten, Reshape, UpSampling2D, merge

import os
import sys
import numpy as np

from keras.optimizers import SGD
from keras.datasets import mnist
#from keras.regularizers import l1_l2

from ROOT import TFile, TTree
from array import array

def ResNetBlock(xIn):

  x = Dense( 1024 )( xIn )
  x = BatchNormalization(mode=2)(x)
  x = Activation( 'relu' )( x )
  x = Dropout( 0.25 )(x)

  x = Dense( 1024 )( x )
  x = BatchNormalization(mode=2)(x)
  x = Activation( 'relu' )( x )
  x = Dropout( 0.25 )(x)

  #x2 = Conv2D( 32, 2, 2, border_mode='same' )( x1 )
  #x2 = BatchNormalization(mode=2)( x2 )
  #x2 = Activation( 'relu' )( x2 )
  #x2 = Dropout( 0.25 )( x2 )

  xOut = merge([x, xIn], mode='sum')
  #x2 = MaxPooling2D(pool_size=(2,2))( x2 )

  return xOut

rand_dim = 5
dim = 28

def Generator():

  act = LeakyReLU( alpha=0.2 )

  model_input = Input(shape=(rand_dim,))

  x = Dense( dim*dim )( model_input )
  x = BatchNormalization()( x )
  x = act( x )
  #x = Reshape( (dim, dim, 1) )( x )
  #x = Dropout( 0.2 )( x )

  #x = Conv2D(64, 3, 1, input_shape=(dim, dim, 1))( x )
  #x = BatchNormalization()( x )
  #x = act( x )
  #x = Dropout(0.2)( x )

  '''
  x = MaxPooling2D( pool_size=(2,2) )( x )
  x = Conv2D(32, 3, 1)( x )
  x = BatchNormalization()( x )
  x = act( x )
  x = Dropout( 0.2 )( x )
  x = Dropout( 0.2 )( x )
  x = Conv2D(16, 2, 1)( x )
  x = BatchNormalization()( x )
  x = act( x )
  x = Dropout( 0.2 )( x )
  x = MaxPooling2D( pool_size=(2,2) )( x )
  '''
  #x = Flatten()( x )
  x = Dense( 1024 )( x )
  x = BatchNormalization()(x)
  x = act( x )
  x = Dropout( 0.1 )(x)

  x = ResNetBlock( x )
  x = ResNetBlock( x )

  #x = Dense( 512 )( x )
  #x = BatchNormalization()(x)
  #x = act( x )
  #x = Dropout( 0.1 )(x)

  x = Dense( 5 )( x )
  output = Lambda(( lambda x: T.tensor.sgn(x) * (T.tensor.abs_(x) % np.pi) ))(x)

  model = Model(input=model_input, output=output)

  #generator_optimizer = SGD(lr=0.1, momentum=0.3, decay=1e-5)
  #model.compile(loss="binary_crossentropy", optimizer=generator_optimizer)
  return model

def Discriminator():
  act = LeakyReLU( alpha=0.2 )

  model_input = Input(shape=(5,))

  x = Dense(5*5)(model_input)
  x = BatchNormalization(mode=2)( x )
  x = act( x )
  x = Reshape((5, 5, 1))( x )
  x = Dropout( 0.25 )( x )
  
  x = Conv2D(64, 2, 1, input_shape=(5, 5, 1))( x )
  x = BatchNormalization(mode=2)( x )
  x = act( x )
  x = Dropout(0.25)( x )
  x = Conv2D(32, 2, 1)( x )
  x = BatchNormalization(mode=2)( x )
  x = act( x )
  x = Dropout( 0.25 )( x )

  x = MaxPooling2D(pool_size=(2,2))( x )

  x = Flatten()( x )
  x = Dense( 512 )( x )
  x = BatchNormalization(mode=2)(x)
  x = act(x)
  x = Dropout( 0.25 )(x)

  x = Dense( 256 )( x )
  x = BatchNormalization(mode=2)(x)
  x = act(x)
  x = Dropout( 0.25 )(x)

  x = Dense( 128 )( x )
  x = BatchNormalization(mode=2)(x)
  x = act(x)
  x = Dropout( 0.25 )(x)

  x = Dense( 64 )( x )
  x = BatchNormalization(mode=2)(x)
  x = act(x)
  x = Dropout( 0.25 )(x)

  x = Dense( 32 )( x )
  x = BatchNormalization(mode=2)(x)
  x = act(x)
  x = Dropout( 0.25 )(x)

  x = Dense(1)(x)
  output = Activation('sigmoid')(x)

  model = Model(input=model_input, output=output)
  discriminator_optimizer = SGD(lr=0.1, momentum=0.1, decay=1e-5)
  model.compile(loss="binary_crossentropy", optimizer=discriminator_optimizer, metrics=['accuracy'])
  return model

def GAN(g_model, d_model):

  GAN = Sequential()

  GAN.add(g_model)

  d_model.trainable = False
  GAN.add(d_model)

  gan_optimizer = SGD(0.1, momentum=0.3)
  GAN.compile(loss="mean_squared_error", optimizer=gan_optimizer, metrics=['accuracy'])
  #GAN.compile(loss='mean_squared_error', optimizer='adam', metrics=['accuracy'])
  return GAN

# Model
Gen = Generator()
Dis = Discriminator()
GAN = GAN(Gen, Dis)
GAN.summary()

Gen.summary()
Dis.summary()


# Paramters
gan_losses = {"d":[], "g":[], "f":[]}
epoch = 100 # 300000
batch = 1000 # 1000


# Input (signal)
signal = np.loadtxt('./input/ggH_Resolved_SRCR_700/signal.d.txt', delimiter=',')
X_train = signal[:int(len(signal)*2/3)]

# Output
f = TFile('./output/test.root', 'recreate')
tr = TTree('coll','coll')

Theta1 = array('f', [0])
Theta2 = array('f', [0])
ThetaStar = array('f', [0])
Phi = array('f', [0])
Phi1 = array('f', [0])

tr.Branch('Theta1', Theta1, 'Theta1/F')
tr.Branch('Theta2', Theta2, 'Theta2/F')
tr.Branch('ThetaStar', ThetaStar, 'ThetaStar/F')
tr.Branch('Phi', Phi, 'Phi/F')
tr.Branch('Phi1', Phi1, 'Phi1/F')


####################################
# Train 
####################################
for e in range(epoch):

  #if e%20==0 : print e, ' epochs ------------------------'
  print "### Loop", e, '#######################################################'

  # Generated data from noise
  noise = np.random.normal(0, 1, size=[batch, rand_dim])
  generated_angular = Gen.predict_on_batch(noise)

  # Random train data extraction
  rand_index = np.random.randint(0, X_train.shape[0], size=batch)
  train_angular = X_train[rand_index, :]

  # Merge and Y label 
  X = np.vstack((train_angular, generated_angular))
  y = np.zeros(int(2*batch))
  y[batch:] = 1
  y = y.astype(int)

  # Discriminator training
  print 'Discriminator training ...'
  Dis.trainable = True
  Dis.fit(X,y,nb_epoch=6,batch_size=int(batch/8), verbose=1)
  #d_loss = Dis.train_on_batch(x=X, y=y)
  Dis.trainable = False

  # Generator training
  print 'Generator training ...'
  noise = np.random.normal(0, 1, size=[batch, rand_dim])
  y = np.ones(batch)
  y = y.astype(int)
  GAN.fit(noise,y,nb_epoch=12,batch_size=int(batch/10), verbose=1)
  #g_loss = GAN.train_on_batch(x=noise, y=y)

  #print 'Generator_loss :', g_loss, ',  Discriminator_loss :', d_loss


print 'Training done ................'
sample_size = 10000
print 'Making noise for sampling ................'
noise = np.random.normal(0, 1, size=[sample_size, rand_dim])
print '. ................'
sample = Gen.predict_on_batch(noise)
print 'done .................'

for i in range(len(sample)):

	ang = sample[i]

	Theta1[0] = float(ang[0])
	Theta2[0] = float(ang[1])
	ThetaStar[0] = float(ang[2])
	Phi[0] = float(ang[3])
	Phi1[0] = float(ang[4])

	tr.Fill()

f.Write()
f.Close()
