#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const int SUMAMULT_OPC = 1;
const int PALINDROMO_OPC = 2;
const int BASECONVERT_OPC = 3;
const int SALIR_OPC = 0;

static const string BaseValues[] = { "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
//26+9 =35 max base

int getbaseValue(char search, int pos) 
{
 
    if (BaseValues[pos][0] == search)
        return pos;
    pos++;
    getbaseValue(search, pos);
}

int baseMa10(int m, string input, int output, int pos) 
{
    for (int i = 0; i < input.length(); i++) 
    {
        int pot = input.length() - 1 - i;
        int value = getbaseValue(input[i], 0);
        output += value* pow(m, pot);
    }
    return output;
}

void base10aN(int n, int input, string output) 
{
    if (input == 0) 
    {
        cout << "Resultado: " << output << "\n";
    }
    else if (input != 0)
    {
        int search = input % n;
        output = BaseValues[search][0] + output;
        input = input / n;
        base10aN(n, input, output);
    }

}

vector<string> leerPalabrasDesdeArchivo(string archivo) 
{
    vector<string> palabras = vector<string>();

    ifstream file;
    file.open(archivo, ios::in);

    if (file.is_open()) 
    {
        while (!file.eof()) 
        {
            string line;
            getline(file, line);
            string palabra = (line);

            palabras.push_back(palabra);
        }
    }
    return palabras;
}

bool PalindromoCheck(string palabra, int end, int start)
{
    if (start >= palabra.length() / 2)
        return true;
    if (palabra[start] != palabra[start])
    {
        return false;
    }
    end--;
    start++;
    PalindromoCheck(palabra, end, start);
}

void palindromoMenu() 
{
    string archivo;
    cout << "Ingrese la ubicacion del archivo a leer: ";
    cin >> archivo;
    vector<string> palabras = leerPalabrasDesdeArchivo(archivo);
    int cantPalindromos = 0;
    for (int i = 0; i < palabras.size()-1; i++) 
    {
        bool check = PalindromoCheck(palabras[i], palabras[i].length(), 1);
        if (check == true) 
        {
            cout << "[" << i << "] " << palabras[i] << ": Palindromo\n";
            cantPalindromos++;
        }
        else
        {
            cout << "[" << i << "] " << palabras[i] << ": No palindromo\n";
        }
    }
    cout << "Cantidad de palindromos: " << cantPalindromos;
}

int Sumamult(int numero1, int numero2, int resultado) 
{
    if (numero2 <= 0) {
        return resultado;
    }
    numero2--;
    return Sumamult(numero1, numero2, resultado+=numero1);
}


int menu() {
    cout << "\n1. Hacer una multiplicacion con sumas\n";
    cout << "2. Comprobacion de palabras palindromas\n";
    cout << "3.Conversion de base m a base n\n";
    cout << "0. Salir\n";
    cout << "Ingrese la opcion que desea abrir: ";

    int opcion;
    cin >> opcion;
    return opcion;
}

void BaseMaN(int m, int n, string input)
{
    int base10 = baseMa10(m, input, 0, 0);
    base10aN(n, base10, " ");
}

int opcionSelector(int opcion)  {

    int numero1, numero2, resultado;
    string read;
    int  basem, basen;
    string convert;

    switch(opcion) 
    {
        
    case SUMAMULT_OPC:
        
        cout << "\n 1. Multiplicacion con sumas\n";
        cout << "Ingrese el primer numero\n";
        cin >> numero1;
        cout << "Ingrese el segundo numero\n";
        cin >> numero2;
        resultado = Sumamult(numero1, numero2, 0);
        cout << "\nEl resultado de su multiplicacion es " << resultado;
        break;

    case PALINDROMO_OPC:
        palindromoMenu();
        break;

    case BASECONVERT_OPC:

        cout << "\n Ingrese la base M\n";
        cin >> basem;
        cout << "Ingrese la base N\n";
        cin >> basen;
        cout << "Ingrese el numero a convertir\n";
        cin >> convert;
        BaseMaN(basem, basen, convert);
        break;

    case SALIR_OPC:

        cout << "Saliendo...";
        break;

    default: 
        cout << "Opcion no valida\n";
    }
    return opcion;
}

int main() {
    int opcion;
    do 
    {
        opcion = menu();
        opcion = opcionSelector(opcion);
    } while (opcion > 0);

    return 0;
}


