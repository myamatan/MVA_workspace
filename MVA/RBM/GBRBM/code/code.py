# Gaussian-Bernoulli Restricted Boltzmann Machine

import sys

from ROOT import TMVA, TFile, TTree, TCut
from array import array

import numpy as np

# Restricted Boltzmann Machien 
class Restricted_BM:

    def __init__(self, n_visible, n_hidden):
        self.n_visible = n_visible
        self.n_hidden = n_hidden
        self.w = np.random.normal(0, 0.01, [n_visible,n_hidden])
        self.b = np.zeros(n_visible)
        self.c = np.zeros(n_hidden)
        self.z = np.zeros(n_visible)
        self.s = np.ones(n_visible)

    def get_probability_hidden(self, visibles):
        prob = np.zeros(self.n_hidden)
	lam = self.c + np.dot(visibles/self.s, self.w)
	prob = 1 / ( 1 + np.exp(-1*lam) )
        return prob 

    def get_probability_visible(self, hiddens):
        prob = np.zeros(self.n_visible)
	mean = self.b + np.dot(self.w, hiddens)
	sigma = self.s
        return mean, sigma

    def get_sample(self,prod):
        rand = np.random.uniform(0,1,len(prod))
	sample = np.where( prod > rand, 1, 0)
        return sample

    def sample_h_given_v(self, prod):
        rand = np.random.uniform(0,1,len(prod))
	sample = np.where( prod > rand, 1, 0)
        return sample

    def sample_v_given_h(self, mean, sigma):
        visible = np.random.normal(mean, sigma)
        #visible = mean
        return visible

    def train(self,visible0,rate):

	prob0 = self.get_probability_hidden(visible0)
        hidden0 = self.sample_h_given_v( prob0 )

	prob_tov = self.get_probability_visible(hidden0)
        visible1 = self.sample_v_given_h(prob_tov[0], prob_tov[1])
	prob1 = self.get_probability_hidden(visible1)
        hidden1 = self.sample_h_given_v( prob1 )

        vz1 = 0.5*(visible0-self.b)**2 - np.dot(prob0, self.w.transpose())*visible0
        vz2 = 0.5*(visible1-self.b)**2 - np.dot(prob1, self.w.transpose())*visible1
	termexp = np.exp( -1 * self.z )
        self.z += rate * termexp * ( vz1 - vz2 )/self.s
        #self.z += rate * ( vz1 - vz2 )/self.s
	
	vOs0 = (visible0/self.s).reshape(self.n_visible,1)
	prb0 = prob0.reshape(1,len(prob0))
	vOs1 = (visible1/self.s).reshape(self.n_visible,1)
	prb1 = prob1.reshape(1,len(prob1))

        self.w += rate * (np.dot(vOs0,prb0) - np.dot(vOs1,prb1))
        self.b += rate * (visible0/self.s - visible1/self.s)
        self.c += rate * (prob0 - prob1)
	self.s = np.exp(self.z)

    def get_reconstruction(self,visible):
        hidden = self.sample_h_given_v( self.get_probability_hidden(visible) )
	mean, sigma = self.get_probability_visible(hidden)
        visible = self.sample_v_given_h(mean, sigma)
        return visible
	
    def get_sample(self, rands):
   	hidden = rands
	mean, sigma = self.get_probability_visible(hidden)
	visible = self.sample_v_given_h(mean, sigma)
	return visible


if __name__ == '__main__':

    # Output
    f = TFile('../output/test.root', 'recreate')
    tr = TTree('coll','coll')
    
    v1 = array('f', [0])
    v2 = array('f', [0])
    v3 = array('f', [0])
    bv1 = array('f', [0])
    bv2 = array('f', [0])
    bv3 = array('f', [0])
    bbv1 = array('f', [0])
    bbv2 = array('f', [0])
    bbv3 = array('f', [0])

    tr.Branch('v1', v1, 'v1/F')
    tr.Branch('v2', v2, 'v2/F')
    tr.Branch('v3', v3, 'v3/F')
    tr.Branch('bv1', bv1, 'bv1/F')
    tr.Branch('bv2', bv2, 'bv2/F')
    tr.Branch('bv3', bv3, 'bv3/F')
    tr.Branch('bbv1', bbv1, 'bbv1/F')
    tr.Branch('bbv2', bbv2, 'bbv2/F')
    tr.Branch('bbv3', bbv3, 'bbv3/F')

    print('- Test ----------------------')
    rbm = Restricted_BM(3,100)
    print('N_visible:',rbm.n_visible)
    print('N_hidden:',rbm.n_hidden)
    print('-----------------------------')

    # sample
    Nsample = 6000
    X = np.random.normal(0, 1, Nsample)
    Y = np.random.normal(0, 1, Nsample)
    Z = np.random.normal(0, 1, Nsample)
    rho = 0.6
    rho2 = 0.8
    var1 = X
    var2 = rho*X + np.sqrt(1-rho**2)*Y
    var3 = rho2*X + np.sqrt(1-rho2**2)*Z
    sample = np.stack((var1, var2, var3), axis=-1)

    lr1=1e-2
    n1=100
    lr2=1e-3
    n2=1000
    print 'First learning (lr=',lr1,')......'
    for i in range(n1):
        for k in range(Nsample):
            rbm.train(sample[np.random.randint(Nsample)], lr1)
        if i%20==0 : print i,'/',n1,' : ',rbm.w[0][:5]

    print 'Second learning (lr=',lr2,')......'
    for i in range(n2):
        for k in range(Nsample):
            rbm.train(sample[np.random.randint(Nsample)], lr2)
        if i%50==0 : print i,'/',n2,' : ',rbm.w[0][:5]

    for i in range(Nsample):
    	v1[0] = float(sample[i][0])
    	v2[0] = float(sample[i][1])
    	v3[0] = float(sample[i][2])
    	bv = rbm.get_reconstruction(sample[i])
	bv1[0] = float(bv[0])
	bv2[0] = float(bv[1])
	bv3[0] = float(bv[2])
	rands = np.where(np.random.uniform(0,1,100)>0.5, 1, 0)
    	bbv = rbm.get_sample(rands)
	bbv1[0] = float(bbv[0])
	bbv2[0] = float(bbv[1])
	bbv3[0] = float(bbv[2])

	tr.Fill()

    f.Write()
    f.Close()
