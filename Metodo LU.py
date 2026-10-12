def decomposicao_lu():

    print("--- Decomposição LU (Método de Doolittle) ---")
    n = int(input("Digite a ordem da matriz (n): "))

    A = [[0.0 for _ in range(n)] for _ in range(n)]
    L = [[0.0 for _ in range(n)] for _ in range(n)]
    U = [[0.0 for _ in range(n)] for _ in range(n)]

    print("\nDigite os valores da matriz A linha por linha:")
    for i in range(n):
        for j in range(n):
            A[i][j] = float(input(f"A[{i+1}][{j+1}]: "))

    for m in range(n - 1):
        
        for j in range(m, n):
            soma = 0.0

            for k in range(m):
                soma += L[m][k] * U[k][j]
            U[m][j] = A[m][j] - soma

        for i in range(m + 1, n):
            soma = 0.0

            for k in range(m):
                soma += L[i][k] * U[k][m]
            L[i][m] = (A[i][m] - soma) / U[m][m]

        L[m][m] = 1.0

    m = n - 1
    soma_final = 0.0

    for k in range(n - 1):
        soma_final += L[m][k] * U[k][m]
    
    U[m][m] = A[m][m] - soma_final
    L[m][m] = 1.0

    print("\n--- Matriz L (Inferior) ---")
    for i in range(n):
        linha_formatada = ["{:.4f}".format(val) for val in L[i]]
        print("  ".join(linha_formatada))

    print("\n--- Matriz U (Superior) ---")
    for i in range(n):
        linha_formatada = ["{:.4f}".format(val) for val in U[i]]
        print("  ".join(linha_formatada))

if __name__ == "__main__":
    decomposicao_lu()