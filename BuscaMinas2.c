#include<ncurses.h>
#include<stdlib.h>
#include<time.h>

#define Mina 1
#define Numero 2
#define minaDetonada 3
#define casillaCubierta 4
#define puntero 5

void GenerarMinas(int *Mapa,int x,int y,int Ancho,int Largo,int maximoMinas);
void GenerarNumeros(int *Mapa,int Ancho,int Largo);
int Puntero(int* x, int* y, char Tecla, int Ancho,int *Mapa, WINDOW *win);
void initNcurses();
void dibujarTablero(int *Mapa, int Ancho, int Largo,int inicio, WINDOW *win);
//void cubrirCasillas();

int main () {
    initNcurses();
   
	int Campo[25];
    int Ancho = 5;
    int Largo = 5;
    int AnchoPantalla;
    int AlturaPantalla;
    getmaxyx(stdscr, AlturaPantalla, AnchoPantalla);
    int limiteSuperior = (AlturaPantalla - Largo)/2;
    int limiteInferior = (AlturaPantalla + Largo)/2;
    int limiteDerecho = (AnchoPantalla - Ancho)/2 ;
    int limiteIzquierdo = (AnchoPantalla + Ancho)/2 ;
    int posX = limiteDerecho;
    int posY = limiteSuperior;
	int Casilla;
    int maxMinas = 10;
    char tecla;
    
    
    
   
    //Semilla para número pseduo aleatorios
   
    if (has_colors()){
        init_pair(Mina,COLOR_BLACK,COLOR_WHITE);
        init_pair(Numero,COLOR_BLUE,COLOR_WHITE);
        init_pair(minaDetonada,COLOR_YELLOW,COLOR_RED);
        init_pair(casillaCubierta,COLOR_WHITE,COLOR_WHITE);
        init_pair(puntero,COLOR_BLACK,COLOR_WHITE);
    }
    WINDOW *ventana = newwin(Largo+4,Ancho+4,limiteSuperior - 1 ,limiteDerecho - 1);
    srand(time(NULL));
    
    do {//Inicializador
        tecla = getch(); //dibujarTablero(Campo,Ancho,Largo,20,9,1);
        printw("%d,%d" ,limiteDerecho,limiteSuperior);
        dibujarTablero(Campo,Ancho,Largo,1,ventana);
        if (tecla == '\n') {
            //Generar Minas
            GenerarMinas(Campo,posX,posY,Ancho,Largo,maxMinas);
        } else{
            Puntero(&posX,&posY,tecla,Ancho,Campo,ventana);
        }
        box(ventana,0,0);
        wrefresh(ventana);
    } while (tecla != '\n');
    
    
    //Generar Numeros de cada casilla
    GenerarNumeros(Campo,Ancho,Largo);
    
    while (tecla != 27) {//Juego después de haber creado las minas, salir con tecla esc
        tecla = getch();
        dibujarTablero(Campo,Ancho,Largo,0,ventana);
        Puntero(&posX,&posY,tecla,Ancho,Campo,ventana);
        box(ventana,0,0);
        wrefresh(ventana);
        //refresh();
    }
    endwin();
	return 0;
}







void GenerarMinas(int* Mapa,int x,int y,int Ancho,int Largo,int maximoMinas) {
    int crearMina;
    int cantidadMinas = 0;
    
    for (int casilla = 0; casilla < 25; casilla++) {
        
        if (cantidadMinas < maximoMinas) crearMina = rand()%2;
        else crearMina = 0;
        
        if (crearMina == 1){
            *(Mapa+casilla) = 9;//9 indica que hay una mina, porque 8 es #maximo con sentido
            cantidadMinas++;
        } else *(Mapa+casilla) = -1;//No hay mina
    }
    
    
    if (*(Mapa + x + y*Ancho) == 9){//Si se había generado una mina antes
        cantidadMinas--;
    }
    
    *(Mapa + x + y*Ancho) = -1; //La primera casilla que se hizo click
    
    int k=0;
    
    while (cantidadMinas < maximoMinas) {//Crear minas faltantes, si es que no se ha llegado a el máximo
        if (k == Ancho*Largo) {
            k = 0;
        }
        if (*(Mapa + k) != 9 && k != (x + y*Ancho)) {
            crearMina = rand()%2;
            if (crearMina == 1) {
                *(Mapa + k) = 9;
                cantidadMinas++;
            }
        }
        k++;
    }

    return;
}


