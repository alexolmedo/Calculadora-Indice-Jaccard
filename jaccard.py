import csv
import collections
from multiprocessing import Pool
import os
import time

def calculojaccard (i):
    linea = ''
    global arregloCompuestos
    for j in range(i+1, len(arregloCompuestos)):
        elementosComunes = 0
        for caracter in arregloCompuestos[i][1]:
            if (arregloCompuestos[j][1].has_key(caracter)):
                elementosComunes += min (arregloCompuestos[i][1][caracter], arregloCompuestos[j][1][caracter])
        # Calculo del indice de Jaccard
        indiceJaccard = float(elementosComunes) / (arregloCompuestos[i][2] + arregloCompuestos[j][2] - elementosComunes)
        linea += arregloCompuestos[i][0] + "\t" + arregloCompuestos[j][0] + "\t" + "{0:.2f}".format(indiceJaccard) + "\n"
    return linea

with open('ZINC_chemicals_test.tsv','rb') as tsvIn:
    # Crear un archivo vacio de soluciones
    open('solution_jaccard.tsv', 'w').close()

    tsvIn = csv.reader(tsvIn, delimiter='\t')
    inicio = time.time()

    global arregloCompuestos
    arregloCompuestos = []

    for indice, compuesto in enumerate(tsvIn):
        # Ignorar primera linea del archivo, agregar diccionario con la frecuencia de todos los caracteres al arreglo
        if indice != 0:
            arregloCompuestos.append([compuesto[1], collections.Counter(compuesto[3])])

    for i in range(len(arregloCompuestos)):

        # Remover simbolos y otros caracteres del diccionario
        for simbolo in ['[', ']', '(', ')', '-', '+', '=', '/']:
            del arregloCompuestos[i][1][simbolo]

        # Agregar el numero total de elementos al arreglo
        numElementos = 0
        for caracter in arregloCompuestos[i][1]:
            numElementos += arregloCompuestos[i][1][caracter]
        arregloCompuestos[i].append(numElementos)

    # Escribir etiquetas de cada columna
    tsvOut = open('solution_jaccard.tsv', 'ab')
    tsvOut.write("compound_a\tcompound_b\tvalue\n")

    pool = Pool()
    for resultado in pool.map(calculojaccard, range(len(arregloCompuestos))):
        tsvOut.write(resultado)

    fin = time.time()
    print fin - inicio
