from unidecode import unidecode

file_path = "DicAberto.dict"  # Replace this with the path to your file

with open(file_path, "r") as file:
    lines = file.readlines()
palavras = []
for l in lines:
    if (not l[:1] == "\t") and l[:1] !="\n" and "-" not in l and "!" not in l and "." not in l and len(l)>2:
        l = unidecode(l)
        palavras.append(l[:-1])

print(palavras)
with open("dic.txt", "w") as file:
    file.write("\n".join(palavras))      