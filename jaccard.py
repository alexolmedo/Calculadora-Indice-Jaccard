import csv

with open('ZINC_chemicals_test.tsv','rb') as tsvIn:
    tsvIn = csv.reader(tsvIn, delimiter='\t')

    arreglo = []

    for indice, compuesto in enumerate(tsvIn):
        if (indice != 0):
            arreglo.append(compuesto[3])


    for i in range(len(arreglo)):
        for j in range(i, len(arreglo)):
            print "###"+str(i+1)+": "+str(arreglo[i])+" ###"+str(j+1)+": "+str(arreglo[j])