from juncao import *

# -*- coding: utf-8 -*-

class Operacoes():
	
	def selecao(self, nome, index, arg):
		c = Catalogo()

		tabela = c.leitura(nome)

		file = open("t/selecao.txt", "w")

		for s in tabela:
			linha1 = s.split("\t")
			if linha1[index] == arg:
				file.write("\t".join(linha1) + "\n")

	def projecao(self, nome, index , outroIndex):			

		c = Catalogo()

		tabela = c.leitura(nome)

		file = open("t/projecao.txt", "w")

		for s in tabela:
			linha1 = s.split("\t")
			file.write(linha1[index] +"\t"+  linha1[outroIndex] + "\n") 

	def projecaoBoletim(self, nome, index , index1, index2, index3, index4):			

		c = Catalogo()

		tabela = c.leitura(nome)

		file = open("t/boletim.txt", "w")

		for s in tabela:
			linha1 = s.split("\t")
			file.write(linha1[index] +"\t"+  linha1[index1]+"\t"+  linha1[index2]+"\t"+  linha1[index3]+"\t"+  linha1[index4] + "\n") 		
		