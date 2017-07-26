# -*- coding: utf-8 -*-

class Catalogo():

	def abrirArquivo(self, nome):
		caminhoDaTabela = 't/'+nome+'.txt'
		return caminhoDaTabela

	def leitura(self, nome):
		objeto = self.abrirArquivo(nome)
		with open(objeto) as entrada:
			linhas = entrada.read().splitlines()
		return linhas
		
	def definirArquivo(self, arquivo, index): 
		if arquivo == 'Alunos': # id, curso_id, matricula, nome 
			if index == 'id': 
				return 0 
			elif index == 'curso_id': 
				return 1 
			elif index == 'matricula': 
				return 2 
			else: # index == 'nome': 
				return 3 
		
		if arquivo == 'Disciplinas': # id, nome, curso_id 
			if index == 'id': 
				return 0 
			elif index == 'nome': 
				return 1 
			else: # index == 'curso_id': 
				return 2 

		if arquivo == 'DisciplinaHistorico': # id, aluno_id, disciplina_id, nota, ano, periodo, situacao 
			if index == 'id': 
				return 0 
			elif index == 'aluno_id': 
				return 1 
			elif index == 'disciplina_id': 
				return 2 
			elif index == 'nota': 
				return 3 
			elif index == 'ano': 
				return 4 
			elif index == 'periodo': 
				return 5 
			else: # index == ' situacao': 
				return 6 

		if arquivo == 'Cursos': # id, nome 
			if index == 'id': 
				return 0 
			else: # index == 'nome': 
				return 1 

		if arquivo == 'mergesorted': # id, nome 
			if index == 'id': 
				return 0 
			else: # index == 'nome': 
				return 1 
				
		if arquivo == 'hash': # id, nome 
			if index == 'id': 
				return 0 
			else: # index == 'nome': 
				return 1 
		if arquivo == 'nested': # id, nome 
			if index == 'id': 
				return 0 
			else: # index == 'nome': 
				return 1
		if arquivo == 'selecao': # id, nome 
			if index == 'id': 
				return 0 
			else: # index == 'nome': 
				return 1 
		if arquivo == 'projecao': # id, nome 
			if index == 'id': 
				return 0 
			else: # index == 'nome': 
				return 1 				 						
	
	def definirTamanho(self, nome):
		if nome == 'Alunos':
			tamanho = 2000
		elif nome == 'Cursos':
			tamanho = 7
		elif nome == 'Disciplinas':
			tamanho = 303
		else:
			tamanho = 15000
		return tamanho

	def indiceOrdenado(self, x):
		return {
			'1': 308,
			'2': 581,
			'3': 853, 
			'4': 1153,
			'5': 1452,
			'6': 1721
		}.get(x, 2000)
		