void GenerarNumeros(int *Mapa,int Ancho,int Largo) {
    int NumeroMinas = 0;
    int Tamaño = Ancho*Largo;
    int esquinasNeg = Ancho + 1;
    int esquinasPos = Ancho - 1;
   
    for (int i =0; i < 25; i++) {
        NumeroMinas = 0;
        
        if ( *(Mapa + i) == -1){//Casilla sin minas
            if ((i+esquinasNeg) < Tamaño) {//Esquina derecha abajo
                if ( *(Mapa + i + esquinasNeg) == 9 ){
                    NumeroMinas++;
                    if ((i+1)%Ancho == 0) NumeroMinas--;
                }
            }
            
            if ((i-esquinasNeg) >= 0) { //Esquina izquierda arriba
                if ( *(Mapa + i - esquinasNeg) == 9 ){
                    NumeroMinas++;
                    if (i%Ancho == 0) NumeroMinas--;
                }
            }
            
            if ((i+esquinasPos) < Tamaño) {//Esquina izquierda abajo
                if ( *(Mapa + i + esquinasPos) == 9 ){
                    NumeroMinas++;
                    if (i%Ancho == 0) NumeroMinas--;
                }
            }
            
            if ((i-esquinasPos) >= 0) {//Esquina derecha arriba
                if ( *(Mapa + i - esquinasPos) == 9 ){
                    NumeroMinas++;
                    if ( (i+1)%Ancho == 0 ) NumeroMinas--;
                }
            }
            
            if ((i+Ancho) < Tamaño) {//Abajo
                if ( *(Mapa + i + Ancho) == 9 ) {
                    NumeroMinas++;
                    if (i > Ancho*Largo - 1) NumeroMinas--;
                }
            }
            
            if ((i-Ancho) >= 0) {//Arriba
                if ( *(Mapa + i - Ancho) == 9 ) {
                    NumeroMinas++;
                    if (i < Ancho) NumeroMinas--;
                }
            }
            
            if ((i+1) < Tamaño) {//Derecha
                if ( *(Mapa + i + 1) == 9 ) {
                    NumeroMinas++;
                    if ((i+1)%Ancho == 0) NumeroMinas--;
                }
            }
            
            if ((i-1) >= 0) {//Izquierda
                if ( *(Mapa + i - 1) == 9 ) {
                    NumeroMinas++;
                    if (i%Ancho == 0) NumeroMinas--;
                }
            }
            
            *(Mapa + i) = NumeroMinas;
        }
    }
    return;
}

void initNcurses(){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
    halfdelay(5);
    if (has_colors()){
         start_color();
    }
    return;
}



int Puntero(int* x, int* y, char Tecla,int Ancho,int *Mapa, WINDOW *win){
    
    switch (Tecla) {
            
        case 'W':
        case 'w'://w
            *y = *y - 1;
            break;
            
        case 'S':
        case 's'://s
           
            *y = *y + 1;
            break;
            
        case 'A':
        case 'a': //a
            *x = *x - 1;
            break;
            
        case 'D':
        case 'd': //d
            *x = *x + 1;
            break;
            
        case '\n':
            *(Mapa + (*x) + (*y)*Ancho) = *(Mapa + (*x) + (*y)*Ancho) - 10 ;//Restar 10 al valor del tablero
            break;
    }
    
    attron(COLOR_PAIR(puntero));
    wmove(win,*y,*x);
    waddch(win,'.');
    attroff(COLOR_PAIR(puntero));
    return 0;
}



void dibujarTablero(int *Mapa, int Ancho, int Largo,int inicio,WINDOW *win){
    if (inicio == 1){
        for (int x = 0 ; x < Ancho; x++) {
            for (int y = 0; y < Largo; y++) {
                attron(COLOR_PAIR(casillaCubierta));
                wmove(win,y,x);
                waddch(win,'o');
            }
        }
        attroff(COLOR_PAIR(casillaCubierta));
        return;
    }
    
    for (int x = 0; x < Ancho; x++) {
        for (int y = 0; y < Largo; y++) {
            wmove(win,y,x);
            if (*(Mapa + x + y*Ancho) >=  10) {
                attron(COLOR_PAIR(casillaCubierta));
                waddch(win,'x');
                attroff(COLOR_PAIR(casillaCubierta));
            } else if (*(Mapa + x + y*Ancho) == 9){
                    attron(COLOR_PAIR(Mina));
                    waddch(win,'O');
                    attroff(COLOR_PAIR(Mina));
                } else{
                    attron(COLOR_PAIR(Numero));
                    waddch(win,*(Mapa + x + y*Ancho) + 48); //Valor de numero + 48
                    attron(COLOR_PAIR(Numero));
                }
            
        }
    }
    return;
}
//Sumar 10 para saber si estan descubiertas o no
