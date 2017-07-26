from catalogo import *

# -*- coding: utf-8 -*-

class Pagina():
    def __init__(self, externa = False):
        self.chaves = []
        self.paginasFilhas = []
        self.externa = externa

    def __str__(self):
        if self.externa:
            return "Pagina Externa com {0} chaves\n\tChaves:{1}\n\tFilhas:{2}\n".format(len(self.chaves), self.chaves, self.paginasFilhas)
        else:
            return "Pagina Interna com {0} chaves, {1} filhas\n\tChaves:{2}\n\n".format(len(self.chaves), len(self.paginasFilhas), self.chaves, self.paginasFilhas)

class ArvoreB():
    def __init__(self, ordem):
        self.ordem = ordem #(Ordem >> 4)
        self.raiz = Pagina(externa = True)

    def inserirChave(self, chave):
        #chave = self.converteDeHexa(str(key))
        r = self.raiz
        if len(r.chaves) == (2*self.ordem) - 1: #Pagina Cheia >> Split
            s = Pagina()
            self.raiz = s
            s.paginasFilhas.insert(0, r) #Raiz eh agora (no index 0) filha da nova raiz s
            self.split(s, 0)            
            self.inserir(s, chave)
        else:
            self.inserir(r, chave)
    
    def inserir(self, pagina, chave):
        #chave = self.converteDeHexa(str(key))
        i = len(pagina.chaves) - 1
        if pagina.externa:
            #Insere a chave
            pagina.chaves.append(0)
            while i >= 0 and chave < pagina.chaves[i]:
                pagina.chaves[i+1] = pagina.chaves[i]
                i -= 1
            pagina.chaves[i+1] = chave
        else:
            #Insere uma pagina filha
            while i >= 0 and chave < pagina.chaves[i]:
                i -= 1
            i += 1
            if len(pagina.paginasFilhas[i].chaves) == (2*self.ordem) - 1:
                self.split(pagina, i)
                if chave > pagina.chaves[i]:
                    i += 1
            self.inserir(pagina.paginasFilhas[i], chave)       

    def split(self, pagina, i):
        ordem = self.ordem
        y = pagina.paginasFilhas[i]
        z = Pagina(externa = y.externa)
        
        pagina.paginasFilhas.insert(i + 1, z)
        pagina.chaves.insert(i, y.chaves[ordem - 1])
        
        z.chaves = y.chaves[ordem:(2*ordem - 1)]
        y.chaves = y.chaves[0:(ordem - 1)]
        
        if not y.externa:
            z.paginasFilhas = y.paginasFilhas[ordem:(2*ordem)]
            y.paginasFilhas = y.paginasFilhas[0:(ordem - 1)]

    def buscarChave(self, chave, pagina = None, paginaPai = None, indexChaveReferencia = None):
        #chave = self.converteDeHexa(str(key))
        if isinstance(pagina, Pagina):
            i = 0
            while i < len(pagina.chaves) and chave > pagina.chaves[i]:#Procurando index da chave
                i += 1
            if i < len(pagina.chaves) and chave == pagina.chaves[i]:#Se encontrar
                return (pagina, i, paginaPai, indexChaveReferencia)
            elif pagina.externa: #Chave nao encontrada e chegamos na externa
                return None
            else: #Nao eh externa, procura-se nas filhas
                return self.buscarChave(chave, pagina = pagina.paginasFilhas[i], paginaPai = pagina, indexChaveReferencia = i)
        else: 
            return self.buscarChave(chave, self.raiz)
    

    def __str__(self):
        r = self.raiz
        return r.__str__() + '\n'.join([filha.__str__() for filha in r.paginasFilhas])
         
def main():
   
    a = ArvoreB(4)
    c = Catalogo()

    historico = 'DisciplinaHistorico'
    periodo = 'periodo'
    ano = 'ano'
    idAluno = 'aluno_id'    
    
    tabelaHistorico = c.leitura(historico)
    for j in tabelaHistorico:
        i = j.split("\t")
        a.inserirChave(i[c.definirArquivo(historico, idAluno)])
        a.inserirChave(i[c.definirArquivo(historico, ano)])
        a.inserirChave(i[c.definirArquivo(historico, periodo)])
        print(a.__str__())
    if a.buscarChave(2007) != None:
        print("Chave encontrada!")
        

    #for i in tabelaHistorico:
        
    

    

    

main()