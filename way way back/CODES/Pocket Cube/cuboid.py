# -*- coding: utf-8 -*-
"""
Created on Sun Mar 15 01:39:05 2015

@author: nelmntrx
"""

import numpy as np
from sympy.combinatorics.permutations import Permutation
import networkx as nx
import string as st
import itertools
import matplotlib.pyplot as plt
import pydot


'''=====BASIC OPERATION======='''

def perm(listahan):
    permute =[]
    for index in range(len(listahan)):
        permute.append(listahan[index-1])     
    return permute #Return only one permutation


"==========================================================="
" ----- ** OPERATIONS  ** -----   "

'''----------rotation side A(90 degrees)----------------'''
def rotate_A(string): 
    array_letter =[]
    for letter in string:
        array_letter.append(letter)
        
    exclude_list = array_letter[:]
    exclude_list[0:4]=perm(array_letter[0]+array_letter[1]+array_letter[3]+array_letter[2])   
    exclude_list[2:4]= perm(exclude_list[2]+exclude_list[3])        

    new_iterations = join(array_letter[4:6]+array_letter[22:24]+array_letter[8:10]+array_letter[6:8])   
    iterated_duo = perm(new_iterations)

    new=[]
    for duo in iterated_duo:
        new.append(list(duo))
     
    exclude_list[4:6]=[element for element in new[0]]
    exclude_list[6:8] = [element for element in new[3]]
    exclude_list[8:10]= [element for element in perm(new[2])]
    exclude_list[22:24] = [element for element in perm(new[1])]
    return exclude_list         

'''------------------rotation side B(90 degrees)-----------------'''


def rotate_B(string): #rotation side B(90 degrees)
    array_letter =[]
    for letter in string:
        array_letter.append(letter)
        
    exclude_list = array_letter[:]   
    exclude_list[16:20]=perm(array_letter[19]+array_letter[16]+array_letter[18]+array_letter[17])

    new_iterations = join(array_letter[10:12]+array_letter[20:22]+array_letter[14:16]+array_letter[12:14])
    iterated_duo = perm(new_iterations)
    new=[]
    for duo in iterated_duo:
        new.append(list(duo))
               
    exclude_list[10:12]=[element for element in new[0]]
    exclude_list[20:22] = [element for element in perm(new[1])]
    exclude_list[14:16]= [element for element in perm(new[2])]
    exclude_list[12:14] = [element for element in new[3]]         
    return exclude_list

'''----------------rotation top (90 degrees)-----------------'''

def rotate_top(string):
    array_letter =[]
    for letter in string:
        array_letter.append(letter)
        
    exclude_list = array_letter[:]
    exclude_list[20:24]=perm(array_letter[23]+array_letter[20]+array_letter[22]+array_letter[21])   


    side_blocks = join(array_letter[9]+array_letter[15]+array_letter[4]+array_letter[10])
    new_iterations = join(array_letter[0:2]+array_letter[18:20])
    team_duo = [new_iterations[0],side_blocks[0], new_iterations[1], side_blocks[1]]
    iterated_duo = perm(team_duo)
#    print team_duo
#    print iterated_duo

    new=[]
    for duo in iterated_duo:
        new.append(list(duo))

               
    exclude_list[0:2]=[element for element in perm(new[0])]
    exclude_list[18:20] = [element for element in perm(new[2])]
    
    exclude_list[4]= new[3][0]
    exclude_list[10]= new[3][1]
    exclude_list[9] = new[1][0]
    exclude_list[15] = new[1][1]
    return exclude_list
    
'''----------rotation bottom (90 degrees)----------------'''

def rotate_bot(string):
    array_letter =[]
    for letter in string:
        array_letter.append(letter)
        
    exclude_list = array_letter[:]
    center = [array_letter[6],array_letter[7],array_letter[13],array_letter[12]]

    exclude_list[6]=perm(center)[0]
    exclude_list[7]=perm(center)[1]
    exclude_list[12]=perm(center)[3]
    exclude_list[13]=perm(center)[2]   


    side_blocks = join(array_letter[8]+array_letter[14]+array_letter[5]+array_letter[11])
    new_iterations = join(perm(array_letter[2:4])+array_letter[16:18])
    team_duo = [new_iterations[0],side_blocks[0], new_iterations[1], side_blocks[1]]
    iterated_duo = perm(team_duo)

    new=[]
    for duo in iterated_duo:
        new.append(list(duo))

    print new         
    exclude_list[2:4]=[element for element in perm(new[0])]
    exclude_list[16:18] = [element for element in perm(new[2])]
    
    exclude_list[5]= new[3][0]
    exclude_list[11]= new[3][1]
    exclude_list[8] = new[1][1]
    exclude_list[14] = new[1][0]
    return exclude_list


'''===================================================================='''



def return_string(array): #connects a list of letters for cube_maker
#    baliktaran = iter(array)
    return ''.join(array)


def cube_maker(string): #returns a graph with nodes and edges that is exactly the same in a pocket cube
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
        
#    labels = {}
#    for node in pocketcube.nodes():
#        labels[node] = node
#
#    pos = nx.random_layout(pocketcube)
#    nx.draw(pocketcube, with_labels=False)
#    nx.draw_networkx_labels(pocketcube, pos, labels, node_size=20, node_color='r' )
#    plt.show()
    return pocketcube

    

 
 
 
 
 
 
 
 
'''=================GARBAGE==================='''

def perm_loop(listahan):
    all_permute=[]
    while len(all_permute)<4:
        all_permute.append(perm(listahan))
        listahan = perm(listahan)
    return all_permute #Return all permutations of 90deg
    
def join(listahan):
    baliktaran = iter(listahan)
    conjoin = [element + next(baliktaran, '') for element in baliktaran]
    return conjoin       
    

def rotate_90a(string):
    array = []
    state_90boom =[]
    state_90panes=[]
    for letter in string:
        array.append(letter)
        
    #For the 1st face of the cube; 
    for boom in perm_loop(array[0:4]):
        exclude_list_boom = array[:] #copy of the original array
        exclude_list_boom[0:4] = boom #Inserts the permutations in the list
        state_90boom.append(exclude_list_boom)
#    return state_90boom

    #For the remaning cuboids that will be affected by the rotation of 90deg at this face
    new_iterations = join(array[4:10]+array[22:24])
    for panes in perm_loop(new_iterations):
        exclude_list_panes = state_90boom[:]
        exclude_list_panes[4:10] = panes[0:3]
        exclude_list_panes[20:22]= panes[3:4]
        state_90panes.append(exclude_list_panes)
    exclude_list_panes 


'''========TEST RUN============='''

solved_cube = 'ABCDEFGHIJKLMNOPQRSTUVWX'
a = rotate_A(solved_cube)
b= rotate_B(return_string(a))
c = rotate_top(return_string(b))
d = rotate_bot(return_string(c))

print 'this is the solved state: ', list(solved_cube)
print ' '
print 'one face: 90 deg: ', a
print '\n'
print 'back rotation of the previous state: ', b
print '\n'
print 'top rotation of the previous state: ', c
print '\n'
print 'base rotation of the previous state: ', d


    
