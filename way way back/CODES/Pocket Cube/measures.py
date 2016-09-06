# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 02:17:03 2015

@author: nelmntrx
"""

import networkx as nx
import os
import cube as cube
import operation as op
import csv
import itertools
import numpy as np
#
#for i in os.listdir(os.getcwd()):
#    if i.startswith('network'):
#        name = i
#        graph = nx.read_dot(i)
#        cc = nx.average_clustering(graph)
#        print 'This is the average clustering of {}: {:f}'.format(i, cc)


solved_state = 'ABCDEFGHIJKLMNOPQRSTUVWX'

#rubiks = nx.Graph()
#for letterA in solved_state:
#    weights ={}
#    rubiks.add_node(letterA)
#    for letterB in solved_state:
#
#        if letterA != letterB:
#            weights[(letterA, letterB)]= cube.path(solved_state)[letterA][letterB]
#        
#        rubiks.add_edge(letterA, letterB, attr_dict=weights)
#
#print rubiks.get_edge_data('A','B')


                       
def onnela_clustering(state):
    sum_AB = 0.0 
    C_o=0.0
    letter_sum=0.0
    partial=0.0
    for node in state:
        for letterA in state:
            if letterA != node:
                for letterB in state:
                    if letterA !=letterB and letterB != node:
                        w1 = cube.path(state)[node][letterA]
                        w1A = w1*0.20
#                        print 'For i={}, j={}, k={}'.format(node, letterA, letterB)
#                        print "({},{}:{})".format(node,letterB,w1A)
                        w2 = cube.path(state)[node][letterB]
                        
                        w2A = w2*0.20
#                        print "({},{}:{})".format(node,letterB,w2A)
                        
                        w3 = cube.path(state)[letterA][letterB]
                        w3A = w3*0.20
#                        print "({},{}:{})".format(letterA,letterB,w3A)
                        partial = (w1A*w2A*w3A)**float(1/3)
#                        print partial
                        
                    sum_AB = partial + sum_AB
#                    print "({},{},{}):{}".format(node,letterA,letterB,sum_AB)

            letter_sum = sum_AB + letter_sum
#            print ' '
#            print 'End of first iteration for {}, {}. This is the partial sum: {}'.format(node, letterA, letter_sum)
#            print ' '
#            print 'Start New iterations. For i={}, j={}'.format(node, letterA)
        
        C_node = letter_sum/(23*22)      
        C_o = C_node + C_o
#        print 'End of first iteration for node {}. This is the average clustering of node {}: {}'.format(node,node, C_node)
        sum_AB = 0.0 
        letter_sum=0.0
        partial=0.0       

    return C_o
                          
def sum_weight(state,letter):
#    maximum = 0
    weight = cube.path(state)[letter]
    count = 0
    for i in range(len(weight.values())):
        count = weight.values()[i] + count
    return count
        
def barrat_clustering(state):
    graph = cube.network(state)
    sum_AB = 0
    for letter in state:
        k = nx.degree(graph)[letter]        
        w_sum = np.sum(cube.path(state)[letter].values())
        partial = 0
        partial_sum = 0
        for letterB in graph.nodes():
            for letterC in graph.nodes():
                if (letter,letterB) in graph.edges() and (letter, letterC) in graph.edges():
                
                    wA = cube.path(state)[letter][letterB]
                    wB = cube.path(state)[letter][letterC]
                    partial = ((wA + wB)*0.50)*(w_sum)**-1 + partial
            partial_sum = partial + partial_sum
        sum_AB = ((k)**-1)*((k-1)**-1)*partial_sum + sum_AB
    return sum_AB
                    
                    
def zhang_clustering(state):
    graph = cube.network(state)
    C_z =0
    for letter in state:
        sum_numerator =0
        for letterB in graph.nodes():
            partial_sum =0
            for letterC in graph.nodes():
                if (letter,letterB) in graph.edges() and (letter, letterC) in graph.edges():
                    wA = cube.path(state)[letter][letterB]*0.20
                    wB = cube.path(state)[letter][letterC]*0.20
                    wC = cube.path(state)[letterB][letterC]*0.20
                    wB_array = cube.path(state)[letter].values()
                    prod = wA*wB*wC
                    partial_sum = prod + partial_sum
            sum_numerator = partial_sum + sum_numerator
        A_squared = (np.sum(wB_array))**2.0
        A_squared_not = (np.sum([element**2 for element in wB_array]))
        C_z = sum_numerator*(A_squared-A_squared_not)**-1 + C_z
    return C_z




#
#wB = cube.path(solved_state)
#array = wB['A'].values()
#arrayA = [i**2 for i in array]
#print np.sum(array)
#print np.sum(arrayA)
#      
#
#print onnela_clustering(solved_state)
#print onnela_clustering(cube.return_string(op.rotate_bot(solved_state)))
#print onnela_clustering(cube.return_string(op.rotate_top(solved_state)))
#print onnela_clustering(cube.return_string(op.rotate_B(solved_state)))
#with open('State_String_BackUp.txt') as filename:
#    reader =    csv.reader(filename)
#    for row in reader:
#        print onnela_clustering(row)
   

            
            
        



#print cube.path(solved_state)['A']
    

            
            


    

















        
        
        
#for i in os.listdir(os.getcwd()):
#    if i.endswith(".txt"):         
#        #Transform to directed graph
#        with open(i, 'r') as essay:  
#            myfile = essay.read()
#            punctuations = '''.,?!#$%^&*()":;/\><-_+=|'''
#            for every in punctuations:
#                myfile = myfile.replace(every,'')
#            pre_processed= myfile.lower().split()
#            
#        
#            diredges=[]
#            n=-1
#            while n<len(pre_processed)-2:
#                n+=1
#                diredges.append((pre_processed[n],pre_processed[n+1]))
#               
#            dgraph = nx.Graph()
#            dgraph.add_nodes_from(pre_processed)
#            
#            dgraph.add_edges_from(diredges)
#            nodes = dgraph.number_of_nodes()
#            edges = dgraph.number_of_edges()
#            
#            cc = nx.average_clustering(dgraph)
#            print 'This is the average clustering of {}: {:f}'.format(i, cc)
            
            
