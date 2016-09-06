# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 03:04:47 2015

@author: nelmntrx
"""

import csv
import cube as cube
import operation as operate
import networkx as nx
import string as st
import itertools
import matplotlib.pyplot as plt
import pylab
import os
import random
import measures as measure
#import pydot

'''This is the main program for the pocket cube. 
There will be 4 main group oprations: rotate_A, rotate_B, rotate_top, and rotate_bot.
The rotation is by default clockwise. We will randomize the implementation of each
operation to a particular state. We will begin at the solved state of the cube and
then stop until no more unique state will be produced.'''

state = 'ABCDEFGHIJKLMNOPQRSTUVWX'

pocketcube_states = []
transitivity=[]
algebra_connect=[]
pearson =[]
zhangc =[]
barratc=[]
onnela=[]
while len(pocketcube_states)<5:
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
        ac = nx.algebraic_connectivity(graph)
        ass = nx.degree_pearson_correlation_coefficient(graph)
        zhang = measure.zhang_clustering(state_string)   
        barrat = measure.barrat_clustering(state_string)
        onnel = measure.onnela_clustering(state_string)
        print 'This is its clustering coefficient: {}'.format(cc)
        print 'This is its degree pearson correlation coefficient: {}'.format(ass)
        print 'This is its alegbraic connectivity: {}'.format(ac)
        print 'This is its Zhang clustering coefficient: {}.'.format(zhang)
        print 'This is its Barrat clustering coefficient: {}.'.format(barrat)
        print 'This is its Onnela clustering coefficient: {}.'.format(onnel)
#        label = 'network({})'.format(state_string)
#        nx.write_dot(graph,label)

        print ' '
        state_string = state

    elif 0.25<ignition<=0.50:
       #apply operation on the string, output: an array
        state_array= operate.rotate_B(state)
        #brings back the array to string
        state_string= cube.return_string(state_array)
        #appends the new state to an array
        pocketcube_states.append(state_string)
#        graph = cube.network(state_string)
#        label = 'network({})'.format(state_string)
#        nx.write_dot(graph,label)

        print 'Successful right side rotation! This is process number {}. File uploaded to directory. Done with the state: {}'.format(len(pocketcube_states),state_string)
        cc = nx.transitivity(graph)
        ac = nx.algebraic_connectivity(graph)
        ass = nx.degree_pearson_correlation_coefficient(graph)
        zhang = measure.zhang_clustering(state_string)   
        barrat = measure.barrat_clustering(state_string)
        onnel = measure.onnela_clustering(state_string)
        print 'This is its clustering coefficient: {}'.format(cc)
        print 'This is its degree pearson correlation coefficient: {}'.format(ass)
        print 'This is its alegbraic connectivity: {}'.format(ac)
        print 'This is its Zhang clustering coefficient: {}.'.format(zhang)
        print 'This is its Barrat clustering coefficient: {}.'.format(barrat)
        print 'This is its Onnela clustering coefficient: {}.'.format(onnel)
#        label = 'network({})'.format(state_string)
#        nx.write_dot(graph,label)        
        
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
        ac = nx.algebraic_connectivity(graph)
        ass = nx.degree_pearson_correlation_coefficient(graph)
        zhang = measure.zhang_clustering(state_string)   
        barrat = measure.barrat_clustering(state_string)
        onnel = measure.onnela_clustering(state_string)
        print 'This is its clustering coefficient: {}'.format(cc)
        print 'This is its degree pearson correlation coefficient: {}'.format(ass)
        print 'This is its alegbraic connectivity: {}'.format(ac)
        print 'This is its Zhang clustering coefficient: {}.'.format(zhang)
        print 'This is its Barrat clustering coefficient: {}.'.format(barrat)
        print 'This is its Onnela clustering coefficient: {}.'.format(onnel)
#        label = 'network({})'.format(state_string)
#        nx.write_dot(graph,label)        
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
        ac = nx.algebraic_connectivity(graph)
        ass = nx.degree_pearson_correlation_coefficient(graph)
        zhang = measure.zhang_clustering(state_string)   
        barrat = measure.barrat_clustering(state_string)
        onnel = measure.onnela_clustering(state_string)
        print 'This is its clustering coefficient: {}'.format(cc)
        print 'This is its degree pearson correlation coefficient: {}'.format(ass)
        print 'This is its alegbraic connectivity: {}'.format(ac)
        print 'This is its Zhang clustering coefficient: {}.'.format(zhang)
        print 'This is its Barrat clustering coefficient: {}.'.format(barrat)
        print 'This is its Onnela clustering coefficient: {}.'.format(onnel)
#        label = 'network({})'.format(state_string)
#        nx.write_dot(graph,label)        
        print ' '
        state_string = state
    
    pearson.append(ass)
    algebra_connect.append(ac)
    transitivity.append(cc)
    zhangc.append(zhang)
    barratc.append(barrat)
    onnela.append(onnel)
    
    
    with open('StateString.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in pocketcube_states:
            writer.writerow(state)

    with open('Transitivity.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in transitivity:
            writer.writerow([state])
    
    with open('Alegbraic_Connectivity.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in algebra_connect:
            writer.writerow([state])    
            
    with open('Pearson.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in pearson:
            writer.writerow([state])
            
    with open('Zhang.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in zhangc:
            writer.writerow([state])
    with open('Barrat.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in barratc:
            writer.writerow([state])
    with open('Onnela.txt', "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for state in onnela:
            writer.writerow([state]) 
    
   
print "Congratulations! You have arrived to the {} state of a 2x2x2 Rubik's cube!".format(len(pocketcube_states))

'''Saves the list of states to a csv files. All of them are still in string form. This will serve
as a back up of mynetwork in case pydot fails to its task'''
#
#for state_string in pocketcube_states:
#    graph = cube.network(state_string)
#    label = 'network({})'.format(state_string)
#    print state_string    
#    nx.write_dot(graph,label) 

       
        



#print transitivity[0]
#print pearson
#print algebra_connect


#outfile = open('State_String_BackUp.txt', 'w')
#for state in pocketcube_states:
#    outfile.write(state)
#    outfile.write('\n')
#outfile.close()
#
#outfile = open('Algebraic_Connect.txt', 'w')
#for state in algebra_connect:
#    outfile.write(state)
#    outfile.write('\n')
#outfile.close()
#
#outfile = open('Transitivity.txt', 'w')
#for state in transitivity:
#    outfile.write(state)
#    outfile.write('\n')
#outfile.close()
#    
#outfile = open('Pearson.txt', 'w')
#for state in pearson:
#    outfile.write(state)
#    outfile.write('\n')
#outfile.close()

