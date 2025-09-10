# Taller 2 - Diccionarios, bucles, condicionales, acumuladores, contadores y banderas

# 1. Solicitar numero de usuarios
num_usuarios = int(input("Ingrese el numero de usuarios a registrar: "))

# 2. Crear diccionario para los usuarios
usuarios = {}  # Diccionario principal

for i in range(num_usuarios):
    print(f"\nRegistro del usuario {i+1}:")
    nombre = input("Ingrese el nombre: ")
    cuenta = input("Ingrese el numero de cuenta bancaria: ")
    clave = input("Ingrese la clave de 3 digitos: ")

    # Guardar datos en un subdiccionario
    usuarios[nombre] = {
        "cuenta": cuenta,
        "clave": clave
    }

# 3. Solicitar usuario a consultar
print("\n--- CONSULTA DE USUARIO ---")
nombre_consulta = input("Ingrese el nombre del usuario a consultar: ")

# Validar si el usuario existe
if nombre_consulta in usuarios:
    datos_usuario = usuarios[nombre_consulta]
    clave_real = datos_usuario["clave"]

    # 4. Fuerza bruta para encontrar la clave
    print("\nIniciando ataque de fuerza bruta para encontrar la clave...")

    contador = 0  
    bandera = False  

    for intento in range(1000):  
        contador += 1
        intento_str = str(intento).zfill(3)  

        print(f"Intento {contador}: {intento_str}") 

        if intento_str == clave_real:
            bandera = True
            print("\n--- RESULTADO ---")
            print(f"Clave encontrada: {intento_str}")
            print(f"Numero de intentos: {contador}")
            break

    if not bandera:
        print("No se pudo encontrar la clave.")

    # 5. Imprimir informacion completa
    print("\n--- INFORMACION DEL USUARIO ---")
    print(f"Nombre: {nombre_consulta}")
    print(f"Cuenta Bancaria: {datos_usuario['cuenta']}")
    print(f"Clave: {datos_usuario['clave']}")

else:
    print("El usuario no existe en el sistema.")

