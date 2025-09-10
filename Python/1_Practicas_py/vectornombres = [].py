vectornombres = []

cantpersonas = int(input("Ingrese la cantida de personas(maximo 20): "))

if cantpersonas <= 20:
    for i in range (cantpersonas):
        nombre = input(f"Ingrese el nombre {i+1}: ")

        if i == 0:
            vectornombres.append(nombre)
        else:
            if nombre in vectornombres:
                print("Nombre repetido, no se agrega.")
            else:
                vectornombres.append(nombre)
else:
    print ("La cantidad supera el limite de 20 ")

buscarnombres = input("\nIngrese el nombre que desea buscar: ")

if buscarnombres in vectornombres:
    posicion = vectornombres.index(buscarnombres)
    print (f"Nombre encontrado en la posicion : {posicion}")
else:
    print("Nombre no encontrado")
    