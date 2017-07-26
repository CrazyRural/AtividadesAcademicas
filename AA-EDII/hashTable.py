from catalogo import *

# -*- coding: utf-8 -*-

class HashTable():

	def __init__(self, i):
		self.tamanho = i
		self.elementos = [[] for _ in range(i)]

	def dispersao(self, chaveEntrada):
		return self.converteDeHexa(chaveEntrada)%self.tamanho

	def insereHash(self, dados):
		posicao = self.dispersao(dados[0])
		self.elementos[posicao].append(dados)
		return self.elementos


	def procuraHash(self,procura):
			
		posicao = self.dispersao(procura)
		
		if self.elementos[posicao] is None:
			return None
		else:
			tam = len(self.elementos[posicao])
			for a in self.elementos[posicao]:
				if procura == a[0]:
					return a

	def troca(self, x):
		return {
			'0': 0,
			'1': 1,
			'2': 2,
			'3': 3,
			'4': 4,
			'5': 5,
			'6': 6,
			'7': 7,
			'8': 8,
			'9': 9,
			'a': 10,
			'b': 11,
			'c': 12,
			'd': 13,
			'e': 14,
			'f': 15
		}.get(x, -1)
	
	def converteDeHexa(self, dados):
		dado = dados.split("-")
		valor = 0
		for i in range(0, len(dado)):
			for j in range(0, len(dado[i])):
				valor += self.troca(dado[i][j])
		return valor		
