#GABRIELA COELHO MIRANDA
#12221EBI001
#TRABALHO 8 - CAÇA PALAVRAS

def funcao(palavra, matriz, linhas, colunas):#função que calculará a quantidade de ocorrencias de cada palavra
    oc = 0#inicializado a variavel de ocorrencias de palavras
    #verificando na horizontal 
    i = 0#inicializado a variavel
    while i < linhas:#percorre todas as linhas - 1 para ficar dentro da matriz
        j = 0
        while j < colunas - len(palavra) + 1:#verifica se tem uma possibilidade de palavra em cada linha, limitando para que aja apenas a posição possivel pra ter a palavra 
            k = 0
            while k < len(palavra) and (matriz[i][j + k].lower() == palavra[k] or matriz[i][j + k] == '*'):#verifica letra por letra da palavra com as letras da matriz
                k = k + 1#incrementando 
            if k == len(palavra):#se k for igual ao tamanho da palavra 
                oc= oc +  1# vai incrementar a ocorrencia da palavra 
                k = 0#voltando a variavel k 
                while k < len(palavra):# se o k for menor que o tamanho da palavra procurada, utilizamos outro loop para percorrer novamente as letras da palavra e, se a letra na matriz não for '*',vira maiúscula para considerar como uma letra da palavra.
                    if matriz[i][j + k] != '*':#considera * como parte da palavra
                        matriz[i][j + k] = matriz[i][j + k].upper()#transforma as letras em letras maiusculas 
                    k = k +1#incrementando para percorrer as letras da palavra que está sendo procurada na matriz
            j = j +1#incrementando para percorrer as colunas
        i = i +1#incrementando para percorrer as linhas 

    #verificando na vertical
    i = 0#inicializado a variavel
    while i < linhas - len(palavra) + 1:#verifica se tem uma possibilidade de palavra em cada coluna, limitando para que aja apenas a posição possivel pra ter a palavra
        j = 0
        while j < colunas:#percorre as colunas da matriz 
            k = 0
            while k < len(palavra) and (matriz[i + k][j].lower() == palavra[k] or matriz[i + k][j] == '*'):#verifica se tem a palavra com as letras da matriz vertical
                k = k +1
            if k == len(palavra):
                oc = oc +1#incrementando a ocorrencia se houver a palavra na matriz
                k = 0
                while k < len(palavra):#Percorre as letras da palavra e as torna maiúsculas para considerá-las
                    if matriz[i + k][j] != '*':#considera * como parte da palavra 
                        matriz[i + k][j] = matriz[i + k][j].upper()#transforma as letras em letras maiusculas 
                    k = k + 1#incrementando para percorrer as letras da palavra que está sendo procurada na matriz
            j = j + 1#incrementando para percorrer as colunas
        i=i+1#incrementando para percorrer as linhas

    #verificando na diagonal- de cima para direita
    i = 0#percorre as linhas na diagonal
    while i < linhas - len(palavra) + 1:
        j = 0
        while j < colunas - len(palavra) + 1:#percorre as colunas onde a palavra caber no sentido da diagonal
            k = 0
            while k < len(palavra) and (matriz[i + k][j + k].lower() == palavra[k] or matriz[i + k][j + k] == '*'):#compara a palavra com as letras na diagonal superior direita.
                k += 1
            if k == len(palavra):
                oc = oc + 1#incrementando a ocorrencia se houver a palavra na matriz
                k = 0
                while k < len(palavra):#Percorre as letras da palavra e as torna maiúsculas para considerá-las
                    if matriz[i + k][j + k] != '*':#considera * como parte da palavra
                        matriz[i + k][j + k] = matriz[i + k][j + k].upper()
                    k = k +1#incrementando para percorrer as letras da palavra que está sendo procurada na matriz
            j = j +1#incrementando para percorrer as colunas
        i = i + 1#incrementando para percorrer as linhas

    #verificando na diagonal- de baixo para a direito
    i = len(palavra) - 1#percorre as linhas na diagonal
    while i < linhas:
        j = 0
        while j < colunas - len(palavra) + 1:#percorre as colunas onde a palavra caber no sentido da diagonal
            k = 0
            while k < len(palavra) and (matriz[i - k][j + k].lower() == palavra[k] or matriz[i - k][j + k] == '*'):#compara a palavra com as letras na diagonal - de baixo para a direito
                k = k +1
            if k == len(palavra):
                oc = oc +1#incrementando a ocorrencia se houver a palavra na matriz
                k = 0
                while k < len(palavra):#Percorre as letras da palavra e as torna maiúsculas para considerá-las
                    if matriz[i - k][j + k] != '*':#considera * como parte da palavra
                        matriz[i - k][j + k] = matriz[i - k][j + k].upper()
                    k = k +1#incrementando para percorrer as letras da palavra que está sendo procurada na matriz
            j = j +1#incrementando para percorrer as colunas 
        i = i +1#incrementando para percorrer as linhas

    return oc#retornando o valores das ocorrencias de cada palavra para resultados 

def resultados(listap, lista, linhas, colunas):#função de impressão como solicitado no exercicio
    print("----------------------------------------")
    print("Lista de Palavras")
    print("----------------------------------------")

    for palavra in listap:
        oc = funcao(palavra, lista, linhas, colunas)#chamando a função que calcula quantas ocorrencias teve de cada palavra 
        print(f"Palavra: {palavra}")#palavra procurada
        print(f"Ocorrencias: {oc}")#numero de vezes que a palavra se encontra na matriz 
        print("----------------------------------------")
        

def main():#função principal
    linhas = int(input())#indica o número de linhas da grade
    colunas = int(input())#indica o número de colunas da grade
    lista = []#lista vazia para adicionar os caracter da "matriz"

    if 2 <= linhas <= 100 and 2 <= colunas <= 100:#condição do exercicio
        for i in range(linhas):#cada linha de caracter vai ser adicionado em uma lista 
            x = [str(x) for x in input().split()]
            lista.append(x)#adicionando na lista

    N = int(input())#indica a quantidade de palavras que devem ser buscadas
    listap = []# as palavras que forem buscadas vai ser adicionado a esta lista
    if 1 <= N <= 10:#condição do exercicio
        i = 0#inicializando variável
        while i < N:#enquanto isso or verdadeiro
            palavras = input().lower()# palavras que devem ser procuradas e convertidas para letras minúsculas
            listap.append(palavras)#adicionando as palavras na lista 
            i = i+ 1#incrementando
    resultados(listap, lista, linhas, colunas)#chamando a função que irá imprimir os resultados com parametros 

    for linha in lista:
        print(' '.join(linha))#imprime a matriz original com as palavras em maiúsculas encontradas 
main()#chamando a função principal 



