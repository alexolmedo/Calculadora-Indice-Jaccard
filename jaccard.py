import csv

with open('ZINC_chemicals.tsv','rb') as tsvIn, open('solution_jaccard.tsv', 'wb') as tsvOut:
    tsvIn = csv.reader(tsvIn, delimiter='\t')

    arreglo = []

    for indice, compuesto in enumerate(tsvIn):
        if indice != 0:
            arreglo.append([compuesto[1], compuesto[3]])

    tsvOut.write("compound_a\tcompound_b\tvalue\n")

    for i in range(len(arreglo)):
        for j in range(i+1, len(arreglo)):
            tsvOut.write(arreglo[i][0]+"\t"+arreglo[j][0]+"\t"+str(0.0)+"\n")
