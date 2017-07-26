from hashTable import *

# -*- coding: utf-8 -*-

class Juncao():

	
	def hashJoin(self, nome1, nome2, index):
		
		resultado = []
		c = Catalogo() 

		tabela1 = c.leitura(nome1) 
		tabela2 = c.leitura(nome2) 


		hashing = HashTable(len(tabela1))
		
		file = open("t/hash.txt","w")

		for s in tabela2:
			linha = s.split("\t")
			hashing.insereHash(s)
		for i in tabela1:
			linha = i.split("\t")
			resultado = hashing.procuraHash(linha[index])
			if resultado is not None:
				file.write(resultado +"\t"+ "\t".join(linha) + "\n")

	def nestedLoopJoin(self, nome1, nome2, index1, index2):

		c = Catalogo() 

		tabela1 = c.leitura(nome1) 
		
		tabela2 = c.leitura(nome2) 

		file = open("t/nested.txt","w")
		

		for s in tabela2:
			linha1 = s.split("\t")
			for r in tabela1:
				linha2 = r.split("\t")
				if linha1[index1] == linha2[index2]:						
					file.write("\t".join(linha1) +"\t"+ "\t".join(linha2) + "\n")

	def sortMergeJoin(self, nome1, nome2, index1, index2, ordernado = True):
			
		c = Catalogo() 

		tabela1 = c.leitura(nome1) 
		tabela2 = c.leitura(nome2) 

		file = open("t/mergesorted.txt","w")
			
		if ordernado is False: 
			return None
		
		contador = 0
		i = 1

		for s in tabela2:
			s = tabela2[i -1]
			linha1 = s.split("\t")
			while contador < c.indiceOrdenado(str(i)):
				r = tabela1[contador]
				linha2 = r.split("\t")
				file.write("\t".join(linha1) +"\t"+ "\t".join(linha2) + "\n")
				contador += 1
			i +=1	
