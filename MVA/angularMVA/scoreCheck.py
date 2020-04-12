#!/usr/bin/env python

import sys

# Select Theano as backend for Keras
from os import environ
environ['KERAS_BACKEND'] = 'theano'

# Set architecture of system (AVX instruction set is not supported on SWAN)
environ['THEANO_FLAGS'] = 'gcc.cxxflags=-march=corei7'

from ROOT import TMVA, TFile, TString, TTree
from array import array
from subprocess import call
from os.path import isfile

from array import array
from numpy import cos

if __name__ == "__main__":

  args = sys.argv
  if len(args) > 1 :
    gp = args[1]
    regime = args[2]
    mass = args[3]
    mc = args[4]
    sig = args[5]
  else:
    gp = 'VBFH'
    regime = 'Resolved'
    mass = '700'
    mc = 'ad'
    sig = 'bkg'
 
  signalID = gp + '_' + regime + '_SRCR_' + mass
  if sig=='bkg':
    sampleName = gp + '_' + regime + '_SRCR_Zjets.' + mc
    outName = gp + '_' + regime + '_SRCR_Zjets.' + mc
  else:
    sampleName = signalID + '/signal.' + mc
    outName = signalID + "." + mc


  # Setup TMVA
  TMVA.Tools.Instance()
  TMVA.PyMethodBase.PyInitialize()
  reader = TMVA.Reader("Color:!Silent")

  # Load data
  prePath='/home/myamatan/data3/angularAna/MVA_workspace/sampleMake/output/'
  data = TFile.Open(prePath + sampleName  + '.root')
  sample = data.Get('coll')

  # for MVA
  var1=array("f",[0])
  var2=array("f",[0])
  var3=array("f",[0])
  var4=array("f",[0])
  var5=array("f",[0])
  var6=array("f",[0])
  var7=array("f",[0])
  var8=array("f",[0])
  var9=array("f",[0])
  var10=array("f",[0])
  var11=array("f",[0])
  var12=array("f",[0])
  # Read
  v1=array("f",[0])
  v2=array("f",[0])
  v3=array("f",[0])
  v4=array("f",[0])
  v5=array("f",[0])
  v6=array("f",[0])
  v7=array("f",[0])
  v8=array("f",[0])
  v9=array("f",[0])
  v10=array("f",[0])
  v11=array("f",[0])
  v12=array("f",[0])

  if gp in {'ggH','RSG','HVT'}:

    if regime=="Resolved":
      reader.AddVariable('myvar1 := cos(Theta1)', var1)
      reader.AddVariable('myvar2 := cos(Theta2)', var2)
      reader.AddVariable('myvar3 := cos(ThetaStar)', var3)
      reader.AddVariable('Phi',var4)
      reader.AddVariable('Phi1',var5)
      sample.SetBranchAddress('Theta1',v1)
      sample.SetBranchAddress('Theta2',v2)
      sample.SetBranchAddress('ThetaStar',v3)
      sample.SetBranchAddress('Phi',v4)
      sample.SetBranchAddress('Phi1',v5)
      sample.SetBranchAddress('Mjj',v11)
      sample.SetBranchAddress('Mlljj',v12)
    elif regime=="Merged":
      reader.AddVariable('myvar1 := cos(Theta1_boosted)', var1)
      reader.AddVariable('myvar2 := cos(ThetaStar_boosted)', var3)
      reader.AddVariable('Phi1_boosted',var5)
      sample.SetBranchAddress('Theta1_boosted',v1)
      sample.SetBranchAddress('ThetaStar_boosted',v3)
      sample.SetBranchAddress('Phi1_boosted',v5)
      sample.SetBranchAddress('MJ',v11)
      sample.SetBranchAddress('MllJ',v12)

  elif gp in {'VBFH','VBFHVT'}: 

    if regime=="Resolved":
      reader.AddVariable('myvar1 := cos(Theta1)', var1)
      reader.AddVariable('myvar2 := cos(Theta2)', var2)
      reader.AddVariable('myvar3 := cos(ThetaStar)', var3)
      reader.AddVariable('Phi',var4)
      reader.AddVariable('Phi1',var5)
      reader.AddVariable('dR_vbfjet1_Zll',var6)
      reader.AddVariable('dR_vbfjet2_Zll',var7)
      reader.AddVariable('dR_vbfjet1_Vqq',var8)
      reader.AddVariable('dR_vbfjet2_Vqq',var9)
      reader.AddVariable('dR_vbfjets',var10)
      sample.SetBranchAddress('Theta1',v1)
      sample.SetBranchAddress('Theta2',v2)
      sample.SetBranchAddress('ThetaStar',v3)
      sample.SetBranchAddress('Phi',v4)
      sample.SetBranchAddress('Phi1',v5)
      sample.SetBranchAddress('dR_vbfjet1_Zll',v6)
      sample.SetBranchAddress('dR_vbfjet2_Zll',v7)
      sample.SetBranchAddress('dR_vbfjet1_Vqq',v8)
      sample.SetBranchAddress('dR_vbfjet2_Vqq',v9)
      sample.SetBranchAddress('dR_vbfjets',v10)
      sample.SetBranchAddress('Mjj',v11)
      sample.SetBranchAddress('Mlljj',v12)
    elif regime=="Merged":
      reader.AddVariable('myvar1 := cos(Theta1_boosted)', var1)
      reader.AddVariable('myvar2 := cos(ThetaStar_boosted)', var3)
      reader.AddVariable('Phi1_boosted',var5)
      reader.AddVariable('dR_vbfjet1_Zll_boosted',var6)
      reader.AddVariable('dR_vbfjet2_Zll_boosted',var7)
      reader.AddVariable('dR_vbfjet1_Vqq_boosted',var8)
      reader.AddVariable('dR_vbfjet2_Vqq_boosted',var9)
      reader.AddVariable('dR_vbfjets_boosted',var10)
      sample.SetBranchAddress('Theta1_boosted',v1)
      sample.SetBranchAddress('ThetaStar_boosted',v3)
      sample.SetBranchAddress('Phi1_boosted',v5)
      sample.SetBranchAddress('dR_vbfjet1_Zll_boosted',v6)
      sample.SetBranchAddress('dR_vbfjet2_Zll_boosted',v7)
      sample.SetBranchAddress('dR_vbfjet1_Vqq_boosted',v8)
      sample.SetBranchAddress('dR_vbfjet2_Vqq_boosted',v9)
      sample.SetBranchAddress('dR_vbfjets_boosted',v10)
      sample.SetBranchAddress('MJ',v11)
      sample.SetBranchAddress('MllJ',v12)
      
  # Book methods
  reader.BookMVA('BDTG_'+signalID, TString('/nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/MVA/angularMVA/weights/weights/TMVAClassification_BDTG_'+signalID+'.weights.xml'))
  
  # Tree for output
  f = TFile('./outputValid/'+outName+'.root', 'recreate')
  tr = TTree('coll','coll')
  Theta1 = array("f", [0])
  Theta2 = array("f", [0])
  ThetaStar = array("f", [0])
  Phi = array("f", [0])
  Phi1 = array("f", [0])
  dR_vbfjet1_Zll = array("f", [0])
  dR_vbfjet2_Zll = array("f", [0])
  dR_vbfjet1_Vqq = array("f", [0])
  dR_vbfjet2_Vqq = array("f", [0])
  dR_vbfjets = array("f", [0])
  Mqq = array("f", [0])
  Mllqq = array("f", [0])
  Score = array("f", [0])
  
  tr.Branch('cosTheta1', Theta1, 'cosTheta1/F')
  tr.Branch('cosTheta2', Theta2, 'cosTheta2/F')
  tr.Branch('cosThetaStar', ThetaStar, 'cosThetaStar/F')
  tr.Branch('Phi', Phi, 'Phi/F')
  tr.Branch('Phi1', Phi1, 'Phi1/F')
  tr.Branch('dR_vbfjet1_Zll', dR_vbfjet1_Zll, 'dR_vbfjet1_Zll/F')
  tr.Branch('dR_vbfjet2_Zll', dR_vbfjet2_Zll, 'dR_vbfjet2_Zll/F')
  tr.Branch('dR_vbfjet1_Vqq', dR_vbfjet1_Vqq, 'dR_vbfjet1_Vqq/F')
  tr.Branch('dR_vbfjet2_Vqq', dR_vbfjet2_Vqq, 'dR_vbfjet2_Vqq/F')
  tr.Branch('dR_vbfjets', dR_vbfjets, 'dR_vbfjets/F')
  tr.Branch('Mqq', Mqq, 'Mqq/F')
  tr.Branch('Mllqq', Mllqq, 'Mllqq/F')
  tr.Branch('Score', Score, 'Score/F')
  
  for i in range(sample.GetEntries()):

      sample.GetEntry(i)

      var1[0] = cos(v1[0])
      var2[0] = cos(v2[0])
      var3[0] = cos(v3[0])
      var4[0] = v4[0]
      var5[0] = v5[0]	
      var6[0] = v6[0]
      var7[0] = v7[0]	
      var8[0] = v8[0]	
      var9[0] = v9[0]	
      var10[0] = v10[0]	
      var11[0] = v11[0]	
      var12[0] = v12[0]	
  
      Theta1[0] = var1[0]
      Theta2[0] = var2[0]
      ThetaStar[0] = var3[0]
      Phi[0] = var4[0]
      Phi1[0] = var5[0]
      dR_vbfjet1_Zll[0] = var6[0]
      dR_vbfjet2_Zll[0] = var7[0]
      dR_vbfjet1_Vqq[0] = var8[0]
      dR_vbfjet2_Vqq[0] = var9[0]
      dR_vbfjets[0] = var10[0]
      Mqq[0] = var11[0]
      Mllqq[0] = var12[0]
      Score[0] = reader.EvaluateMVA('BDTG_'+signalID)

      tr.Fill()
  
  f.Write()
  f.Close()
  
  
