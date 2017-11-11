import csv

with open('ZINC_chemicals.tsv','rb') as tsvIn:
    tsvIn = csv.reader(tsvIn, delimiter='\t')

    for indice, item in enumerate(tsvIn):
        if (indice != 0):
            print item[3]
