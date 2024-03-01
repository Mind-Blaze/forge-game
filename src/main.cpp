#include <iostream>
#include <SDL.h>
//#include <string>
//#include <cstring> 
#include <SDL_ttf.h>

void SDL_ExitWithError(const char *message);
void SDL_ExitWithError(const char *message, SDL_Window *window);
void SDL_ExitWithError(const char *message, SDL_Window *window, SDL_Renderer *renderer);
void SDL_ExitWithError(const char *message, SDL_Window *window, SDL_Renderer *renderer, const char *path);

bool varBetween(int variable, int min, int max);

void doubleClick(int *items, int currentTouch);
int witchCase(int x, int y);

#include "imagesIndex.cpp"

int oldTouch = -1;
int money = 0;
float level = 1;
int ask = 0;
int price = 0;
int askPrice = 0;
int normalPrice = 0;
bool page = 0;
int canCraft = 0;
int clicks = 0;
bool craftAnimation = 0;
bool canContunueCraftAnimation = 0;


#include "renderCore.cpp"
#include "gameCore.cpp"


 

void buttonPressed(int x, int y, int items[]);

SDL_Rect itemHighlight(int box);

int main(int argc, char *argv[]) {
  /*
    Random
  */

  srand((unsigned) time(NULL));
  
  /*
    Les stats au démarage
  */

  ask = baseIronRubySword;
  
  money = 300;

  int items[34] = {0};
  items[0] = iron;
  items[1] = copper;
  items[2] = copper;
  items[3] = ruby;
  items[4] = coal;
  items[5] = coal;
  
  //ask = askGenerator(level,money,0);
  askPrice = sellPrice(ask,0);
  price = askPrice;
  
  /*
    Initialisation de SDL et de TTF
  */


  if(SDL_Init(SDL_INIT_VIDEO) != 0) SDL_ExitWithError("Initialisation");

  SDL_Window *window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,240 ScMulti,320 ScMulti,SDL_WINDOW_SHOWN);
  if(window == NULL) SDL_ExitWithError("Création fenetre");

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if(renderer == NULL) SDL_ExitWithError("Création moteur de rendu");
  if(SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_MUL)) SDL_ExitWithError("Impossible d'acctiver le blendmode",window,renderer);

  if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);

  initTextures(window,renderer);

  if(TTF_Init() != 0) SDL_ExitWithError("impossible de démarrer TTF",window,renderer);
  TTF_Font *font = TTF_OpenFont("assets/fonts/arial.ttf", 18 ScMulti);
  if(font == NULL) SDL_ExitWithError("impossible de charger la police",window,renderer);
  SDL_Color color = { 255, 255, 255 };

  

  /*
    Code principale
  */


  SDL_Event event;
  bool programState = true;
  bool toRefresh = 1;
  bool minimized = 0;
  
  while(programState){
   
    
    if(SDL_WaitEventTimeout(&event,maxFPS) == 1){
      
      switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
          if(event.button.button == SDL_BUTTON_LEFT){
            clicks = event.button.clicks;
            buttonPressed(event.motion.x,event.motion.y,items);
            toRefresh = 1;
          }
          break;

        case SDL_WINDOWEVENT:
          switch (event.window.event){
            case SDL_WINDOWEVENT_HIDDEN:
              minimized = 1;
              break;
            case SDL_WINDOWEVENT_EXPOSED:
              toRefresh = 1;
              minimized = 0;
              break;
            case SDL_WINDOWEVENT_MOVED:
              toRefresh = 1;
              break;
            
        }
        break;
  
        case SDL_QUIT:
          programState = false;
          break;
        
        default:
          break;

      }
    }
    
    
    if(craftAnimation){
      crafting(items);
    }
    if(canContunueCraftAnimation){
      refresh(window,renderer,items,itemHighlight(oldTouch),font,&color);
    }
    else if (toRefresh && !minimized){
      refresh(window,renderer,items,itemHighlight(oldTouch),font,&color);
      toRefresh = 0;
    }
  }
  SDL_DestroyTexture(*texture);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "\n";
  return 0;
}

