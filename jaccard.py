import csv
import collections

with open('ZINC_chemicals.tsv','rb') as tsvIn, open('solution_jaccard.tsv', 'wb') as tsvOut:
    tsvIn = csv.reader(tsvIn, delimiter='\t')

    arreglo = []

    for indice, compuesto in enumerate(tsvIn):
        if indice != 0:
            arreglo.append([compuesto[1], collections.Counter(compuesto[3])])


    for i in range(len(arreglo)):
        numElementos = 0
        # Remover simbolos y otros caracteres
        for simbolo in ['[',']','(',')','-','+','=','/']:
            del arreglo[i][1][simbolo]

        # Agregar el numero total de elementos
        for caracter in arreglo[i][1]:
            numElementos+=arreglo[i][1][caracter]
        arreglo[i].append(numElementos)

    for i in range(len(arreglo)):
        for j in range(i+1, len(arreglo)):
            elementosComunes = 0
            for caracter in arreglo[i][1]:
                if (arreglo[j][1].has_key(caracter)):
                    elementosComunes += min (arreglo[i][1][caracter],arreglo[j][1][caracter])
            tsvOut.write(arreglo[i][0] + "\t" + arreglo[j][0] + "\t" + "{0:.2f}".format(float(elementosComunes) / (arreglo[i][2]+arreglo[j][2] - elementosComunes)) + "\n")

