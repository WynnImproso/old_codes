# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 00:45:48 2015

@author: nelmntrx
"""

import networkx as nx
import matplotlib.pyplot as plt
import os
import csv
import pydot

from networkx.utils import open_file, make_str

#def make_network():
for i in os.listdir(os.getcwd()):
    if i.endswith(".txt"): 
        with open(i, 'r') as essay:
            myfile = essay.read()
            punctuations = '''.,?!#$%^&*()":;/\><-_+=|'''
            for every in punctuations:
                myfile = myfile.replace(every,'')
            pre_processed= myfile.lower().split()
            
        diredges=[]
        n=-1
        while n<len(pre_processed)-2:
            n+=1
            diredges.append((pre_processed[n],pre_processed[n+1]))
           
        udgraph = nx.Graph()
        udgraph.add_nodes_from(pre_processed)
        
        udgraph.add_edges_from(diredges)
        nodes = udgraph.number_of_nodes()
        edges = udgraph.number_of_edges()
        label = 'network'+i
        label = label.replace('.txt', '')
        nx.write_dot(udgraph, label)
        
        
        
    




#
#
#graph = nx.erdos_renyi_graph(500,2)
#nx.write_dot(graph,'Erdos Reyni')
#
##
##new = nx.read_dot('Erdos Reyni')
##print nx.average_clustering(new)
#
#print nx.average_clustering(graph)