# -*- coding: utf-8 -*-
"""
Created on Tue Mar 17 17:20:08 2015

@author: nelmntrx
"""
import cube as cube
import operator as operate

import operator as operator 
import networkx as nx
import string as st
import itertools
import matplotlib.pyplot as plt
import pylab


'''This algorithm makes the coresspoding weighted graph from a state of a pocketcube'''
solved_state = 'ABCDEFGHIJKLMNOPQRSTUVWX'


def network(string):
    pocketcube = nx.Graph()
        
    
    for letterA in solved_state:
        pocketcube.add_node(letterA)
    edges = pocketcube.edges()
    listahan = cube.path(solved_state)[letterA]
#        for letterB in listahan:
#            pair = (letterA, letterB)
        
    pocketcube.add_weighted_edges_from(edges)
    return pocketcube
    #print pocketcube.edges()
#    
#    labels = {}
#    for node in pocketcube.nodes():
#        labels[node] = node
#    edge_labels = dict([((u,v), d['weight']) for u,v,d in pocketcube.edges(data=True)])
    
#    pos = nx.spring_layout(pocketcube)
#    nx.draw(pocketcube, with_labels=False,node_size=10)
#    nx.draw_networkx_labels(pocketcube, pos, font_size=13,font_family='sans-serif')
#    nx.draw_networkx_edge_labels(pocketcube, pos,edge_labels=edge_labels)
#    
#    
#    pylab.show()

