    ##############################################################
    #             MENU OPERACIONES CON if/elif/else              #
    ##############################################################

def menu_if():
    print(" MENU CON if/elif/else ")
    print("1. Sumar")
    print("2. Resta")
    print("3. Multiplicacion")

    opcion = input("Elige una Opcion: ")

    if opcion == "1":
        print("Eligió la opción 1: Sumar")
        var1 = float(input("Ingrese el primer número: ")) 
        var2 = float(input("Ingrese el segundo número: "))
        print("El resultado de la suma es:", var1 + var2)

    elif opcion == "2":
        print("Eligio la opcion 2: Restar")
        var1 = float(input("Ingrese el primer número: ")) 
        var2 = float(input("Ingrese el segundo número: "))
        print("El resultado de la resta es:", var1 - var2)

    elif opcion == "3":
        print("Eligió la opción 3: Multiplicar")
        var1 = float(input("Ingrese el primer número: ")) 
        var2 = float(input("Ingrese el segundo número: "))
        print("El resultado de la multiplicación es:", var1 * var2)

    else:
        print("Opción no válida.")


# menu_if()     



    ##############################################################
    #                 MENU OPERACIONES CON WHILE                 #
    ##############################################################


def menu_while():
    while True:
        print("\n MENU CON WHILE ")
        print("1. Sumar")
        print("2. Restar")
        print("3. Multiplicacion")
        print("4. Salir")


        opcion = input("\nElige una Opcion: ")

        if opcion == "1":
            print("Eligió la opción 1: Sumar")
            var1 = float(input("Ingrese el primer número: ")) 
            var2 = float(input("Ingrese el segundo número: "))
            print("El resultado de la suma es:", var1 + var2)

        elif opcion == "2":
            print("Eligió la opción 2: Restar")
            var1 = float(input("Ingrese el primer número: ")) 
            var2 = float(input("Ingrese el segundo número: "))
            print("El resultado de la resta es:", var1 - var2)

        elif opcion == "3":
            print("Eligió la opción 3: Multiplicar")
            var1 = float(input("Ingrese el primer número: ")) 
            var2 = float(input("Ingrese el segundo número: "))
            print("El resultado de la multiplicación es:", var1 * var2)

        else:
            print("\nTerminando el programa.")
            break

# menu_while()     



    ##############################################################
    #                 MENU WHILE CON FUNCIONES                   #
    ##############################################################


def suma():
    var1 = float(input("Ingrese el primer numero  : "))
    var2 = float(input("Ingrese el segundo numero : "))
    print("El resultado de la suma es:", var1 + var2)

def multiplicacion():
    var1 = float(input("Ingrese el primer numero  : "))
    var2 = float(input("Ingrese el segundo numero : "))
    print("El resultado de la multiplicacion es:", var1 * var2)

def potencia():
    var1 = float(input("Ingrese la base  : "))
    var2 = float(input("Ingrese el exponente : "))
    print("El resultado de la potencia es:", var1 ** var2)

def menu_funciones():
    while True:
        print("\n MENU CON FUNCIONES ")
        print("1. Sumar")
        print("2. Multiplicación")
        print("3. Potencia")
        print("4. Salir")

        opcion = input("\nElige una opción: ")

        if opcion == "1":
            suma()
        elif opcion == "2":
            multiplicacion()
        elif opcion == "3":
            potencia()
        elif opcion == "4":
            print("\n Saliendo del programa.")
            break
        else:
            print(" Opción no válida. Intente de nuevo.")


# menu_funciones()    



  


  

    



