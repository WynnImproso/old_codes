# -*- coding: utf-8 -*-
"""
Created on Tue Mar 17 17:18:46 2015

@author: nelmntrx
"""

'''MISCELLANEOUS FUNCTIONS for looping'''

import numpy as np
from sympy.combinatorics.permutations import Permutation
import networkx as nx
import string as st
import itertools
import matplotlib.pyplot as plt



def return_string(array): #connects a list of letters for cube_maker
#    baliktaran = iter(array)
    return ''.join(array)


def path(string): #returns a graph with nodes and edges that is exactly the same in a pocket cube
    pocketcube = nx.Graph()
    for letter in string:
        pocketcube.add_node(letter)
    edges = [(string[0],string[22]),(string[0],string[1]), (string[0],string[2]),
    (string[0],string[4]), (string[1],string[23]), (string[1],string[9]),
    (string[1],string[3]),(string[2],string[3]),(string[3],string[8]),
    (string[3],string[7]),(string[2],string[5]),(string[2],string[6]),
    (string[4],string[22]),(string[4],string[10]),(string[5],string[11]),
    (string[5],string[6]),(string[6],string[7]),(string[6],string[12]),
    (string[7],string[8]),(string[7],string[13]),(string[8],string[9]),
    (string[8],string[14]),(string[9],string[15]),(string[9],string[23]),
    (string[10],string[20]),(string[10],string[11]),(string[10],string[18]),
    (string[11],string[16]),(string[11],string[12]),(string[12],string[13]),
    (string[12],string[16]),(string[13],string[14]),
    (string[13],string[17]),(string[14],string[15]),(string[14],string[17]),
    (string[15],string[21]),(string[15],string[19]),(string[16],string[18]),
    (string[16],string[17]),(string[17],string[19]),(string[19],string[21]),
    (string[18],string[20]),(string[20],string[21]),(string[20],string[22]),
    (string[21],string[23]),(string[22],string[23]), (string[18], string[19])]
    pocketcube.add_edges_from(edges)
        

    return nx.shortest_path_length(pocketcube)

def show(string):
    pocketcube = nx.Graph()
    for letter in string:
        pocketcube.add_node(letter)
    edges = [(string[0],string[22]),(string[0],string[1]), (string[0],string[3]),
    (string[0],string[4]), (string[1],string[23]), (string[1],string[9]),
    (string[1],string[2]),(string[2],string[3]),(string[2],string[8]),
    (string[2],string[7]),(string[3],string[5]),(string[3],string[6]),
    (string[4],string[22]),(string[4],string[10]),(string[5],string[11]),
    (string[5],string[6]),(string[6],string[7]),(string[6],string[12]),
    (string[7],string[8]),(string[7],string[13]),(string[8],string[9]),
    (string[8],string[14]),(string[9],string[15]),(string[9],string[23]),
    (string[10],string[10]),(string[10],string[11]),(string[10],string[18]),
    (string[11],string[16]),(string[11],string[12]),(string[12],string[13]),
    (string[12],string[13]),(string[12],string[16]),(string[13],string[14]),
    (string[13],string[17]),(string[14],string[15]),(string[14],string[17]),
    (string[15],string[21]),(string[15],string[19]),(string[16],string[18]),
    (string[16],string[17]),(string[17],string[19]),(string[19],string[21]),
    (string[18],string[20]),(string[20],string[21]),(string[20],string[22]),
    (string[21],string[23]),(string[22],string[23]), (string[18], string[19])]
    pocketcube.add_edges_from(edges)

    labels = {}
    for node in pocketcube.nodes():
        labels[node] = node

    pos = nx.random_layout(pocketcube)
    nx.draw(pocketcube, with_labels=False)
    nx.draw_networkx_labels(pocketcube, pos, labels, node_size=20, node_color='r' )
    plt.show()
    return "This is state: %s" %string
    
    
def network(string):
    pocketcube = nx.Graph()
    for letterA in string:
        pocketcube.add_node(letterA)
        listahan = path(string)[letterA]
        for letterB in listahan:
            if letterA != letterB:
                pocketcube.add_edge(letterA, letterB, weight = listahan[letterB])
    return pocketcube

#solved_state = 'ABCDEFGHIJKLMNOPQRSTUVWX'
#
#graph = network(solved_state)
##for edge in graph.edges():
##    print edge
##    print nx.from_edgelist(graph)
#print nx.algebraic_connectivity(graph)
#print nx.average_clustering(graph)
#print nx.transitivity(graph)
#print nx.diameter(graph)




#    label = 'network({})'.format(string)
#    return nx.write_dot(pocketcube, label)    
    
    
    
#    labels = {}
#    for node in pocketcube.nodes():
#        labels[node] = node
#    edge_labels = dict([((u,v), d['weight']) for u,v,d in pocketcube.edges(data=True)])
#    
#    pos = nx.spring_layout(pocketcube)
#    nx.draw(pocketcube, with_labels=False,node_size=10)
#    nx.draw_networkx_labels(pocketcube, pos, font_size=13,font_family='sans-serif')
#    nx.draw_networkx_edge_labels(pocketcube, pos,edge_labels=edge_labels)
#    
#    
#    pylab.show()
#state = 'ABCDEFGHIJKLMNOPQRSTUVWX'
#graph = network(state)
#label = 'network({})'.format(state)
#print nx.write_dot(graph,label)