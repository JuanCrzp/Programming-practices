import tkinter as tk
from tkinter import messagebox, simpledialog
import math

# --- Configuración inicial de temas ---
themes = {
    "Oscuro": {
        "BG_COLOR": "#000000",
        "DISPLAY_BG": "#1C1C1C",
        "DISPLAY_FG": "#FFFFFF",
        "NUM_BTN_BG": "#505050",
        "NUM_BTN_FG": "#FFFFFF",
        "OP_BTN_BG": "#007AFF",
        "OP_BTN_FG": "#FFFFFF",
        "FUNC_BTN_BG": "#A6A6A6",
        "FUNC_BTN_FG": "#000000"
    },
    "Claro": {
        "BG_COLOR": "#F0F0F0",
        "DISPLAY_BG": "#FFFFFF",
        "DISPLAY_FG": "#000000",
        "NUM_BTN_BG": "#D3D3D3",
        "NUM_BTN_FG": "#000000",
        "OP_BTN_BG": "#FF9500",
        "OP_BTN_FG": "#FFFFFF",
        "FUNC_BTN_BG": "#E0E0E0",
        "FUNC_BTN_FG": "#000000"
    }
}

# Tema actual (por defecto, Oscuro)
current_theme = themes["Oscuro"]

# --- Funciones de evaluación y validación ---
def evaluate_expression(expr):
    if not expr.strip():
        return ""
    try:
        expr = expr.replace('^', '**')
        result = eval(expr, {"__builtins__": None}, {
            "sqrt": math.sqrt, "sin": math.sin, "cos": math.cos, "tan": math.tan,
            "log": math.log, "log10": math.log10, "pi": math.pi, "e": math.e,
            "abs": abs, "pow": pow
        })
        return result
    except Exception as e:
        return f"Error: {str(e)}"

# --- Variables Globales para Memoria e Historial ---
memory = 0  # Valor almacenado en memoria
history = []  # Lista de operaciones realizadas

def update_history(operation, result):
    # Agrega la operación y resultado al historial y actualiza el widget de historial
    history.append(f"{operation} = {result}")
    history_text.config(state="normal")
    history_text.delete("1.0", tk.END)
    for op in history[-10:]:  # Mostrar solo las últimas 10 operaciones
        history_text.insert(tk.END, op + "\n")
    history_text.config(state="disabled")

# --- Funciones de la Calculadora ---
def on_click(btn_text):
    global memory  # Declaración global para memory
    current = display_var.get()
    if btn_text == "AC":
        display_var.set("")
    elif btn_text == "=":
        result = evaluate_expression(current)
        if "Error:" not in str(result):
            update_history(current, result)
        display_var.set(result)
    elif btn_text == "±":
        try:
            value = float(current)
            display_var.set(str(-value))
        except Exception:
            display_var.set("Error: Valor no numérico")
    # Funciones de memoria
    elif btn_text == "M+":
        try:
            memory_value = float(evaluate_expression(current))
            memory += memory_value
        except Exception:
            display_var.set("Error en M+")
    elif btn_text == "M-":
        try:
            memory_value = float(evaluate_expression(current))
            memory -= memory_value
        except Exception:
            display_var.set("Error en M-")
    elif btn_text == "MR":
        display_var.set(str(memory))
    elif btn_text == "MC":
        memory = 0
        display_var.set("")
    else:
        # Si el botón es un operador visual, se mapea al operador real
        if btn_text in symbol_map and btn_text != "=":
            btn_text = symbol_map[btn_text]
        display_var.set(current + btn_text)

def on_key(event):
    # Evitar la duplicación retornando "break" después de procesar el evento
    if event.char in "0123456789.+-*/^":
        display_var.set(display_var.get() + event.char)
        return "break"
    elif event.keysym == "Return":
        on_click("=")
        return "break"
    elif event.keysym == "BackSpace":
        display_var.set(display_var.get()[:-1])
        return "break"
    elif event.keysym == "Escape":
        display_var.set("")
        return "break"

# Mapeo de símbolos visuales a operadores para la evaluación
symbol_map = {
    "÷": "/",
    "×": "*",
    "−": "-",
    "+": "+",
    "=": "="
}

