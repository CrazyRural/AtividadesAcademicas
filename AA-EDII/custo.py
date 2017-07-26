from catalogo import *

# -*- coding: utf-8 -*-


class Custo():


	def calculaCusto(self, nome1, nome2, quantidadeJoin):

		c = Catalogo()

		tamanho1 = c.definirTamanho(nome1)
		tamanho2 = c.definirTamanho(nome2)

		custoTotal = [[10000000000000000000 for col in range(2)] for row in range(quantidadeJoin)]

		k = 0

		for i in range(0, quantidadeJoin):
			
			for j in range(1,3):
				
				custo = 0

				if j == 1:
					custo = tamanho1 * tamanho2
				elif j == 2:
					custo = tamanho1 + tamanho2
				else:
					custo = tamanho1 + tamanho2 + tamanho1*log10(tamanho1) + tamanho2*log10(tamanho2)

				if custoTotal[i][k] > custo:
					custoTotal[i][k] = custo
					custoTotal[i][k+1] = j						
		return custoTotal		