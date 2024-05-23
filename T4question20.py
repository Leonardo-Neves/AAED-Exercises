import random

def heapRefaz(A, esq, dir):

    i = esq
    j = i * 2 + 1

    aux = A[i]
    while (j <= dir):
    
        if ((j < dir) and (A[j] < A[j + 1])):
            j = j + 1
        if (aux >= A[j]):
            break
        A[i] = A[j]
        i = j
        j = i * 2 + 1
    
    A[i] = aux

    return A

def heapConstroi(A, n):
    esq = int((n / 2) - 1)
    
    while (esq >= 0):
        A = heapRefaz(A, esq, n-1)
        esq = esq - 1

    return A

def heapSort(A, n):
    A = heapConstroi(A, n)

    m = n - 1

    while (m > 0):
        aux = A[m]
        A[m] = A[0]
        A[0] = aux
        m = m - 1
        A = heapRefaz(A, 0, m)

    return A

def pegarMaioresKValores(array, k):
    i = 1

    maiores_valores = []

    while i <= k:
        array = heapConstroi(array, len(array))

        if array[0] not in maiores_valores:
            maiores_valores.append(array[0])
            i = i + 1

        array = array[1:]

    return maiores_valores

n = 20
itens = [random.randint(1, 100) for i in range(0, n)]

k = 10
print('maiores_valores: ', pegarMaioresKValores(itens, k))

        