/*
      ---------------------------------------
Calcule le boutton clické en fonction de la position
      ---------------------------------------
*/

int witchCase(int x, int y){

  int currentTouch = -1;

  if( x > 16 ScMulti && y > 128 ScMulti && x < 48 ScMulti && y < 160 ScMulti) currentTouch = 0;
  else if( x > 75 ScMulti && y > 128 ScMulti && x < 107 ScMulti && y < 160 ScMulti) currentTouch = 1;
  else if( x > 134 ScMulti && y > 128 ScMulti && x < 166 ScMulti && y < 160 ScMulti) currentTouch = 2;
  else if( x > 193 ScMulti && y > 128 ScMulti && x < 225 ScMulti && y < 160 ScMulti) currentTouch = 3;

  else if( x > 16 ScMulti && y > 176 ScMulti && x < 48 ScMulti && y < 208 ScMulti) currentTouch = 4;
  else if( x > 75 ScMulti && y > 176 ScMulti && x < 107 ScMulti && y < 208 ScMulti) currentTouch = 5;
  else if( x > 134 ScMulti && y > 176 ScMulti && x < 166 ScMulti && y < 208 ScMulti) currentTouch = 6;
  else if( x > 193 ScMulti && y > 176 ScMulti && x < 225 ScMulti && y < 208 ScMulti) currentTouch = 7;

  else if( x > 16 ScMulti && y > 224 ScMulti && x < 48 ScMulti && y < 256 ScMulti) currentTouch = 8;
  else if( x > 75 ScMulti && y > 224 ScMulti && x < 107 ScMulti && y < 256 ScMulti) currentTouch = 9;
  else if( x > 134 ScMulti && y > 224 ScMulti && x < 166 ScMulti && y < 256 ScMulti) currentTouch = 10;
  else if( x > 193 ScMulti && y > 224 ScMulti && x < 225 ScMulti && y < 256 ScMulti) currentTouch = 11;

  else if( x > 16 ScMulti && y > 272 ScMulti && x < 48 ScMulti && y < 304 ScMulti) currentTouch = 12;
  else if( x > 75 ScMulti && y > 272 ScMulti && x < 107 ScMulti && y < 304 ScMulti) currentTouch = 13;
  else if( x > 134 ScMulti && y > 272 ScMulti && x < 166 ScMulti && y < 304 ScMulti) currentTouch = 14;
  else if( x > 193 ScMulti && y > 272 ScMulti && x < 225 ScMulti && y < 304 ScMulti) currentTouch = 15;

  else if( x > 16 ScMulti && y > 272 ScMulti && x < 48 ScMulti && y < 304 ScMulti) currentTouch = 12;
  else if( x > 75 ScMulti && y > 272 ScMulti && x < 107 ScMulti && y < 304 ScMulti) currentTouch = 13;
  else if( x > 134 ScMulti && y > 272 ScMulti && x < 166 ScMulti && y < 304 ScMulti) currentTouch = 14;
  else if( x > 193 ScMulti && y > 272 ScMulti && x < 225 ScMulti && y < 304 ScMulti) currentTouch = 15;

  else if( x > 0 ScMulti && y > 0 ScMulti && x < 120 ScMulti && y < 30 ScMulti) { 
    if(oldTouch == 20 && page == 1) oldTouch = -1;
    currentTouch = -2;
    page = 0;
  }
  else if( x > 120 ScMulti && y > 0 ScMulti && x < 240 ScMulti && y < 30 ScMulti) {
    if(oldTouch == 16 && oldTouch == 17 && oldTouch == 18 && oldTouch == 19 && page == 0) oldTouch = -1;
    currentTouch = -2;
    page = 1;
  }

  else if (!page){
    if( x > 16 ScMulti && y > 44 ScMulti && x < 48 ScMulti && y < 76 ScMulti) currentTouch = 16;
    else if( x > 64 ScMulti && y > 44 ScMulti && x < 96 ScMulti && y < 76 ScMulti) currentTouch = 17;
    else if( x > 112 ScMulti && y > 44 ScMulti && x < 144 ScMulti && y < 76 ScMulti) currentTouch = 18;
    else if( x > 193 ScMulti && y > 44 ScMulti && x < 225 ScMulti && y < 76 ScMulti) currentTouch = 19;

    else if( x > 149 ScMulti && y > 48 ScMulti && x < 188 ScMulti && y < 73 ScMulti) currentTouch = 31;

    else if( x > 161 ScMulti && y > 86 ScMulti && x < 177 ScMulti && y < 106 ScMulti) currentTouch = 32;
    else if( x > 141 ScMulti && y > 90 ScMulti && x < 157 ScMulti && y < 106 ScMulti) currentTouch = 33;
    else if( x > 181 ScMulti && y > 90 ScMulti && x < 197 ScMulti && y < 106 ScMulti) currentTouch = 34;
  }

  if(page){
    if (x > 193 ScMulti && y > 44 ScMulti && x < 225 ScMulti && y < 76 ScMulti) currentTouch = 20;

    else if( x > 68 ScMulti && y > 39 ScMulti && x < 84 ScMulti && y < 55 ScMulti) currentTouch = 21;
    else if( x > 100 ScMulti && y > 39 ScMulti && x < 116 ScMulti && y < 55 ScMulti) currentTouch = 22;
    else if( x > 132 ScMulti && y > 39 ScMulti && x < 148 ScMulti && y < 55 ScMulti) currentTouch = 23;
    else if( x > 164 ScMulti && y > 39 ScMulti && x < 180 ScMulti && y < 55 ScMulti) currentTouch = 24;

    else if( x > 68 ScMulti && y > 65 ScMulti && x < 84 ScMulti && y < 81 ScMulti) currentTouch = 25;
    else if( x > 100 ScMulti && y > 65 ScMulti && x < 116 ScMulti && y < 81 ScMulti) currentTouch = 26;
    else if( x > 132 ScMulti && y > 65 ScMulti && x < 148 ScMulti && y < 81 ScMulti) currentTouch = 27;
    else if( x > 164 ScMulti && y > 65 ScMulti && x < 180 ScMulti && y < 81 ScMulti) currentTouch = 28;

    

    else if( x > 9 ScMulti && y > 34 ScMulti && x < 51 ScMulti && y < 58 ScMulti) currentTouch = 29;
    else if( x > 9 ScMulti && y > 62 ScMulti && x < 51 ScMulti && y < 86 ScMulti) currentTouch = 30;

  }

  return currentTouch;
}

