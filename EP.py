#
import os
import subprocess
import operator
import shutil
import csv
import fileinput


#This lines count the number of files with the .txt 
#extension in the current directory and return it as
#the variable r. This is an example
#of a non supported feature neither for os.system module
#or for subprocess module in a Python version before 
#Python 3
#It can be implemented to use this output directly as a variable
#erasing the string lines in the next code

command='ls *txt | wc -l'
n_files=subprocess.run(command, shell=True, stdout=subprocess.PIPE)
r = print(n_files.stdout)

#This two following lines ask the user (as a string) for the
#number of data files to fit in the current directory and return that
#value as ask_file_num integer variable
#This can be used with the previous command to
#check if the number of .txt files and this string matches.

ask_file_num = int(input("Number of files: "))
print(ask_file_num)

#The following block asks for a number of lines
#to be erased of EVERY data file. This is needed 
#because the data files include a date and time 
#header which write a variable number of lines,
#but it has never been observed to be more 
#than 5 lines.
#Consider that every time this part of the script
#is executed, it will erase the same amount of lines
#each time. However, the string has an option 
#to be valued as zero, skipping the erasing
#as a security feature.
#As a resolution on discussions about this part
#with the team, we conclude to erase about 10 
#lines of every data file to ensure erasing all 
#data junk. This can be optimized looking for the
#number of columns. The header write only 3 
#columns while the useful data is about 6 columns.
#Erase as many lines as the ones having only
#3 columns is a fine solution.
#It was preferred to erase a constant number of lines
#as the beggining of the data is more less arbitrary.

#The name format of every data file is resonador_x.txt
#with x an integer. This can be easily modified
#to match with the future formats if any.



ask_lines_num = int(input("Number lines to be erased: "))
print(ask_lines_num)
if ask_lines_num != 0:

    for file in range(0,ask_file_num):
        subprocess.run('sed -i -e 1,%sd resonador_%s.txt' %(ask_lines_num,file), shell=True)
        subprocess.run('rm resonador_%s.txt-e' %file, shell=True) #comment to keep original files
        print("erased lines from resonador_%s" %file)
    subprocess.run('sed -i -e 1,10d resonador.txt', shell=True)
    print("erased lines")
elif ask_lines_num == 0:    #this allows to skip the erasing, added for safety
    pass


#The following block ask for the number of resonators and create 
#as many directories as number of resonators, copying
#the data files to organize them according
#to the correspondient resonator.
#Also, it consider a shift in the name of each file as 
#the very first data file taken will have the name
#"resonador.txt" and the next one will be named
#"resonador_0.txt", and so on.
#This is an important consideration while 
#modifying the name of data files taken
#directly using LabVIEW 

ask_res_num = int(input("Number of resonators: "))
res=ask_res_num+2
print(ask_res_num)

for i in range(1,res):
    subprocess.run('mkdir resonator%s' %i, shell=True)
    print('resonator%s' %i)
    if i==14:
        subprocess.run('mkdir resonator1', shell=True)
    else:
        pass
for x in range(0,39):
    for i in range (0,res):
        shift = 2
        k = i + x*13
        
        j= (operator.mod(k, 13))+shift
        print('i')
        print(i)
        
        
        print('k')
        print(k)
        
        print('j')
        print(j)
        subprocess.call('cp resonador_%s.txt ./resonator%s' %(k,j), shell=True)
        if j==14:
            subprocess.call('cp resonador_%s.txt ./resonator1' %k, shell=True)
        else:
            pass
subprocess.call('rm -r ./resonator14', shell=True)

#This lines copy the Fitting script into each
#directory with the intention of performing 
#the fit inside each directory.
#Up to the future modifications to keep or erase
#this lines depending on the desired data 
#organization.
#Note to change the path to the programs accordingly.


for alpha in range (1,14):
    subprocess.call('cp /Users/janette/Documents/MKID11WAFER1/Programas/KGOQc.C /Users/janette/Documents/MKID11WAFER1/MKID11WAFER1STW/SweepTempWcopycopy/resonator%s' %alpha, shell=True)
    print ('done copy first')
    subprocess.call('cp /Users/janette/Documents/MKID11WAFER1/Programas/KGOQc.C /Users/janette/Documents/MKID11WAFER1/MKID11WAFER1STW/SweepTempWcopycopy/resonator%s' %alpha, shell=True)
    print ('done copy second')
print ('done copy')

#



subprocess.call('cp /Users/janette/Documents/MKID11WAFER1/Programas/KGOQc.C /Users/janette/Documents/MKID11WAFER1/MKID11WAFER1STW/SweepTempWcopycopy', shell=True)
print ('done copy first')
subprocess.call(' cp /Users/janette/Documents/MKID11WAFER1/Programas/CKGao.C /Users/janette/Documents/MKID11WAFER1/MKID11WAFER1STW/SweepTempWcopycopy', shell=True)
print ('done copy CKGao.C')
subprocess.run('more CKGao.C', shell=True)

#I keep the following commented lines
#as reference to use PyROOT.
#This macro can be found at 
#https://root.cern.ch/pyroot
#
#from ROOT import gROOT, gRandom,TCanvas,TH1F,TFile
#gROOT.Reset()
#froot = TFile("examplepython.root","RECREATE","blank");

#c1 = TCanvas('c1','Example',200,10,700,500)
#hpx = TH1F('hpx','px',100,-4,4)

#for i in xrange(25000):
#    px = gRandom.Gaus()
#    hpx.Fill(px)

#hpx.Draw()
#c1.Update()
#froot.Write();
#froot.cd();
#froot.ls();
#hpx.Write("hpxxx");


#The following lines are the continuos 
#script running on ROOT.
#This line replacement solution was 
#implemented as a way to work around
#the PyROOT issue.
#The name of the .C files are the ones modified 
#to store the relevant data using TTree Class
#

subprocess.run(r'root -l -q .L KGOQc.C', shell=True)

count = 1

for beta in range(2, ask_file_num):
    
    print(ask_file_num)
    
    subprocess.run(r'root -l -q .L CKGao.C', shell=True)
    print(beta)
    gamma=beta-1

    
    lines = open("CKGao.C").read().splitlines()
    if count < 10:
        temp = lines[152][43]
    if count > 9:
        temp = lines[152][43:45]
    if count > 99:
        temp = lines[152][43:46]
    print ("temp = ", temp)
    temp = int(temp) + 1
    temp = str(temp)
    replacer = 'void CKGao(TString nombrefile1= "resonador_' + temp + '.txt"){'
    lines[152] = replacer
    open('CKGao.C','w').write('\n'.join(lines))
    print ("count =",count)
    count += 1


