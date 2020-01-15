/*El juego favorito de Gupy
 Por Jack Robles García
 GUPY: Gato únicamente Para Yucatécos
 */
#include<iostream>
#include<stdbool.h>
#include <unistd.h>
#include<stdlib.h>
using namespace std;
int IA(int &electi);
void Tablero();
bool victoria();
char cuadrante[9] = {'1','2','3','4','5','6','7','8','9'};// Variable Global para usarla en varias funciones

int main(){
    int electi=0,turno=0;
    char marca[2]={'X','O'};
    cout<<"\tGUPY\n"<<"1 para modo de un jugador, 2 para multijugador"<<endl;
    cin<<electi;
    while(victoria()==false) {
           Tablero();
    cout<<"Jugador "<<turno+1<<" Ingresa número de casilla: ";
      
        if (turno==0) {
             cin>>electi;
        } else if (turno==1){
            electi=IA(electi);
            cout<<electi<<endl;
            usleep(1000000);
        }
       
    if(electi==1 && cuadrante[0]=='1'){
        cuadrante[0]= marca[turno];
    } else  if(electi==2 && cuadrante[1]=='2'){
        cuadrante[1]= marca[turno];
    } else  if(electi==3 && cuadrante[2]=='3'){
        cuadrante[2]= marca[turno];
    } else  if(electi==4 && cuadrante[3]=='4'){
        cuadrante[3]= marca[turno];
    } else  if(electi==5 && cuadrante[4]=='5'){
        cuadrante[4]= marca[turno];
    } else  if(electi==6 && cuadrante[5]=='6'){
        cuadrante[5]= marca[turno];
    } else  if(electi==7 && cuadrante[6]=='7'){
        cuadrante[6]= marca[turno];
    } else  if(electi==8 && cuadrante[7]=='8'){
        cuadrante[7]= marca[turno];
    } else  if(electi==9 && cuadrante[8]=='9'){
        cuadrante[8]= marca[turno];
    } else {
        turno+=2;//Añado dos para después sustraerlos
    }
 
        victoria();//Verifica que hayan ganado
        if (turno==0 ) { //Cambiar turnos
             turno++;
        } else if (turno==1){
            turno--;
        } else {
            cout<<"Entra un numero válido weón..."<<endl;
            usleep(2000000);//La función en unix maneja microsegundos 10^-6 segundos
            turno-=2;//Quito 2 para conserva el turno del jugador
        }
    }
    if (turno==0 ) { //Imprimir ganador
        Tablero();
       cout<<"El jugador "<<turno++<<" ganó"<<endl;
    } else if (turno==1){
        Tablero();
        cout<<"El jugador "<<turno--<<" ganó"<<endl;
    }
  
}
//:::::::::::::::::::::::::::-> Funciones

void Tablero(){
    system("clear");//"clear" es el comando equivalente a "clr" en sistemas unix
    cout<<"     |     |"<<endl;
    cout<<"  "<<cuadrante[0]<<"  |  "<<cuadrante[1]<<"  |  "<<cuadrante[2]<<endl;
    cout<<"_____|_____|_____"<<endl;
    cout<<"     |     |"<<endl;
    cout<<"  "<<cuadrante[3]<<"  |  "<<cuadrante[4]<<"  |  "<<cuadrante[5]<<endl;
    cout<<"_____|_____|_____"<<endl;
    cout<<"     |     |"<<endl;
    cout<<"  "<<cuadrante[6]<<"  |  "<<cuadrante[7]<<"  |  "<<cuadrante[8]<<endl;
    cout<<"     |     |"<<endl;
}

bool victoria() {//verfica las combinaciones, las condiciones usan el axioma de transistividad
    if(cuadrante[0]==cuadrante[1]&&cuadrante[2]==cuadrante[0]){        //1 2 3
        return true;
    } else if (cuadrante[3]==cuadrante[6]&&cuadrante[3]==cuadrante[5]){//4 5 6
        return true;
    } else if (cuadrante[6]==cuadrante[7]&&cuadrante[6]==cuadrante[8]){//7 8 9
        return true;
    } else if (cuadrante[0]==cuadrante[3]&&cuadrante[0]==cuadrante[6]){//1 4 7
        return true;
    } else if (cuadrante[1]==cuadrante[4]&&cuadrante[1]==cuadrante[7]){//2 5 8
        return true;
    } else if (cuadrante[2]==cuadrante[8]&&cuadrante[2]==cuadrante[5]){//3 6 9
        return true;
    } else if (cuadrante[6]==cuadrante[2]&&cuadrante[6]==cuadrante[4]){//7 5 3
        return true;
    } else if (cuadrante[0]==cuadrante[4]&&cuadrante[0]==cuadrante[8]){//1 5 9
        return true;
    } else {
        return false;
        }
}//100 líneas exactas antes de agregarle la IA

int IA(int &electi){
    
    /*
     Evaluar casilla actual del jugador
     -> dependiendo de la casilla evaluada, inteligencia pondrá un número
     */
    if (electi == 1 || electi == 2  ||  electi == 3 ) {
        
    }
    return srand(time(NULL));
}
