import csv
import collections

with open('ZINC_chemicals.tsv','rb') as tsvIn, open('solution_python.tsv', 'wb') as tsvOut:
    tsvIn = csv.reader(tsvIn, delimiter='\t')

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
    tsvOut.write("compound_a\tcompound_b\tvalue\n")

    for i in range(len(arregloCompuestos)):
        for j in range(i+1, len(arregloCompuestos)):
            elementosComunes = 0
            for caracter in arregloCompuestos[i][1]:
                if (arregloCompuestos[j][1].has_key(caracter)):
                    elementosComunes += min (arregloCompuestos[i][1][caracter], arregloCompuestos[j][1][caracter])
            # Calculo y escritura a archivo del indice de Jaccard
            indiceJaccard = float(elementosComunes) / (arregloCompuestos[i][2] + arregloCompuestos[j][2] - elementosComunes)
            tsvOut.write(arregloCompuestos[i][0] + "\t" + arregloCompuestos[j][0] + "\t" + "{0:.2f}".format(indiceJaccard) + "\n")

