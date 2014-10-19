
void testaLeds(int tempo);
void acendeLed(int x, int y);
void apagaLed(int x, int y);
void zeraTabuleiro();
void toggle(int x, int y);
void desenhaTabuleiro(int tempo, int  posX, int posY);
boolean estaCompleto();
void sorteiaTabuleiro();

int cont = 0;
boolean state = true;
int posicaox = 0;
int posicaoy = 0; 
int tabuleiro[6][6];
boolean apertado = false;
double low = 0.05;
double high = 0.20;

void setup() {

  for(int i = 0; i <= 11; i++)
    pinMode(i,OUTPUT);
  for(int i = 0; i <= 5; i++)
    digitalWrite(i,LOW);
  for(int i = 6; i <= 11; i++)
    digitalWrite(i,HIGH);
  zeraTabuleiro();
    tabuleiro[1][1] = tabuleiro[1][4] = tabuleiro[2][0] = tabuleiro[2][2] = tabuleiro[2][3] = tabuleiro[2][5] =
      tabuleiro[3][0] = tabuleiro[3][2] = tabuleiro[3][3] = tabuleiro[3][5] = tabuleiro[4][1] = tabuleiro[4][4] = 1;
    desenhaTabuleiro(300, 0, 0);
    zeraTabuleiro();
  testaLeds(200);
  sorteiaTabuleiro();
}

void loop(){
  if (!estaCompleto()) {
    int direita = analogRead(A0);
    int esquerda = analogRead(A1);
    int cima = analogRead(A2); 
    int baixo = analogRead(A3);
    int toggleIt = analogRead(A4);
    
    if(!apertado && direita >= 600) {
      posicaox = posicaox + 1; 
      apertado = true; 
    }
    if(posicaox > 5)
      posicaox = 0;
    
  
    if(!apertado && esquerda > 600) {
      posicaox = posicaox - 1; 
      apertado = true;
    
    }
    if(posicaox < 0){
      posicaox = 5;
    }
  
    if(!apertado && cima > 600) {
      posicaoy = posicaoy + 1; 
      apertado = true;
    }
    if(posicaoy > 5){
      posicaoy = 0;
    }
  
    if(!apertado && baixo > 600) {
      posicaoy = posicaoy - 1; 
      apertado = true;
    }
     
    
    if(posicaoy < 0){
      posicaoy = 5;
    }
    
      if(!apertado && toggleIt > 600) {
      toggle(posicaox,posicaoy); 
      apertado = true;
    }
    if(baixo < 600 && cima < 600 && esquerda < 600 && direita < 600 && toggleIt < 600)
        apertado = false;
        
    desenhaTabuleiro(3,posicaox,posicaoy);
  }
  else {
    apertado = false;
    zeraTabuleiro();
    tabuleiro[1][1] = tabuleiro[1][4] = tabuleiro[2][0] = tabuleiro[2][2] = tabuleiro[2][3] = tabuleiro[2][5] =
      tabuleiro[3][0] = tabuleiro[3][2] = tabuleiro[3][3] = tabuleiro[3][5] = tabuleiro[4][1] = tabuleiro[4][4] = 1;
    while (!apertado && analogRead(A4) <= 600) {
      desenhaTabuleiro(3, 0, 0);
      if (analogRead(A4) > 600) apertado = true;
    }
    zeraTabuleiro();
    testaLeds(200);
    sorteiaTabuleiro();
  }
}



void acendeLed(int x, int y) {
  digitalWrite(x,HIGH);
  digitalWrite(y + 6,LOW);
}

void apagaLed(int x, int y) {
  digitalWrite(x,LOW);
  digitalWrite(y + 6,HIGH);
}

void testaLeds(int tempo) {
  for(int x = 0; x <=5; x++)
    for(int y = 0; y <=5; y++) {
      acendeLed(x,y);
      delay(tempo);
      apagaLed(x,y);
    }
}

void zeraTabuleiro() {
  for(int i = 0; i <= 5; i++)
    for(int j = 0; j <= 5; j++)
      tabuleiro[i][j] = 0;
}

void toggle(int x, int y) {
    if(tabuleiro[x][y] == 0)
        tabuleiro[x][y] = 1;
    else
        tabuleiro[x][y] = 0;    

    if(x + 1 <= 5) {
        if (tabuleiro[x + 1][y] == 1)
          tabuleiro[x + 1][y] = 0;
        else
        tabuleiro[x + 1][y] = 1;
    }
    if(x - 1 >= 0){
        if(tabuleiro[x - 1][y] == 1)
          tabuleiro[x - 1][y] = 0;
        else
          tabuleiro[x - 1][y] = 1;
    }  
    if(y + 1 <= 5) {
        if(tabuleiro[x][y + 1] == 1)
          tabuleiro[x][y + 1] = 0;
        else
          tabuleiro[x][y + 1] = 1;
    }
    if(y - 1 >= 0){
        if(tabuleiro[x][y - 1] == 1)
          tabuleiro[x][y - 1] = 0;
        else
          tabuleiro[x][y - 1] = 1;
    }
}

void desenhaTabuleiro(int tempo, int posX, int posY) {
  for(int i = 0; i <= 5; i++) {
     digitalWrite(i,HIGH);
   for(int j = 0; j <= 5; j++) {
       if(tabuleiro[i][j] == 1)
             digitalWrite(j + 6,LOW);
         else
            digitalWrite(j + 6,HIGH);    
        if( i == posX && j == posY) {  
          if(state) {
                digitalWrite(posY + 6,LOW);
             } 
            else {
                digitalWrite(posY + 6,HIGH);
            }
            if (cont >= 125) {
                cont = 0;
                state = state ? false : true;
            }
                
          }
        
    }
      delay(tempo);    
      digitalWrite(i,LOW);
      cont++;    
   }  
}

boolean estaCompleto() {
  for (int i = 0; i < 6; i++)
     for (int j = 0; j < 6; j++)
        if (tabuleiro[i][j]) return false;
  if (low == 0.05) {
    low = 0.25;
    high = 0.50;
  }
  else if (low == 0.25) {
    low = 0.55;
    high = 0.85; 
  }
  else {
    low = 0.65;
    high = 0.9;
  }
  return true; 
}

void sorteiaTabuleiro() {
  randomSeed(analogRead(A5));
  long nLuzes = random(low*36, high*36); 
  for (; nLuzes > 0; nLuzes--)
    toggle(random(0, 6), random(0, 6));
}
