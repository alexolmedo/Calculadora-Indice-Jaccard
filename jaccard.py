import csv
import collections
import multiprocessing


def calculojaccard (hilo, numHilos):
    global arregloCompuestos
    for i in range(hilo, len(arregloCompuestos), numHilos):
        for j in range(i+1, len(arregloCompuestos)):
            elementosComunes = 0
            for caracter in arregloCompuestos[i][1]:
                if (arregloCompuestos[j][1].has_key(caracter)):
                    elementosComunes += min (arregloCompuestos[i][1][caracter], arregloCompuestos[j][1][caracter])
            # Calculo y escritura a archivo del indice de Jaccard
            indiceJaccard = float(elementosComunes) / (arregloCompuestos[i][2] + arregloCompuestos[j][2] - elementosComunes)
            with open('solution_python.tsv', 'ab') as tsvOut:
                tsvOut.write(arregloCompuestos[i][0] + "\t" + arregloCompuestos[j][0] + "\t" + "{0:.2f}".format(indiceJaccard) + "\n")


with open('ZINC_chemicals.tsv','rb') as tsvIn:
    tsvIn = csv.reader(tsvIn, delimiter='\t')
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
    with open('solution_python.tsv', 'wb') as tsvOut:
        tsvOut.write("compound_a\tcompound_b\tvalue\n")

    nucleos = multiprocessing.cpu_count()
    procesos = []

    for nucleo in range(nucleos):
        proceso = multiprocessing.Process(target=calculojaccard, args=(nucleo, nucleos))
        procesos.append(proceso)
        procesos[-1].start()

    for proceso in procesos:
        proceso.join()
