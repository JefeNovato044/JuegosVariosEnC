#include<iostream>
#include<ctime>
#include<ncurses.h>
using namespace std;

//Objetos 
class proyectil {
    private:
        int posX;
        int posY;
    
    public:
        void setPos(int x, int y){
            posX = x;
            posY = y;
        }
    
        int* getPos(){
            int posiciones[2] = {posX, posY};
            return posiciones;
        }
    
        void moverProyectil (int dir){
            posY += dir;
        }
    
        void render(){
            mvaddch(posY + 1, posX, ' ');
            mvaddch(posY,posX,'|');
        }
};

class naveEspacial {
    protected:
        int posX;
        int posY;
        int hitBox;//Amplitud del lugar donde puede ser dañado
        bool isAlive = true;
        char diseño[9] = { ' ','\\' , '(' , '^' ,  '-' , '^',')','/', ' '};
        int gap = 1;
        int acumulatedGap = 0;
        int timer =10;
        proyectil *prjPtr = NULL;
    
    public:
        void isHit(int x, int y){
            if (x >= posX && x <= (posX + 6) && y == posY) {
                isAlive = false;
            }
            return;
        }
    
    
        bool checkBelow(naveEspacial *ptr){//Función para saber si puede disparar o no.
            if(ptr -> isAlive == false){
                return true;
            } else{
                return false;
            }
        }
    
    
        void moveObject(){
    
                
              if (acumulatedGap == 11 || acumulatedGap == -1) {//Reset position after moving 10 times.
                    gap *= -1;
                }
            
            posX += gap;
            acumulatedGap += gap;
            move(12,25);
            printw("A: %d", acumulatedGap);
            return;
        }
    
        void render(){
            static int boca = 1;
         //   if (posX >= 0 && posX <= 99) {//Solo renderizar si estan en la pantalla
                if (boca > 0) {
                        diseño[4] = '-';
                    } else{
                        diseño[4] = '0';
                    }
            
                    for (int i = 0; i < 9; i++) {
                        //Mueve el cursor a la posición adecuada, y añade el caractér correspondiente.
                        if (isAlive) {
                            mvaddch(posY, posX + i,diseño[i]);
                        } else{
                            mvaddch(posY, posX + i,' ');
                        }
                    }
                    //mvaddch(posY, posX + 8,' ');
                    boca*=-1;
                //}
            }
            
    
        void shoot(){
            if (prjPtr == NULL) {
                prjPtr = new proyectil;//Crear nuevo proyectil
                prjPtr -> setPos(posX, posY - 3);
            }
        }
        
       // bool checkProyectile(){
           // return true;
        //}
    
        void destruirProyectil(){
            delete prjPtr;
            prjPtr = NULL;
        }
    
        void setPos(int x, int y) {
            posX = x;
            posY = y;
        }
};

class naveJugador : public naveEspacial {
    
    private:
        int vidas;//Numero de intentos
    
    public:
        //Función para controlar la nave.
    int controles(){
        char key = getch();
        switch (key) {
            case 'a':
                posX--;
                break;
            case 'd':
                posX++;
                break;
            case 'w':
                shoot();
                break;
            case 27:
                return 1;
        }
        
        return 0;
    }
    
        void setPos(int x, int y) {
               posX = x;
               posY = y;
        }
  
        void render(){
            mvaddch(posY,posX,'*');
            mvaddch(posY,posX + 1,'N');
            mvaddch(posY,posX - 1,'N');
            mvaddch(posY - 1, posX,'I');
            mvaddch(posY, posX - 2,' ');
            mvaddch(posY, posX + 2,' ');
            mvaddch(posY - 1, posX - 1,' ');
            mvaddch(posY - 1, posX + 1,' ');
        }
        
    bool checkProyectile(){
        
       // if (prjPtr -> ) {
        
        //}
        mvprintw(15,20,"                      ");//Limpiar buffer
        mvprintw(15,20,"Ptr: %p", prjPtr);
        if (prjPtr != NULL){
            prjPtr->moverProyectil(-1);
            prjPtr->render();
        }
        if (timer == 0) {
            destruirProyectil();
            timer = 10;
        }
        timer--;
               return true;
           }
     //Sobrescribir función.
};

void initNcurses(){
    initscr();
    noecho();
    raw();
    timeout((1.0f/60.0f)*1000);
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    return;
}



int main(){

    time_t aTime = 0;
    time_t bTime = 0;
    float elapsedTime;
    float timer = 0.0f;
    cout<<"\e[8;25;100t";//Cambiar tamaño de terminal a 80x40 (altura x ancho)
    
    initNcurses();
    
    bool jugando = true;
    naveEspacial grupoEnemigos[55];
    //Inicializar enemigos
    int numAliensPorFila = 100/9;
    int Filas = 5;
    
    for (int Fila = 0; Fila < Filas; Fila++) {//Alien \(^-^)/--
        for (int col = 0; col < numAliensPorFila; col++) {
            grupoEnemigos[Fila*11 + col].setPos(9*col,Fila + 2);//(0,Fila),(9,Fila),(18,Fila)...
        }
    }
    
    //Inicializar el jugador
    naveJugador* jugador = new naveJugador;
    jugador->setPos(49,23);
    
    
    
    
    
    //:::::::::::::.::::::::::CICLO DE JUEGO::::::::::::::::::::::::::::::///
    while(jugando){
    //Lógica de juego
       
        if (jugador->controles() == 1) {
                  jugando = false;
        }
        
        
        jugador->checkProyectile();//Checar Proyectil
        
        for (int Fila = 0; Fila < Filas; Fila++) {//Mover enemigos
            for (int col = 0; col < numAliensPorFila; col++) {
                 grupoEnemigos[Fila*11 + col].moveObject();
            }
        }
         
        
        
        
        //Renderizado
        for (int Fila = 0; Fila < Filas; Fila++) {
            for (int col = 0; col < numAliensPorFila; col++) {
                 grupoEnemigos[Fila*11 + col].render();
            }
        }
      
        jugador->render();
        mvprintw(0,0,"uWu");
        refresh();
    }
    
    
    
    delete jugador;
    endwin();
    return 0;
}




















/*
Alienigena:
.........
\(^-^)/--
^ Posición del alienígena señalan al brazo, las posiciónes de las demas piezas estan dados por: (x + n, y)
 
 
 

 
 
 A = (1,2,3,4)
 Relacion = {(1,2), (2,2), (2,3), (3,4)}
 
void moveObject(){
        static int gap = 1;
        static int acumulatedGap = 0;
        static int timer = 1000;
        
        if (timer == 0) {
        
            if (acumulatedGap > 10) {//Reset position after moving 10 times.
                posX -= acumulatedGap;
                acumulatedGap = 0;
                mvprintw(12,25,"Eureqo");
            } else{
                posX += gap;
                acumulatedGap++;
                mvprintw(12,25,"Eureka");
            }
            
            timer = 10;
        } else{
            timer --;
            
        }
        
        return;
    }

 lista de enemigos mas gap puede que me de a que enemigo le estoy disparadno sin tener que checar toda la lista
 */

