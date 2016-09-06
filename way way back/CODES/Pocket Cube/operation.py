# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 05:18:47 2015

@author: nelmntrx
"""

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

    rotation_A =[array_letter[4], array_letter[23], array_letter[8], array_letter[6]]
    exclude_list[4]=perm(rotation_A)[0]
    exclude_list[23]=perm(rotation_A)[1]        
    exclude_list[8]=perm(rotation_A)[2]    
    exclude_list[6]=perm(rotation_A)[3]    
    
    rotation_B =[array_letter[5], array_letter[22], array_letter[9], array_letter[7]]
    exclude_list[5]=perm(rotation_B)[0]
    exclude_list[22]=perm(rotation_B)[1]        
    exclude_list[9]=perm(rotation_B)[2]    
    exclude_list[7]=perm(rotation_B)[3] 
    return exclude_list


       

'''------------------rotation side B(90 degrees)-----------------'''


def rotate_B(string): #rotation side B(90 degrees)
    array_letter =[]
    for letter in string:
        array_letter.append(letter)
        
    exclude_list = array_letter[:]   
    exclude_list[16:20]=perm(array_letter[19]+array_letter[16]+array_letter[18]+array_letter[17])
        
    rotation_A =[array_letter[10], array_letter[21], array_letter[14], array_letter[12]]
    exclude_list[10]=perm(rotation_A)[0]
    exclude_list[21]=perm(rotation_A)[1]        
    exclude_list[14]=perm(rotation_A)[2]    
    exclude_list[12]=perm(rotation_A)[3]    
    
    rotation_B =[array_letter[11], array_letter[20], array_letter[15], array_letter[13]]
    exclude_list[11]=perm(rotation_B)[0]
    exclude_list[20]=perm(rotation_B)[1]        
    exclude_list[15]=perm(rotation_B)[2]    
    exclude_list[13]=perm(rotation_B)[3] 
    return exclude_list
    


'''----------------rotation top (90 degrees)-----------------'''

def rotate_top(string):
    array_letter =[]
    for letter in string:
        array_letter.append(letter)
        
    exclude_list = array_letter[:]
    exclude_list[20:24]=perm(array_letter[22]+array_letter[23]+array_letter[21]+array_letter[20])   

    rotation_A =[array_letter[0], array_letter[9], array_letter[19], array_letter[10]]
    exclude_list[0]=perm(rotation_A)[0]
    exclude_list[9]=perm(rotation_A)[1]        
    exclude_list[19]=perm(rotation_A)[2]    
    exclude_list[10]=perm(rotation_A)[3]    
    
    rotation_B =[array_letter[1], array_letter[15], array_letter[18], array_letter[4]]
    exclude_list[1]=perm(rotation_B)[0]
    exclude_list[15]=perm(rotation_B)[1]        
    exclude_list[18]=perm(rotation_B)[2]    
    exclude_list[4]=perm(rotation_B)[3] 
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

    rotation_A =[array_letter[2], array_letter[8], array_letter[17], array_letter[11]]
    exclude_list[2]=perm(rotation_A)[0]
    exclude_list[8]=perm(rotation_A)[1]        
    exclude_list[17]=perm(rotation_A)[2]    
    exclude_list[11]=perm(rotation_A)[3]    
    
    rotation_B =[array_letter[3], array_letter[14], array_letter[16], array_letter[5]]
    exclude_list[3]=perm(rotation_B)[0]
    exclude_list[14]=perm(rotation_B)[1]        
    exclude_list[16]=perm(rotation_B)[2]    
    exclude_list[5]=perm(rotation_B)[3] 
    return exclude_list    


'''===================================================================='''
