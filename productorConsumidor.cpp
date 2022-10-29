#include <iostream>
#include <thread>
#include <cstdlib>
#include <string>
#include <semaphore.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

const int bufferSize=25; //Capacidad del buffer
int buffer[bufferSize]; //Buffer
bool terminarEjecucion = false; //Variable para terminar la ejecución del programa. 
sem_t vacio, lleno; //Declaración de los semáforos

//Generar aleatoriamente el número de producción que se podra tener un un solo intento (entre 1 a 5)
int numeroProductosGenerar(){
        return rand() % 5 + 1;
}

//Generar aleatoriamente el número de consumo que se podra tener un un solo intento (entre 1 a 5)
int numeroProductosConsumir(){
        return rand() % 5 + 1;
}

//Imprimier el estado actual del buffer
void imprimirBuffer(){
    string bufferComoCadena;
    for(int x = 0; x < bufferSize; x++){
        int valor = buffer[x];
        if(x == bufferSize-1){
            bufferComoCadena = bufferComoCadena + "[" + to_string(valor) + "]\n";
        }
        else{
            bufferComoCadena = bufferComoCadena + "[" + to_string(valor) + "], ";
        }
    } 
    bufferComoCadena = "\nEstado del buffer: " + bufferComoCadena;
    cout << bufferComoCadena;
}

//Función del productor
void producir(){
    int posicionProduccion = 0; //Variable que indica en que posición del buffer se quedo la producción
    int numeroProduccion = 0; //Variable que indica el número de veces que se ha producido
    while(terminarEjecucion == false){
        sleep(1);
        sem_wait(&vacio); //dormir al productor ya que se termino de producir
        string msg = "\nThread-P Despertando ";
        cout << msg;
        int numProductosGenerar = numeroProductosGenerar();
        for (int x = 0; x < numProductosGenerar; x++){ //Inicia el proceso de producción
            if (posicionProduccion == bufferSize){ //Validar si no se ha llegado al límite del buffer
                posicionProduccion= 0;
            }
            int valorActualBuffer = buffer[posicionProduccion];
            if(valorActualBuffer != 0){ //Validar que no se intente producir en una posición llena
                msg = "\nThread-P Trato de producir en la posicion " + to_string(posicionProduccion) + 
                    " del buffer pero se encontraba llena.";
                break;
            }
            int v = rand() % 99 + 1; //generar un númer aleatorio entre 1 al 100
            buffer[posicionProduccion] = v;
            msg = "\nThread-P Produciendo en la posicion " + to_string(posicionProduccion) + 
                " del buffer, numero de produccion = " + to_string(numeroProduccion) + ", valor producido: " + to_string(v);
            cout << msg;
            posicionProduccion++;
            numeroProduccion++;

        } //Termina el proceso de producción
        msg = "\nThread-P Durmiendo Z.Z.Z.Z.Z ";
        cout << msg;
        imprimirBuffer();
        sem_post(&lleno); //despertar al consumidor ya que se termino de consumir
    }
    sleep(1);
}

//Función del consumidor
void consumir(){
    int posicionConsumo = 0; //Variable que indica en que posición del buffer se quedo el consumo
    int numeroConsumo = 0; //Variable que indica el número de veces que se ha consumido
    while (terminarEjecucion == false){
        sleep(1);
        sem_wait(&lleno); //dormir al consumidor cuando se termino de consumir 
        string msg = "\nThread-C Despertando ";
        cout << msg;
        int numProductosConsumir = numeroProductosConsumir();
        for (int x = 0; x < numProductosConsumir; x++){ //Inicia proceso de consumo
            if(posicionConsumo == bufferSize){ //Validar sino se ha llegado al límite del buffer
                posicionConsumo = 0;
            }
            int producto = buffer[posicionConsumo];
            if(producto == 0){ //Validar que no se intente consumir un valor vacio (0)
                msg = "\nThread-C Trato de consumir de la posicion " + to_string(posicionConsumo) + 
                    " del buffer pero se encontraba vacia ";
                cout << msg;
                break;
            }
            else{ //Consumir
                buffer[posicionConsumo] = 0; //La pos. del buffer que se consumio se vuelve a settear en vacio (0)
                msg = "\nThread-C Consumiendo de la posicion " + to_string(posicionConsumo) + 
                    " del buffer, numero de consumo = " + to_string(numeroConsumo) + " producto consumido: " + to_string(producto);
                cout << msg;
                posicionConsumo++;
                numeroConsumo++;
            }
        } //Termina proceso de consujmo
        msg = "\nThread-C Durmiendo Z.Z.Z.Z.Z";
        cout << msg;
        imprimirBuffer();
        sem_post(&vacio); //despertar al productor ya que se termino de consumir
    }
    sleep(1);
}

//Evaluar si se presiona la tecla Esc para salir 
void teclaPresionada(){
    while(true){
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
            terminarEjecucion = true;
            return;
        }
    }
}

int main(){
    // Inicialización de los semafors
    sem_init(&vacio, 0, 1); //Se inicializa en 1 para que sea el productor el primero en iniciar su proceso
    sem_init(&lleno, 0, 0); //Se inicializa en 0 para que el consumidor tenga que espera la señal del productor
    
    //Creación y ejeución de un hilo con la finalidad de terminar la ejecución del programa
    thread keyboardEvent(teclaPresionada);
    //Creación y ejecución de los hilos productor y consumidor
    thread productor(producir);
    thread consumidor(consumir);

    //Esperar por los hilos
    keyboardEvent.join();
    productor.join();
    cout << "\nTermino el productor";
    consumidor.join();
    cout << "\nTermino el consumidor";
    
    imprimirBuffer();
    return 0;
}