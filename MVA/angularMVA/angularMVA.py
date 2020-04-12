#!/usr/bin/env python
import sys

# Select Theano as backend for Keras
from os import environ
environ['KERAS_BACKEND'] = 'theano'

# Set architecture of system (AVX instruction set is not supported on SWAN)
environ['THEANO_FLAGS'] = 'gcc.cxxflags=-march=corei7'


from ROOT import TMVA, TFile, TTree, TCut, TString
from ROOT import gRandom
from subprocess import call
from os.path import isfile

from keras.models import Sequential, Model
from keras.layers.core import Dense
from keras.optimizers import Adam

from keras.layers.advanced_activations import LeakyReLU
from keras.layers.recurrent import LSTM, SimpleRNN
from keras.layers import Dense, Activation, BatchNormalization, Dropout, Input, Lambda
from keras.layers import Conv2D, MaxPooling2D, Flatten, Reshape, UpSampling2D, merge

from keras.optimizers import SGD
from keras.datasets import mnist

from modelMVA import ResNetBlock, myDNN 

if __name__ == "__main__":

  args = sys.argv
  if len(args) > 1 :
    gp = args[1]
    regime = args[2]
    mass = args[3]
    mc = args[4]
    out = args[5]
  else:
    gp = 'VBFH'
    regime = 'Resolved'
    mass = '700'
    mc = 'ad'
    out = '.myDNN'
  
  gRandom.SetSeed(0)

  signalID = gp + '_' + regime + '_SRCR_' + mass
  signalName = signalID + '/signal.' + mc
  bkgName = gp + '_' + regime + '_SRCR_Zjets.' + mc

  nSF = 1.9
  nTrainSig = 40000 * nSF
  nTrainBkg = 40000 * nSF
  nInput = 5

  # Setup TMVA
  TMVA.PyMethodBase.PyInitialize()
  
  output = TFile.Open('./outputMVA/'+signalID+out+'.root', 'RECREATE')
  factory = TMVA.Factory('TMVAClassification', output,
              '!V:!Silent:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification')

  # Load data
  path = '/home/myamatan/data3/angularAna/MVA_workspace/sampleMake/output/'
  dataS = TFile.Open(path + signalName + '.root')
  signal = dataS.Get('coll')
  dataB = TFile.Open(path + bkgName + '.root')
  background = dataB.Get('coll')
  
  #dataloader = TMVA.DataLoader('weights')
  dataloader = TMVA.DataLoader('test')
  if gp in {'ggH','RSG','HVT'}:

    if regime=="Resolved":
      dataloader.AddVariable('myvar1 := cos(Theta1)','F')
      dataloader.AddVariable('myvar2 := cos(Theta2)','F')
      dataloader.AddVariable('myvar3 := cos(ThetaStar)','F')
      dataloader.AddVariable('Phi')
      dataloader.AddVariable('Phi1')
      dataloader.AddVariable('btagCategory')
      nInput = 6
    elif regime=="Merged":
      dataloader.AddVariable('myvar1 := cos(Theta1_boosted)','F')
      dataloader.AddVariable('myvar2 := cos(ThetaStar_boosted)','F')
      dataloader.AddVariable('Phi1_boosted')
      nInput = 3

  elif gp in {'VBFH','VBFHVT'}: 

    if regime=="Resolved":
      dataloader.AddVariable('myvar1 := cos(Theta1)','F')
      dataloader.AddVariable('myvar2 := cos(Theta2)','F')
      dataloader.AddVariable('myvar3 := cos(ThetaStar)','F')
      dataloader.AddVariable('Phi')
      dataloader.AddVariable('Phi1')
      dataloader.AddVariable('dR_vbfjet1_Zll')
      dataloader.AddVariable('dR_vbfjet2_Zll')
      dataloader.AddVariable('dR_vbfjet1_Vqq')
      dataloader.AddVariable('dR_vbfjet2_Vqq')
      dataloader.AddVariable('dR_vbfjets')
      #dataloader.AddVariable('btagCategory')
      nTrainSig = 12000 * nSF
      nTrainBkg = 12000 * nSF
      nInput = 10
    elif regime=="Merged":
      dataloader.AddVariable('myvar1 := cos(Theta1_boosted)','F')
      dataloader.AddVariable('myvar2 := cos(ThetaStar_boosted)','F')
      dataloader.AddVariable('Phi1_boosted')
      dataloader.AddVariable('dR_vbfjet1_Zll_boosted')
      dataloader.AddVariable('dR_vbfjet2_Zll_boosted')
      dataloader.AddVariable('dR_vbfjet1_Vqq_boosted')
      dataloader.AddVariable('dR_vbfjet2_Vqq_boosted')
      dataloader.AddVariable('dR_vbfjets_boosted')
      nTrainSig = 8500 * nSF
      nTrainBkg = 8500 * nSF
      nInput = 8

  dataloader.AddSignalTree(signal, 1.0)
  dataloader.AddBackgroundTree(background, 1.0)

  dataloader.PrepareTrainingAndTestTree(TCut(''),
          'nTrain_Signal='+str(nTrainSig)+':nTrain_Background='+str(nTrainBkg)+':nTest_Signal=3000:nTest_Background=3000:SplitMode=Random:NormMode=NumEvents:!V')

  ## My DNN
  # Generate model
  model = myDNN(nInput)
  # Store model to file
  model.save('model.h5')
  model.summary()
  factory.BookMethod(dataloader, TMVA.Types.kPyKeras, 'PyKeras',
          'H:!V:VarTransform=G:FilenameModel=model.h5:NumEpochs=10:BatchSize=32')

  # Book methods
  print signalID
  #factory.BookMethod(dataloader, TMVA.Types.kBDT, 'BDTG_'+signalID,
  #        '!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3')

  # Run training, test and evaluation
  factory.TrainAllMethods()
  factory.TestAllMethods()
  factory.EvaluateAllMethods()