/*
    ---------------------------------------
Effectue des acctions en fonction du boutton clické
    ---------------------------------------
*/

void buttonPressed(int x, int y, int items[]){

  int currentTouch = witchCase(x,y);

  std::cout << "level : " << level << " ask : " << ask << " clicks : " << clicks << "\n";

  if(page){
    std::cout << "shop : ";
  }
  if(!page){
    std::cout << "forge: ";
  }

  std::cout << currentTouch << " ; " << oldTouch;

  if(currentTouch != -2){ // le changement de tab n'est pas compris dans cette fonction
    if(currentTouch == -1){ // si touché dans le vide
      oldTouch = -1;
    }
    else if(currentTouch == oldTouch){  // si touché 2 fois au même endroit
      doubleClick(items,currentTouch);
    }
    // calcule des acction à faire dans l'ordre du dernier click
    else if (!page){  // dans la page "forge"
      if(varBetween(currentTouch,0,18)){  // un point d'échange est dans l'inventaire ou la forge en entré
        if(varBetween(oldTouch,0,18) || oldTouch == 19 && items[currentTouch] == 0){ // l'autre point d'échage des dans l'inventaire ou la forge entré et sorti
          int temp = items[oldTouch];
          items[oldTouch] = items[currentTouch];
          items[currentTouch] = temp;
          oldTouch = -1;
          canCrafting(items);
        }
        else if(oldTouch >= 32 && oldTouch <= 34 && items[oldTouch] == 0 && items[currentTouch] == coal){ // permet d'échanger avec l'emplacement charbon de la forge
          int temp = items[oldTouch];
          items[oldTouch] = items[currentTouch];
          items[currentTouch] = temp;
          oldTouch = -1;
        }
        else{
          oldTouch = currentTouch;
        }
      }
      else if(currentTouch == 19){  // de la sorti de la forge à l'inventaire ou la table de craft
        if(varBetween(oldTouch,0,18) && items[oldTouch] == 0){
          int temp = items[oldTouch];
          items[oldTouch] = items[currentTouch];
          items[currentTouch] = temp;
          oldTouch = -1;
        }
        else if(clicks == 2){
          doubleClick(items,currentTouch);
        }
        else{
          oldTouch = currentTouch;
        }
      }
      else if(currentTouch >= 32 && currentTouch <= 34){  // permet de mettre du charbon dans la forge, uniquement vers la forge
        if(items[oldTouch] == coal){
          int temp = items[oldTouch];
          items[oldTouch] = items[currentTouch];
          items[currentTouch] = temp;
          oldTouch = -1;
        }
        else if(clicks == 2 && items[oldTouch] == coal){
          doubleClick(items,currentTouch);
        }
        else{
          oldTouch = currentTouch;
        }

      }
      else if(currentTouch == 31 && canCraft !=0 && items[32] == coal && !craftAnimation && items[19] == 0){  // si le bouton craft est clické
        craftAnimation = true;
        items[16] = 0;
        items[17] = 0;
        items[18] = 0;
        oldTouch = -1;
      }
    }

    // dans la page "shop"
    else if(page){  
      if(varBetween(currentTouch,0,15) || currentTouch == 20){ // un point d'échange est dans l'inventaire ou le shop
        if(varBetween(oldTouch,0,15) || oldTouch == 20){ // l'autre point d'échage des dans l'inventaire ou le shop
          int temp = items[oldTouch];
          items[oldTouch] = items[currentTouch];
          items[currentTouch] = temp;
          oldTouch = -1;
        }
        else if(clicks == 2){
          doubleClick(items,currentTouch);
        }
        else{
          oldTouch = currentTouch;
        }
      }
      else if(varBetween(currentTouch,21,28)){ // permet de séléctionner un item à achetter
        oldTouch = currentTouch;
      }
      else if(currentTouch == 29){ // touche pour achetter l'item séléctionné
        if(varBetween(oldTouch,21,28)){
          if(money >= price){
            bool findPlace = 0;
            for(int i = 0; i <= 15; i++){ // met d'habort dans l'inventaire si possible
                if(items[i] == 0){
                  buy(items,oldTouch,i);
                  findPlace = true;
                  break; 
                }
              }
            if (!findPlace && items[20] == 0){ // sinon met l'item dans la case shop
              buy(items, oldTouch);
            }
          }
        }
        else{
          oldTouch = -1;
        }
      }
      else if(currentTouch == 30){ // vend l'item dans la case shop
        if(items[20] == ask){ // si cela correspond à l'item demandé
          money += askPrice;
          ask = askGenerator((int)level,money,levelUpdate());
          
          askPrice = sellPrice(ask,0);
          items[20] = 0;
        }
        else if(items[20] != 0){  // si c'est un autre item

          if(items[20] >= iron && items[20]<= coal) money += sellPrice(items[20]-11,1);
          else money += sellPrice(items[20],1);

          items[20] = 0;
        }
        oldTouch = -1;
      }
    }
  }

  
  // calcule le prix de l'item dans la case shop
  if(!varBetween(oldTouch,21,28)){  // si rien n'est prévu d'être acheté
    if(items[20] == 0 || items[20] == ask){ // affiche le prix de l'item demendé si la case shop est vide ou contient l'item
      price = askPrice;
    }
    else{ // affiche le prix de l'autre item (prix de base - 5%)

      if(items[20] >= iron && items[20]<= coal) normalPrice = sellPrice(items[20]-11,1);
      else normalPrice = sellPrice(items[20],1);

      price = normalPrice;
    }
  }
  else{ // affiche le prix de l'élément sélécationné en achat
    price = buyPrice(oldTouch);
  }

  std::cout << "  >>>  " << currentTouch << " ; " << oldTouch << "\n";
  
}

