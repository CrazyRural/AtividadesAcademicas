from operacoes import *
from custo import *

# -*- coding: utf-8 -*-

class Main():

	#Resolvendo primeira query
	def query1(self, curso):

		c = Catalogo()
		j = Juncao()
		o = Operacoes() 
		cc = Custo()

		j.sortMergeJoin('alunos', 'Cursos', 'curso_id', 'id')
		o.selecao('mergesorted', 1, curso)
		o.projecao('selecao', 4, 5)


		custo = cc.calculaCusto('Alunos', 'Cursos',1) 

		print("Custo total: "+ str(custo[0][0]))

	def query2(self, matricula):	
		c = Catalogo()
		j = Juncao()
		o = Operacoes() 
		cc = Custo()

		o.selecao('DisciplinaHistorico', c.definirArquivo('DisciplinaHistorico', 'nota'), '10')
		j.nestedLoopJoin('Disciplinas','selecao', 2, 0)
		j.hashJoin('Alunos', 'nested', 1)
		o.selecao('hash', 12, matricula)
		o.projecao('selecao', 8, 3)

		numeroDeJoin = 2
		custo = cc.calculaCusto('DisciplinaHistorico', 'Disciplinas', 1)
		custo += cc.calculaCusto('Alunos', 'Disciplinas', 1)

		print("Custo total: "+ str(custo[0][0]))
	
	def query3(self, matricula, ano, periodo):
		c = Catalogo()
		j = Juncao()
		o = Operacoes() 
		cc = Custo()

		o.selecao('Alunos', 2, matricula)
		j.nestedLoopJoin('selecao', 'DisciplinaHistorico', 1, 0)
		j.nestedLoopJoin('nested', 'Disciplinas', 0, 2)
		o.selecao('nested', 7, ano)
		o.selecao('selecao', 6, periodo)
		o.projecao('selecao', 1, 6)

		custo = cc.calculaCusto('DisciplinaHistorico', 'Alunos', 1)
		custo += cc.calculaCusto('Alunos', 'Disciplinas', 1)

		print("Custo total: "+ str(custo[0][0]))

	def boletim(self, nome):
		c = Catalogo()
		j = Juncao()
		o = Operacoes() 
		cc = Custo()

		o.selecao('Alunos', 3, nome)
		j.hashJoin('selecao', 'DisciplinaHistorico', 1)
		j.nestedLoopJoin('hash', 'Disciplinas', 0, 2)
		o.projecaoBoletim('nested', 1, 6, 9, 8, 7)

		numeroDeJoin = 1

		custo = cc.calculaCusto('Alunos', 'DisciplinaHistorico', 1)

		print("Custo total: "+ str(custo[0][0]))

def main():
	m = Main()

	#m.query1('DIREITO')
	#m.query2('2003713902')
	#m.query3('2003713902', '2010', '7')
	m.boletim('LARA GOMES')


main()	
