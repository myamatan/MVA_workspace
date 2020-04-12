from keras.models import Sequential, Model
from keras.layers.core import Dense
from keras.optimizers import Adam

from keras.layers.advanced_activations import LeakyReLU
from keras.layers.recurrent import LSTM, SimpleRNN
from keras.layers import Dense, Activation, BatchNormalization, Dropout, Input, Lambda
from keras.layers import Conv2D, MaxPooling2D, Flatten, Reshape, UpSampling2D, merge
#from keras.layers.embeddings import Embedding
#from keras.layers.wrappers import TimeDistributed

from keras.optimizers import SGD
from keras.datasets import mnist

def ResNetBlock(xIn):

  x = Dense( 256 )( xIn )
  x = BatchNormalization()(x)
  x = Activation( 'relu' )( x )
  x = Dropout( 0.1 )(x)

  x = Dense( 256 )( x )
  x = BatchNormalization()(x)
  x = Activation( 'relu' )( x )
  x = Dropout( 0.1 )(x)

  #x2 = Conv2D( 32, 2, 2, border_mode='same' )( x1 )
  #x2 = BatchNormalization(mode=2)( x2 )
  #x2 = Activation( 'relu' )( x2 )
  #x2 = Dropout( 0.25 )( x2 )

  xOut = merge([x, xIn], mode='sum')
  #x2 = MaxPooling2D(pool_size=(2,2))( x2 )

  return xOut


def myDNN(nInput):

  #act = LeakyReLU( alpha=0.2 )

  model_input = Input(shape=(nInput,))

  ##x = Dense( nInput*nInput, init='glorot_normal')( model_input )
  
  x = Dense( 256, init='glorot_normal')( model_input )
  x = BatchNormalization()( x )
  x = Activation( 'relu' )( x )
  ##x = Reshape((nInput, nInput, 1))( x )
  x = Dropout( 0.05 )( x )

  x = ResNetBlock( x )
  x = ResNetBlock( x )
  x = ResNetBlock( x )
  #x = ResNetBlock( x )
 
  '''
  x = Conv2D( 32, 2, 2, input_shape=(nInput, nInput, 1),  border_mode='same' )( x ) ## Doesn't work
  #x = Conv2D( 32, 2, 2, input_shape=(nInput, nInput, 1) )( x )
  x = BatchNormalization(mode=2)( x )
  x = Activation( 'relu' )( x )
  x = Dropout( 0.25 )( x )
  #x = MaxPooling2D(pool_size=(2,2))( x )

  #x = ResNetBlock( x )
  #x = ResNetBlock( x )

  x = Conv2D(64, 2, 2)( x )
  x = BatchNormalization(mode=2)( x )
  x = Activation( 'relu' )( x )
  x = Dropout( 0.25 )( x )

  x = Conv2D(32, 2, 2)( x )
  x = BatchNormalization(mode=2)( x )
  x = Activation( 'relu' )( x )
  x = Dropout( 0.25 )( x )

  x = Flatten()( x )

  x = Dense( 256 )( x )
  x = BatchNormalization(mode=2)(x)
  x = Activation( 'relu' )( x )
  x = Dropout( 0.25 )(x)
  '''

  #x = Dense( 128 )( x )
  #x = BatchNormalization(mode=2)(x)
  #x = Activation( 'relu' )( x )
  #x = Dropout( 0.25 )(x)

  x = Dense(2, init='glorot_uniform')(x)
  output = Activation('softmax')(x)

  model = Model(input=model_input, output=output)

  model.compile(loss='categorical_crossentropy', optimizer=Adam(), metrics=['accuracy',])

  return model


def CNNs(nInput):

  model_input = Input(shape=(nInput,))

  x = Dense( nInput * nInput, init='glorot_normal')( model_input )
  x = Reshape((nInput, nInput, 1))( x )
  x = Conv2D( 32, 2, 2, input_shape=(nInput, nInput, 1),  border_mode='same' )( x ) ## Doesn't work
  x = Conv2D(32, 2, 2)( x )

  x = Flatten()( x )

  x = Dense( 256 )( x )
  x = Dense(2, init='glorot_uniform')(x)
  output = Activation('softmax')(x)

  model = Model(input=model_input, output=output)
  model.compile(loss='categorical_crossentropy', optimizer=Adam(), metrics=['accuracy',])
  
  return model

def RNNs():

  num_steps=30
  batch_size=20
  hidden_size=500
  vocabulary=10

  model = Sequential()
  model.add(Embedding(vocabulary, hidden_size, input_length=num_steps))
  model.add(LSTM(hidden_size, return_sequences=True))
  model.add(TimeDistributed(Dense(vocabulary)))
  model.add(Activation('softmax'))

  model.compile(loss='categorical_crossentropy', optimizer=Adam(), metrics=['accuracy',])
  
  return model
	