/*
---------------------------------------
      Si il y a un double click
---------------------------------------
*/

void doubleClick(int *items, int currentTouch){

  if(clicks == 2 && items[currentTouch] != 0 && currentTouch >= 0){
    if(currentTouch <= 15){
      if(!page && items[currentTouch] == coal){
        for(int i = 0; i < 3; i++){
          if(items[32+i] == 0){
            items[32+i] = items[currentTouch];
            items[currentTouch] = 0;
            break;
          }
        }
      }
      else if(!page){
        for(int i = 16; i <= 18; i++){
          if(items[i] == 0){
            int temp = items[i];
            items[i] = items[currentTouch];
            items[currentTouch] = temp;
            canCrafting(items);
            break; 
          }
        }
      }
      else if(page){
        if(items[20] == 0){
          int temp = items[20];
          items[20] = items[currentTouch];
          items[currentTouch] = temp;
          canCrafting(items);
        }
      }
    }
    else if(oldTouch <= 20){
      for(int i = 0; i <= 15; i++){
        if(items[i] == 0){
          int temp = items[i];
          items[i] = items[currentTouch];
          items[currentTouch] = temp;
          canCrafting(items);
          break; 
        }
      }
    }
  }
  
  oldTouch = -1;
}

/*
              ---------------------------------------
Donne le déctangle à mettre en surbrillance si une case est selectionné
              ---------------------------------------
*/

