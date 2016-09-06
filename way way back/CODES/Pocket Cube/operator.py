# -*- coding: utf-8 -*-
"""
Created on Tue Mar 17 17:15:26 2015

@author: nelmntrx
"""


import itertools


'''EVERY OPERATION RETURNS AN ARRAY OF STATE'''



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

    new_iterations = ''.join(array_letter[4:6]+array_letter[22:24]+array_letter[8:10]+array_letter[6:8])   
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

    new_iterations = ''.join(array_letter[10:12]+array_letter[20:22]+array_letter[14:16]+array_letter[12:14])
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


    side_blocks = ''.join(array_letter[9]+array_letter[15]+array_letter[4]+array_letter[10])
    new_iterations = ''.join(array_letter[0:2]+array_letter[18:20])
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


    side_blocks = ''.join(array_letter[8]+array_letter[14]+array_letter[5]+array_letter[11])
    new_iterations = ''.join(perm(array_letter[2:4])+array_letter[16:18])
    team_duo = [new_iterations[0],side_blocks[0], new_iterations[1], side_blocks[1]]
    iterated_duo = perm(team_duo)

    new=[]
    for duo in iterated_duo:
        new.append(list(duo))
        
    exclude_list[2:4]=[element for element in perm(new[0])]
    exclude_list[16:18] = [element for element in perm(new[2])]
    
    exclude_list[5]= new[3][0]
    exclude_list[11]= new[3][1]
    exclude_list[8] = new[1][1]
    exclude_list[14] = new[1][0]
    return exclude_list




'''===================================================================='''

#
#
#print rotate_A('ABCDEFGHIJKLMNOPQRTSUVWX')