# --- Funciones de Personalización (Temas) ---
def apply_theme(theme):
    global current_theme
    current_theme = themes[theme]
    root.config(bg=current_theme["BG_COLOR"])
    display.config(bg=current_theme["DISPLAY_BG"], fg=current_theme["DISPLAY_FG"])
    history_text.config(bg=current_theme["DISPLAY_BG"], fg=current_theme["DISPLAY_FG"])
    for btn in buttons_list:
        text = btn["text"]
        if text in ["AC", "±", "%", "M+", "M-", "MR", "MC"]:
            btn.config(bg=current_theme["FUNC_BTN_BG"], fg=current_theme["FUNC_BTN_FG"],
                       activebackground=current_theme["FUNC_BTN_BG"], activeforeground=current_theme["FUNC_BTN_FG"])
        elif text in ["÷", "×", "−", "+", "="]:
            btn.config(bg=current_theme["OP_BTN_BG"], fg=current_theme["OP_BTN_FG"],
                       activebackground=current_theme["OP_BTN_BG"], activeforeground=current_theme["OP_BTN_FG"])
        else:
            btn.config(bg=current_theme["NUM_BTN_BG"], fg=current_theme["NUM_BTN_FG"],
                       activebackground=current_theme["NUM_BTN_BG"], activeforeground=current_theme["NUM_BTN_FG"])

def change_to_dark():
    apply_theme("Oscuro")

def change_to_light():
    apply_theme("Claro")

# --- Configuración de la Ventana Principal ---
root = tk.Tk()
root.title("Calculadora                                                           by JC ")
root.geometry("500x700")
root.minsize(400, 600)
root.config(bg=current_theme["BG_COLOR"])

# Menú para Temas
menu_bar = tk.Menu(root)
theme_menu = tk.Menu(menu_bar, tearoff=0)
theme_menu.add_command(label="Oscuro", command=change_to_dark)
theme_menu.add_command(label="Claro", command=change_to_light)
menu_bar.add_cascade(label="Temas", menu=theme_menu)
root.config(menu=menu_bar)

# --- Display ---
display_var = tk.StringVar()
display = tk.Entry(root, textvariable=display_var, font=("Helvetica", 48),
                   bg=current_theme["DISPLAY_BG"], fg=current_theme["DISPLAY_FG"],
                   bd=0, justify="right")
display.grid(row=0, column=0, columnspan=4, padx=10, pady=(20, 10), sticky="nsew")

# --- Historial de Operaciones ---
history_text = tk.Text(root, height=5, state="disabled", font=("Helvetica", 12),
                       bg=current_theme["DISPLAY_BG"], fg=current_theme["DISPLAY_FG"])
history_text.grid(row=1, column=0, columnspan=4, padx=10, pady=(0, 10), sticky="nsew")

# --- Botones ---
btn_font = ("Helvetica", 24)
btn_defs = [
    # Fila: funciones y operadores
    [("AC", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"]),
     ("±", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"]),
     ("%", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"]),
     ("÷", current_theme["OP_BTN_BG"], current_theme["OP_BTN_FG"])],
    
    # Fila: botones de memoria
    [("M+", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"]),
     ("M-", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"]),
     ("MR", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"]),
     ("MC", current_theme["FUNC_BTN_BG"], current_theme["FUNC_BTN_FG"])],
    
    # Fila: numéricos y operadores
    [("7", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("8", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("9", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("×", current_theme["OP_BTN_BG"], current_theme["OP_BTN_FG"])],
    
    [("4", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("5", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("6", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("−", current_theme["OP_BTN_BG"], current_theme["OP_BTN_FG"])],
    
    [("1", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("2", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("3", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("+", current_theme["OP_BTN_BG"], current_theme["OP_BTN_FG"])],
    
    [("0", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     (".", current_theme["NUM_BTN_BG"], current_theme["NUM_BTN_FG"]),
     ("=", current_theme["OP_BTN_BG"], current_theme["OP_BTN_FG"])]
]

buttons_list = []  # Lista para guardar referencias a los botones y actualizarlos según el tema

row_index = 2
for row in btn_defs:
    if len(row) == 4:
        for col_index, (text, bg, fg) in enumerate(row):
            btn = tk.Button(root, text=text, bg=bg, fg=fg, font=btn_font, bd=0,
                            command=lambda t=text: on_click(t),
                            activebackground=bg, activeforeground=fg)
            btn.grid(row=row_index, column=col_index, sticky="nsew", padx=5, pady=5)
            buttons_list.append(btn)
    else:
        for col_index, (text, bg, fg) in enumerate(row):
            btn = tk.Button(root, text=text, bg=bg, fg=fg, font=btn_font, bd=0,
                            command=lambda t=text: on_click(t),
                            activebackground=bg, activeforeground=fg)
            if text == "0":
                btn.grid(row=row_index, column=0, columnspan=2, sticky="nsew", padx=5, pady=5)
            elif text == ".":
                btn.grid(row=row_index, column=2, sticky="nsew", padx=5, pady=5)
            else:  # "="
                btn.grid(row=row_index, column=3, sticky="nsew", padx=5, pady=5)
            buttons_list.append(btn)
    row_index += 1

# --- Configuración responsiva de la cuadrícula ---
total_rows = row_index
for i in range(total_rows):
    root.rowconfigure(i, weight=1)
for j in range(4):
    root.columnconfigure(j, weight=1)

root.bind("<Key>", on_key)

root.mainloop()
