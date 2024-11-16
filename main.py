import csv_reader

rows = csv_reader.read_csv('C:\\arquivos\\vendas_uc.csv', ';')
for row in rows:
    print(row)