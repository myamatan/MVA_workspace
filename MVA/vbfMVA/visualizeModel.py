from keras.models import Sequential, Model
from keras.layers.core import Dense
from keras.optimizers import Adam

from keras.layers.advanced_activations import LeakyReLU
from keras.layers.recurrent import LSTM, SimpleRNN
from keras.layers import Dense, Activation, BatchNormalization, Dropout, Input, Lambda
from keras.layers import Conv2D, MaxPooling2D, Flatten, Reshape, UpSampling2D, merge
from keras.layers.embeddings import Embedding
from keras.layers.wrappers import TimeDistributed

from keras.optimizers import SGD
from keras.datasets import mnist

from modelMVA import ResNetBlock, myDNN, CNNs, RNNs

from keras.models import Sequential
from keras.layers import Dense
from keras.utils.vis_utils import plot_model

#model = myDNN(5)
#model = CNNs(5)
model = RNNs()

plot_model(model, to_file='./pics/model_plot_RNN.png', show_shapes=True, show_layer_names=True)