SDL_Rect itemHighlight(int box){

  SDL_Rect rectangle;
  rectangle.w = 32 ScMulti;
  rectangle.h = 32 ScMulti;
  if(box > 20){
    rectangle.w = 16 ScMulti;
    rectangle.h = 16 ScMulti;
  }

  switch(box){
    case 0:
      rectangle.x = 16 ScMulti;
      rectangle.y = 128 ScMulti;
      break;
    case 1:
      rectangle.x = 75 ScMulti;
      rectangle.y = 128 ScMulti;
      break;
    case 2:
      rectangle.x = 134 ScMulti;
      rectangle.y = 128 ScMulti;
      break;
    case 3:
      rectangle.x = 193 ScMulti;
      rectangle.y = 128 ScMulti;
      break;

    case 4:
      rectangle.x = 16 ScMulti;
      rectangle.y = 176 ScMulti;
      break;
    case 5:
      rectangle.x = 75 ScMulti;
      rectangle.y = 176 ScMulti;
      break;
    case 6:
      rectangle.x = 134 ScMulti;
      rectangle.y = 176 ScMulti;
      break;
    case 7:
      rectangle.x = 193 ScMulti;
      rectangle.y = 176 ScMulti;
      break;
    
    case 8:
      rectangle.x = 16 ScMulti;
      rectangle.y = 224 ScMulti;
      break;
    case 9:
      rectangle.x = 75 ScMulti;
      rectangle.y = 224 ScMulti;
      break;
    case 10:
      rectangle.x = 134 ScMulti;
      rectangle.y = 224 ScMulti;
      break;
    case 11:
      rectangle.x = 193 ScMulti;
      rectangle.y = 224 ScMulti;
      break;

    case 12:
      rectangle.x = 16 ScMulti;
      rectangle.y = 272 ScMulti;
      break;
    case 13:
      rectangle.x = 75 ScMulti;
      rectangle.y = 272 ScMulti;
      break;
    case 14:
      rectangle.x = 134 ScMulti;
      rectangle.y = 272 ScMulti;
      break;
    case 15:
      rectangle.x = 193 ScMulti;
      rectangle.y = 272 ScMulti;
      break;
  }

    if (!page){
      switch(box){
        case 16:
          rectangle.x = 16 ScMulti;
          rectangle.y = 44 ScMulti;
          break;
        case 17:
          rectangle.x = 64 ScMulti;
          rectangle.y = 44 ScMulti;
          break;
        case 18:
          rectangle.x = 112 ScMulti;
          rectangle.y = 44 ScMulti;
          break;
        case 19:
          rectangle.x = 193 ScMulti;
          rectangle.y = 44 ScMulti;
          break;
        case 32:
          rectangle.x = 161 ScMulti;
          rectangle.y = 86 ScMulti;
          rectangle.w = 16 ScMulti;
          rectangle.h = 16 ScMulti;
          break;
      }
    }
    else{
      switch(box){
        case 20:
          rectangle.x = 193 ScMulti;
          rectangle.y = 44 ScMulti;
          break;


        case 21:
          rectangle.x = 68 ScMulti;
          rectangle.y = 39 ScMulti;
          break;
        case 22:
          rectangle.x = 100 ScMulti;
          rectangle.y = 39 ScMulti;
          break;
        case 23:
          rectangle.x = 132 ScMulti;
          rectangle.y = 39 ScMulti;
          break;
        case 24:
          rectangle.x = 164 ScMulti;
          rectangle.y = 39 ScMulti;
          break;

        case 25:
          rectangle.x = 68 ScMulti;
          rectangle.y = 65 ScMulti;
          break;
        case 26:
          rectangle.x = 100 ScMulti;
          rectangle.y = 65 ScMulti;
          break;
        case 27:
          rectangle.x = 132 ScMulti;
          rectangle.y = 65 ScMulti;
          break;
        case 28:
          rectangle.x = 164 ScMulti;
          rectangle.y = 65 ScMulti;
          break;
      }
    }

    if (box == -1 ){
      rectangle.x = 0;
      rectangle.y = 0;
      rectangle.w = 0;
      rectangle.h = 0;
    }
    

  
  return rectangle;

}



