/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <functional>
using namespace std;



int** crearMatriz(int n, int m) {
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[m];
    }
    return matriz;
}

void llenarMatriz(int** matriz, int n, int m) {
    cout << "Ingrese los valores:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matriz[i][j];
        }
    }
}

void mostrarMatriz(int** matriz, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void sumaFilas(int** matriz, int n, int m) {
    for (int i = 0; i < n; i++) {
        int suma = 0;
        for (int j = 0; j < m; j++) {
            suma += matriz[i][j];
        }
        cout << "Suma fila " << i << ": " << suma << endl;
    }
}

int mayorElemento(int** matriz, int n, int m) {
    int mayor = matriz[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matriz[i][j] > mayor) {
                mayor = matriz[i][j];
            }
        }
    }
    return mayor;
}

int** transponer(int** matriz, int n, int m) {
    int** t = crearMatriz(m, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            t[j][i] = matriz[i][j];
        }
    }
    return t;
}



double cuadrado(double x) { return x * x; }
double doble(double x) { return x * 2; }
double inverso(double x) { return (x != 0) ? 1 / x : 0; }

void aplicar(double* arr, int n, double (*func)(double)) {
    for (int i = 0; i < n; i++) {
        arr[i] = func(arr[i]);
    }
}



double procesarSimple(double* arr, int n,
                      function<double(double)> transformar,
                      function<double(double, double)> acumular) {

    double resultado = transformar(arr[0]);

    for (int i = 1; i < n; i++) {
        resultado = acumular(resultado, transformar(arr[i]));
    }

    return resultado;
}

double procesarMultiple(double* arr, int n,
                        vector<function<double(double)>> transformaciones,
                        function<double(double, double)> acumulador) {

    double resultado = 0;

    for (int i = 0; i < n; i++) {
        double valor = arr[i];

        for (auto& f : transformaciones) {
            valor = f(valor);
        }

        resultado = acumulador(resultado, valor);
    }

    return resultado;
}



int main() {
    int opcion;

    do {
        cout << "\n===== Taller de PUNTEROS==\n";
        cout << "Selecciona una opcion:\n";
        cout << "1. Funciones como parametros\n";
        cout << "2. Matriz dinamica + operaciones por punteros\n";
        cout << "3. Lambdas + composicion de operaciones\n";
        cout << "4. GANAR MAS NOTA PROFE (NIVEL BONUS)\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;


        if (opcion == 1) {
            int n;
            cout << "Tamaño del arreglo: ";
            cin >> n;

            double* arr = new double[n];

            cout << "Ingrese valores:\n";
            for (int i = 0; i < n; i++) cin >> arr[i];

            int op;
            cout << "1. Cuadrado\n2. Doble\n3. Inverso\nOpcion: ";
            cin >> op;

            if (op == 1) aplicar(arr, n, cuadrado);
            else if (op == 2) aplicar(arr, n, doble);
            else if (op == 3) aplicar(arr, n, inverso);

            cout << "Resultado:\n";
            for (int i = 0; i < n; i++) cout << arr[i] << " ";

            delete[] arr;
        }


        else if (opcion == 2) {
            int n, m;
            cout << "Filas y columnas: ";
            cin >> n >> m;

            int** matriz = crearMatriz(n, m);
            llenarMatriz(matriz, n, m);

            cout << "\nMatriz:\n";
            mostrarMatriz(matriz, n, m);

            sumaFilas(matriz, n, m);

            cout << "Mayor elemento: " << mayorElemento(matriz, n, m) << endl;

            int** trans = transponer(matriz, n, m);
            cout << "\nTranspuesta:\n";
            mostrarMatriz(trans, m, n);
        }

 
        else if (opcion == 3) {
            int n;
            cout << "Tamaño: ";
            cin >> n;

            double* arr = new double[n];
            for (int i = 0; i < n; i++) cin >> arr[i];

            auto transformar = [](double x) { return x * 2; };
            auto acumular = [](double a, double b) { return a + b; };

            double res = procesarSimple(arr, n, transformar, acumular);
            cout << "Resultado: " << res << endl;

            delete[] arr;
        }


        else if (opcion == 4) {
            int n;
            cout << "Tamaño: ";
            cin >> n;

            double* arr = new double[n];
            for (int i = 0; i < n; i++) cin >> arr[i];

            vector<function<double(double)>> transformaciones;

            transformaciones.push_back([](double x) { return x * 2; });
            transformaciones.push_back([](double x) { return x + 3; });
            transformaciones.push_back([](double x) { return x * x; });

            auto acumulador = [](double a, double b) { return a + b; };

            double res = procesarMultiple(arr, n, transformaciones, acumulador);
            cout << "Resultado: " << res << endl;

            delete[] arr;
        }

    } while (opcion != 0);

    return 0;
}
