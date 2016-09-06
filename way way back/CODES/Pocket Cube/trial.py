# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 07:18:01 2015

@author: nelmntrx
"""

# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 03:04:47 2015

@author: nelmntrx
"""


import cube as cube
import operation as operate
import networkx as nx
import string as st
import itertools
import matplotlib.pyplot as plt
import pylab
import os
import random
import pydot

'''This is the main program for the pocket cube. 
There will be 4 main group oprations: rotate_A, rotate_B, rotate_top, and rotate_bot.
The rotation is by default clockwise. We will randomize the implementation of each
operation to a particular state. We will begin at the solved state of the cube and
then stop until no more unique state will be produced.'''






def metric():
    state = 'ABCDEFGHIJKLMNOPQRSTUVWX'
    
    pocketcube_states = []
    while state not in pocketcube_states:
        ignition = random.random()
        if 0<ignition<=0.25:
           #apply operation on the string, output: an array
            state_array= operate.rotate_A(state)
            #brings back the array to string
            state_string= cube.return_string(state_array)
            #appends the new state to an array
            pocketcube_states.append(state_string)
            graph = cube.network(state_string)
    
            print 'Successful left side rotation! This is process number {}. Done with the state: {}'.format(len(pocketcube_states),state_string)
            cc = nx.transitivity(graph)
            print 'This is its clustering coefficient: {}'.format(cc)
            label = 'network({})'.format(state_string)
            nx.write_dot(graph,label)        
            print ' '
            state_string = state
    
        elif 0.25<ignition<=0.50:
           #apply operation on the string, output: an array
            state_array= operate.rotate_B(state)
            #brings back the array to string
            state_string= cube.return_string(state_array)
            #appends the new state to an array
            pocketcube_states.append(state_string)
            graph = cube.network(state_string)
    #        label = 'network({})'.format(state_string)
    #        nx.write_dot(graph,label)
    
            print 'Successful right side rotation! This is process number {}. File uploaded to directory. Done with the state: {}'.format(len(pocketcube_states),state_string)
            cc = nx.transitivity(graph)
            print 'This is its clustering coefficient: {}'.format(cc)
            label = 'network({})'.format(state_string)
            nx.write_dot(graph,label)        
            
            print ' '
            state_string = state
            
        elif 0.5<ignition<=0.75:
           #apply operation on the string, output: an array
            state_array= operate.rotate_top(state)
            #brings back the array to string
            state_string= cube.return_string(state_array)
            #appends the new state to an array
            pocketcube_states.append(state_string)
            graph = cube.network(state_string)
    #        label = 'network({})'.format(state_string)
    #        nx.write_dot(graph,label)
    
            print 'Successful top rotation! This is process number {}. File uploaded to directory. Done with the state: {}'.format(len(pocketcube_states),state_string)
            cc = nx.transitivity(graph)
            print 'This is its clustering coefficient: {}'.format(cc)
            label = 'network({})'.format(state_string)
            nx.write_dot(graph,label)        
            print ' ' 
            state_string = state
    
        elif 0.75<ignition<=1.0:
           #apply operation on the string, output: an array
            state_array= operate.rotate_bot(state)
            #brings back the array to string
            state_string= cube.return_string(state_array)
            #appends the new state to an array
            pocketcube_states.append(state_string)
            graph = cube.network(state_string)
    #        label = 'network({})'.format(state_string)
    #        nx.write_dot(graph,label)
    
            print 'Successful base rotation! This is process number {}. File uploaded to directory. Done with the state: {}'.format(len(pocketcube_states),state_string)
            cc = nx.transitivity(graph)
            print 'This is its clustering coefficient: {}'.format(cc)
            label = 'network({})'.format(state_string)
            nx.write_dot(graph,label)        
            print ' '
            state_string = state    
        
        
    
    
    print "Congratulations! You have arrived to the {} state of a 2x2x2 Rubik's cube!".format(len(pocketcube_states))