/*
---------------------------------------
      Fonction autre
---------------------------------------
*/




// vérifie si la variable est entre les bornes
bool varBetween(int variable, int min, int max){
  return (variable >= min && variable <= max);
}



// en cas d'erreur graphique
void SDL_ExitWithError(const char *message){
    
    SDL_Log("ERREUR SDL : %s >>> %s\n", message, SDL_GetError());
    SDL_Quit();
    std::cout << "\n";
    exit(EXIT_FAILURE); 

}

void SDL_ExitWithError(const char *message, SDL_Window *window){

    SDL_Log("ERREUR SDL : %s >>> %s\n", message, SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "\n";
    exit(EXIT_FAILURE); 

}

void SDL_ExitWithError(const char *message, SDL_Window *window, SDL_Renderer *renderer){

    SDL_Log("ERREUR SDL : %s >>> %s\n", message, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "\n";
    exit(EXIT_FAILURE); 

}

void SDL_ExitWithError(const char *message, SDL_Window *window, SDL_Renderer *renderer, const char *path){

    SDL_Log("ERREUR SDL : %s : %s >>> %s\n", message, path, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "\n";
    exit(EXIT_FAILURE); 

}


// compilation : 

// windows : les dossier lib et includes doivent être présents; ajouter un fichier .dll dans le même dossier que l'executable
// cd "f:\Mes Programes\C++\minigame\" ; if ($?) { g++ src\main.cpp -o main -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf} ; if ($?) { .\main }
//
// principal : g++ src\main.cpp -o main -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
// ajouter "-mwindows" pour que le terminale ne se lance pas

// ubuntu (systeme unix) : les dossier lib et includes sont inutiles; le fichier sdl2-config est utile que pour la compilation
// cd "/media/Petit-progremmes/Mes Programes/C++/minigame" && g++ src/main.cpp -o main $(sdl2-config --cflags --libs) -lSDL2_ttf  && "/media/Petit-progremmes/Mes Programes/C++/minigame/"main
//
// principal : g++ src/main.cpp -o main $(sdl2-config --cflags --libs) -lSDL2_ttf