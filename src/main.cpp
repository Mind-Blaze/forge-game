#include <iostream>
#include <SDL.h>
#include <string>
#include <cstring> 
#include <SDL_ttf.h>
#include "gameCore.cpp"

#define ScMulti *3
#define mainPathBackground "assets/gui/main5.bmp"
#define shopPathBackground "assets/gui/shop2.9.bmp"
 

void SDL_ExitWithError(const char *message);
void SDL_ExitWithError(const char *message, SDL_Window *window);
void SDL_ExitWithError(const char *message, SDL_Window *window, SDL_Renderer *renderer);
void SDL_ExitWithError(const char *message, SDL_Window *window, SDL_Renderer *renderer, const char *path);

void initTextures(SDL_Window *window , SDL_Renderer *renderer, SDL_Texture *texture[]);
void initTexturesCore(SDL_Window *window , SDL_Renderer *renderer, const char *path, SDL_Texture **texture, int index);

void refresh(SDL_Window *window , SDL_Renderer *renderer, SDL_Texture **texture, int items[], bool page, SDL_Rect *highlightRectangle, TTF_Font *font, SDL_Color *color
             , int money, int price, int ask);

void buttonPressed(int x, int y, int items[],int *oldTouch, bool *page, SDL_Window *window , SDL_Renderer *renderer, SDL_Texture **texture, int *money
                   , TTF_Font *font, SDL_Color *color,int *ask, float *level,int *price);

SDL_Rect itemHighlight(int box);

int main(int argc, char *argv[]) {

  srand(time(NULL));

  int items[21] = {0};
  items[0] = 66;
  items[1] = 66;
  items[2] = 70;
  items[3] = 69;

  int oldTouch = -1;

  bool page = 0;
  

  if(SDL_Init(SDL_INIT_VIDEO) != 0) SDL_ExitWithError("Initialisation");

  SDL_Window *window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,240 ScMulti,320 ScMulti,SDL_WINDOW_SHOWN);
  if(window == NULL) SDL_ExitWithError("Création fenetre");

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL) SDL_ExitWithError("Création moteur de rendu");
  if(SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_MUL)) SDL_ExitWithError("Impossible d'acctiver le blendmode",window,renderer);

  if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);

  
  SDL_Texture *texture[76];
  initTextures(window,renderer,texture);

  if(TTF_Init() != 0) SDL_ExitWithError("impossible de démarrer TTF",window,renderer);
  TTF_Font *font = TTF_OpenFont("assets/fonts/arial.ttf", 18 ScMulti);
  if(font == NULL) SDL_ExitWithError("impossible de charger la police",window,renderer);
  SDL_Color color = { 255, 255, 255 };

  int money = 100000;
  int ask = askGenerator(1,1);
  float level = 1.5;
	
  refresh(window,renderer,texture,items,page,NULL,font,&color,money,0,ask);

  SDL_Event event;
  bool programState = true;
  SDL_Rect tempRect;
  int price = sellPrice(ask);

  while(programState){
    while(SDL_WaitEvent(&event) == 1){

      switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
          buttonPressed(event.motion.x,event.motion.y,items,&oldTouch,&page,window,renderer,texture,&money,font,&color,&ask,&level,&price);
          break;
        case SDL_QUIT:
          programState = false;
          break;
        case SDL_WINDOWEVENT:
          switch (event.window.event){
            case SDL_WINDOWEVENT_EXPOSED:
              tempRect = itemHighlight(oldTouch);
              refresh(window,renderer,texture,items,page,&tempRect,font,&color,money,price,ask);
              break;
            case SDL_WINDOWEVENT_MOVED:
              tempRect = itemHighlight(oldTouch);
              refresh(window,renderer,texture,items,page,&tempRect,font,&color,money,price,ask);
              break;
          }
          break;
        default:
          break;

      }
      if(!programState){
        break;
      }
      if (ask == 0){
        ask = askGenerator(level,money);
      }

    }
  }

  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyTexture(*texture);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "\n";
  return 0;
}

void buttonPressed(int x, int y, int items[],int *oldTouch, bool *page, SDL_Window *window , SDL_Renderer *renderer, SDL_Texture **texture, int *money
                   , TTF_Font *font, SDL_Color *color, int *ask, float *level, int *price){

  int currentTouch = -1;
  int buyPrice = 0;

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
    if(*oldTouch == 20 && *page == 1) *oldTouch = -1;
    currentTouch = -2;
    *page = 0;
  }
  else if( x > 120 ScMulti && y > 0 ScMulti && x < 240 ScMulti && y < 30 ScMulti) {
    if(*oldTouch == 16 && *oldTouch == 17 && *oldTouch == 18 && *oldTouch == 19 && *page == 0) *oldTouch = -1;
    currentTouch = -2;
    *page = 1;
  }

  else if (!*page){
    if( x > 16 ScMulti && y > 44 ScMulti && x < 48 ScMulti && y < 76 ScMulti) currentTouch = 16;
    else if( x > 64 ScMulti && y > 44 ScMulti && x < 96 ScMulti && y < 76 ScMulti) currentTouch = 17;
    else if( x > 112 ScMulti && y > 44 ScMulti && x < 144 ScMulti && y < 76 ScMulti) currentTouch = 18;
    else if( x > 193 ScMulti && y > 44 ScMulti && x < 225 ScMulti && y < 76 ScMulti) currentTouch = 19;
  }

  if(*page){
    if (x > 193 ScMulti && y > 44 ScMulti && x < 225 ScMulti && y < 76 ScMulti) currentTouch = 20;

    else if( x > 68 ScMulti && y > 39 ScMulti && x < 84 ScMulti && y < 55 ScMulti) { currentTouch = 21; buyPrice = ironPrice;}
    else if( x > 100 ScMulti && y > 39 ScMulti && x < 116 ScMulti && y < 55 ScMulti) { currentTouch = 22; buyPrice = goldPrice;}
    else if( x > 132 ScMulti && y > 39 ScMulti && x < 148 ScMulti && y < 55 ScMulti) { currentTouch = 23; buyPrice = copperPrice;}

    else if( x > 68 ScMulti && y > 65 ScMulti && x < 84 ScMulti && y < 81 ScMulti) { currentTouch = 24; buyPrice = diamondPrice;}
    else if( x > 100 ScMulti && y > 65 ScMulti && x < 116 ScMulti && y < 81 ScMulti) { currentTouch = 25; buyPrice = rubyPrice;}
    else if( x > 132 ScMulti && y > 65 ScMulti && x < 148 ScMulti && y < 81 ScMulti) { currentTouch = 26; buyPrice = saphirPrice;}
    else if( x > 159 ScMulti && y > 52 ScMulti && x < 175 ScMulti && y < 68 ScMulti) { currentTouch = 28; buyPrice = amethystePrice;}

    

    else if( x > 9 ScMulti && y > 34 ScMulti && x < 51 ScMulti && y < 58 ScMulti) currentTouch = 29;
    else if( x > 9 ScMulti && y > 62 ScMulti && x < 51 ScMulti && y < 86 ScMulti) currentTouch = 30;

  }


  if(*page){
    std::cout << "page : ";
  }
  if(!*page){
    std::cout << "!page : ";
  }

  std::cout << currentTouch << " ; " << *oldTouch;

  bool rectangleState = 0;
  


  SDL_Rect rectangle;
  
  if(currentTouch != -1 && currentTouch != -2 && currentTouch != *oldTouch && currentTouch <= 20 && *oldTouch <= 20){

    if(items[*oldTouch] != 0 || items[currentTouch] != 0){
      if(*oldTouch == 16 || *oldTouch == 17 || *oldTouch == 18 || ((currentTouch == 16 || currentTouch == 17 || currentTouch == 18) && *oldTouch != -1 && *oldTouch != -2)){
        int temp = items[*oldTouch];
        items[*oldTouch] = items[currentTouch];
        items[currentTouch] = temp;
        *oldTouch = -1;
        crafting(items);

      }
      else if(*oldTouch == -1){
        *oldTouch = currentTouch;
        rectangle = itemHighlight(currentTouch);
        rectangleState = true;
      }
      else{
        int temp = items[*oldTouch];
        items[*oldTouch] = items[currentTouch];
        items[currentTouch] = temp;
        *oldTouch = -1;
      }
    }
    else{
      *oldTouch = currentTouch;
      rectangle = itemHighlight(currentTouch);
      rectangleState = true;
    }
  }
  else if(currentTouch >= 21 && currentTouch <= 28){
    rectangle = itemHighlight(currentTouch);
    rectangleState = true;
    *oldTouch = currentTouch;

  }
  else if(currentTouch == 29 && *oldTouch >= 21 && *oldTouch <= 28 && items[20] == 0){
    buy(items,money,*oldTouch);
    *oldTouch = -1;
  }
  else if(currentTouch == 30 && items[20] == *ask){
    *money = *money + *price;
    *ask = askGenerator((int)*level,*money);
    *price = sellPrice(*ask);
    items[20] = 0;
  }
  else if(currentTouch != -1 && currentTouch != -2 && currentTouch != *oldTouch){
    *oldTouch = currentTouch;
    rectangle = itemHighlight(currentTouch);
  }
  else if(currentTouch == *oldTouch){
    *oldTouch = -1;
  }

  
  if(rectangleState){
    if (buyPrice != 0) refresh(window,renderer,texture,items,*page,&rectangle,font,color,*money,buyPrice,*ask);
    else refresh(window,renderer,texture,items,*page,&rectangle,font,color,*money,*price,*ask);
  }
  else{
    if (buyPrice != 0) refresh(window,renderer,texture,items,*page,NULL,font,color,*money,buyPrice,*ask);
    else refresh(window,renderer,texture,items,*page,NULL,font,color,*money,*price,*ask);
  }

  std::cout << "  >>>  " << currentTouch << " ; " << *oldTouch << "\n";
  
}


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
      rectangle.x = 68 ScMulti;
      rectangle.y = 65 ScMulti;
      break;
    case 25:
      rectangle.x = 100 ScMulti;
      rectangle.y = 65 ScMulti;
      break;
    case 26:
      rectangle.x = 132 ScMulti;
      rectangle.y = 65 ScMulti;
      break;

    case 27:
      rectangle.x = 164 ScMulti;
      rectangle.y = 39 ScMulti;
      break;
    case 28:
      rectangle.x = 159 ScMulti;
      rectangle.y = 52 ScMulti;
      break;

  }


  
  return rectangle;

}





void refresh(SDL_Window *window , SDL_Renderer *renderer, SDL_Texture **texture, int items[], bool page, SDL_Rect *highlightRectangle, TTF_Font *font, SDL_Color *color
             , int money, int price, int ask){

  SDL_RenderClear(renderer);



  SDL_Rect rectangle;
  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = 32 ScMulti;
  rectangle.h = 32 ScMulti;


  if(page == 0){

    rectangle.w = 240 ScMulti;
    rectangle.h = 320 ScMulti;
    if(SDL_RenderCopy(renderer,texture[74],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"main");
    rectangle.w = 32 ScMulti;
    rectangle.h = 32 ScMulti;

    rectangle.x = 16 ScMulti;
    rectangle.y = 44 ScMulti;
    if(SDL_RenderCopy(renderer,texture[items[16]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"item 16");
    rectangle.x = 64 ScMulti;
    rectangle.y = 44 ScMulti;
    if(SDL_RenderCopy(renderer,texture[items[17]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 17");
    rectangle.x = 112 ScMulti;
    rectangle.y = 44 ScMulti;
    if(SDL_RenderCopy(renderer,texture[items[18]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 18");
    rectangle.x = 193 ScMulti;
    rectangle.y = 44 ScMulti;
    if(SDL_RenderCopy(renderer,texture[items[19]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 19");

  }
  
  else if(page){


    rectangle.w = 240 ScMulti;
    rectangle.h = 320 ScMulti;
    if(SDL_RenderCopy(renderer,texture[75],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"shop");
    rectangle.w = 16 ScMulti;
    rectangle.h = 16 ScMulti;

    rectangle.x = 68 ScMulti;
    rectangle.y = 39 ScMulti;
    if(SDL_RenderCopy(renderer,texture[58],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop1");
    rectangle.x = 100 ScMulti;
    rectangle.y = 39 ScMulti;
    if(SDL_RenderCopy(renderer,texture[59],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop2");
    rectangle.x = 132 ScMulti;
    rectangle.y = 39 ScMulti;
    if(SDL_RenderCopy(renderer,texture[61],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop3");

    rectangle.x = 68 ScMulti;
    rectangle.y = 65 ScMulti;
    if(SDL_RenderCopy(renderer,texture[60],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop4");
    rectangle.x = 100 ScMulti;
    rectangle.y = 65 ScMulti;
    if(SDL_RenderCopy(renderer,texture[62],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop5");
    rectangle.x = 132 ScMulti;
    rectangle.y = 65 ScMulti;
    if(SDL_RenderCopy(renderer,texture[63],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop6");
    rectangle.x = 159 ScMulti;
    rectangle.y = 52 ScMulti;
    if(SDL_RenderCopy(renderer,texture[64],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"itemShop7");

    

    
    char moneyChar[10];
    sprintf(moneyChar,"%d",money);
    SDL_Surface *surface = TTF_RenderText_Solid(font,moneyChar, *color);
    if(surface == NULL) SDL_ExitWithError("Impossible de crée la surface",window,renderer);
    SDL_Texture *moneyText = SDL_CreateTextureFromSurface(renderer, surface);
    if(moneyText == NULL) SDL_ExitWithError("Impossible de crée la texture",window,renderer);
    if (SDL_QueryTexture(moneyText, NULL, NULL, &rectangle.w, &rectangle.h) != 0) SDL_ExitWithError("Impossible de précharger la texture",window,renderer);
    rectangle.x = 54 ScMulti;
    rectangle.y = 90 ScMulti;
    if (SDL_RenderCopy(renderer, moneyText, NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de préafficher la texture",window,renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(moneyText);

    char priceChar[10];
    sprintf(moneyChar,"%d",price);
    surface = TTF_RenderText_Solid(font,moneyChar, *color);
    if(surface == NULL) SDL_ExitWithError("Impossible de crée la surface",window,renderer);
    SDL_Texture *priceText = SDL_CreateTextureFromSurface(renderer, surface);
    if(priceText == NULL) SDL_ExitWithError("Impossible de crée la texture",window,renderer);
    if (SDL_QueryTexture(priceText, NULL, NULL, &rectangle.w, &rectangle.h) != 0) SDL_ExitWithError("Impossible de précharger la texture",window,renderer);
    rectangle.x = 185 ScMulti;
    rectangle.y = 90 ScMulti;
    if (SDL_RenderCopy(renderer, priceText, NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de préafficher la texture",window,renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(priceText);
      

    rectangle.w = 32 ScMulti;
    rectangle.h = 32 ScMulti;
    rectangle.x = 193 ScMulti;
    rectangle.y = 44 ScMulti;
    
    if (items[20] != 0){
      if(SDL_RenderCopy(renderer,texture[items[20]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 20");
    }
    else{
      if(SDL_SetRenderDrawColor(renderer,0,0,0,100)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
      if(SDL_RenderCopy(renderer,texture[ask],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 20");
      SDL_RenderFillRect(renderer,&rectangle);
      if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    }

    if(items[20] >= 2 && items[20] != ask){
      if(SDL_SetRenderDrawColor(renderer,255,100,100,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
      SDL_RenderFillRect(renderer,&rectangle);
      if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    }

  }


  rectangle.x = 16 ScMulti;
  rectangle.y = 128 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[0]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 0");
  rectangle.x = 75 ScMulti;
  rectangle.y = 128 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[1]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 1");
  rectangle.x = 134 ScMulti;
  rectangle.y = 128 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[2]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 2");
  rectangle.x = 193 ScMulti;
  rectangle.y = 128 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[3]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 3");

  rectangle.x = 16 ScMulti;
  rectangle.y = 176 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[4]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 4");
  rectangle.x = 75 ScMulti;
  rectangle.y = 176 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[5]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 5");
  rectangle.x = 134 ScMulti;
  rectangle.y = 176 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[6]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 6");
  rectangle.x = 193 ScMulti;
  rectangle.y = 176 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[7]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 7");

  rectangle.x = 16 ScMulti;
  rectangle.y = 224 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[8]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 8");
  rectangle.x = 75 ScMulti;
  rectangle.y = 224 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[9]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 9");
  rectangle.x = 134 ScMulti;
  rectangle.y = 224 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[10]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 10");
  rectangle.x = 193 ScMulti;
  rectangle.y = 224 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[11]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 11");

  rectangle.x = 16 ScMulti;
  rectangle.y = 272 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[12]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 12");
  rectangle.x = 75 ScMulti;
  rectangle.y = 272 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[13]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 13");
  rectangle.x = 134 ScMulti;
  rectangle.y = 272 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[14]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 14");
  rectangle.x = 193 ScMulti;
  rectangle.y = 272 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[15]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 15");

  

  
  if (highlightRectangle != NULL){
    SDL_RenderFillRect(renderer, highlightRectangle);
  }

  SDL_RenderPresent(renderer);

}

void initTextures(SDL_Window *window , SDL_Renderer *renderer, SDL_Texture **texture){

  int i = 0;

  initTexturesCore(window,renderer,"assets/resource/0.bmp",texture,0);
  //initTexturesCore(window,renderer,"assets/resource/1.bmp",texture,1);
  initTexturesCore(window,renderer,"assets/item/10000.bmp",texture,2);
  initTexturesCore(window,renderer,"assets/item/10001.bmp",texture,3);
  initTexturesCore(window,renderer,"assets/item/10002.bmp",texture,4);
  initTexturesCore(window,renderer,"assets/item/10003.bmp",texture,5);
  initTexturesCore(window,renderer,"assets/item/10010.bmp",texture,6);
  initTexturesCore(window,renderer,"assets/item/10011.bmp",texture,7);
  initTexturesCore(window,renderer,"assets/item/10012.bmp",texture,8);
  initTexturesCore(window,renderer,"assets/item/10013.bmp",texture,9);
  initTexturesCore(window,renderer,"assets/item/10020.bmp",texture,10);
  initTexturesCore(window,renderer,"assets/item/10021.bmp",texture,11);
  initTexturesCore(window,renderer,"assets/item/10022.bmp",texture,12);
  initTexturesCore(window,renderer,"assets/item/10023.bmp",texture,13);
  initTexturesCore(window,renderer,"assets/item/10100.bmp",texture,14);
  initTexturesCore(window,renderer,"assets/item/10101.bmp",texture,15);
  initTexturesCore(window,renderer,"assets/item/10102.bmp",texture,16);
  initTexturesCore(window,renderer,"assets/item/10103.bmp",texture,17);
  initTexturesCore(window,renderer,"assets/item/10110.bmp",texture,18);
  initTexturesCore(window,renderer,"assets/item/10111.bmp",texture,19);
  initTexturesCore(window,renderer,"assets/item/10112.bmp",texture,20);
  initTexturesCore(window,renderer,"assets/item/10113.bmp",texture,21);
  initTexturesCore(window,renderer,"assets/item/10120.bmp",texture,22);
  initTexturesCore(window,renderer,"assets/item/10121.bmp",texture,23);
  initTexturesCore(window,renderer,"assets/item/10122.bmp",texture,24);
  initTexturesCore(window,renderer,"assets/item/10123.bmp",texture,25);
  initTexturesCore(window,renderer,"assets/item/10200.bmp",texture,26);
  initTexturesCore(window,renderer,"assets/item/10201.bmp",texture,27);
  initTexturesCore(window,renderer,"assets/item/10202.bmp",texture,28);
  initTexturesCore(window,renderer,"assets/item/10203.bmp",texture,29);
  initTexturesCore(window,renderer,"assets/item/10210.bmp",texture,30);
  initTexturesCore(window,renderer,"assets/item/10211.bmp",texture,31);
  initTexturesCore(window,renderer,"assets/item/10212.bmp",texture,32);
  initTexturesCore(window,renderer,"assets/item/10213.bmp",texture,33);
  initTexturesCore(window,renderer,"assets/item/10220.bmp",texture,34);
  initTexturesCore(window,renderer,"assets/item/10221.bmp",texture,35);
  initTexturesCore(window,renderer,"assets/item/10222.bmp",texture,36);
  initTexturesCore(window,renderer,"assets/item/10223.bmp",texture,37);
  initTexturesCore(window,renderer,"assets/item/10300.bmp",texture,38);
  initTexturesCore(window,renderer,"assets/item/10301.bmp",texture,39);
  initTexturesCore(window,renderer,"assets/item/10302.bmp",texture,40);
  initTexturesCore(window,renderer,"assets/item/10303.bmp",texture,41);
  initTexturesCore(window,renderer,"assets/item/10310.bmp",texture,42);
  initTexturesCore(window,renderer,"assets/item/10311.bmp",texture,43);
  initTexturesCore(window,renderer,"assets/item/10312.bmp",texture,44);
  initTexturesCore(window,renderer,"assets/item/10313.bmp",texture,45);
  initTexturesCore(window,renderer,"assets/item/10320.bmp",texture,46);
  initTexturesCore(window,renderer,"assets/item/10321.bmp",texture,47);
  initTexturesCore(window,renderer,"assets/item/10322.bmp",texture,48);
  initTexturesCore(window,renderer,"assets/item/10323.bmp",texture,49);
  initTexturesCore(window,renderer,"assets/item/10410.bmp",texture,50);
  initTexturesCore(window,renderer,"assets/item/10411.bmp",texture,51);
  initTexturesCore(window,renderer,"assets/item/10412.bmp",texture,52);
  initTexturesCore(window,renderer,"assets/item/10413.bmp",texture,53);
  initTexturesCore(window,renderer,"assets/item/10420.bmp",texture,54);
  initTexturesCore(window,renderer,"assets/item/10421.bmp",texture,55);
  initTexturesCore(window,renderer,"assets/item/10422.bmp",texture,56);
  initTexturesCore(window,renderer,"assets/item/10423.bmp",texture,57);

  initTexturesCore(window,renderer,"assets/resource/20100.bmp",texture,58);
  initTexturesCore(window,renderer,"assets/resource/21100.bmp",texture,59);
  initTexturesCore(window,renderer,"assets/resource/22100.bmp",texture,60);
  initTexturesCore(window,renderer,"assets/resource/23100.bmp",texture,61);
  initTexturesCore(window,renderer,"assets/resource/24100.bmp",texture,62);
  initTexturesCore(window,renderer,"assets/resource/25100.bmp",texture,63);
  initTexturesCore(window,renderer,"assets/resource/26100.bmp",texture,64);

  initTexturesCore(window,renderer,"assets/resource/20000.bmp",texture,66);
  initTexturesCore(window,renderer,"assets/resource/21000.bmp",texture,67);
  initTexturesCore(window,renderer,"assets/resource/22000.bmp",texture,68);
  initTexturesCore(window,renderer,"assets/resource/23000.bmp",texture,69);
  initTexturesCore(window,renderer,"assets/resource/24000.bmp",texture,70);
  initTexturesCore(window,renderer,"assets/resource/25000.bmp",texture,71);
  initTexturesCore(window,renderer,"assets/resource/26000.bmp",texture,72);
  initTexturesCore(window,renderer,mainPathBackground,texture,74);
  initTexturesCore(window,renderer,shopPathBackground,texture,75);
  

}


void initTexturesCore(SDL_Window *window , SDL_Renderer *renderer, const char *path, SDL_Texture **texture, int index){

  SDL_Surface *image;
  
  image = SDL_LoadBMP(path);
  if (image == NULL) SDL_ExitWithError("Impossible de charger l'image",window,renderer,path);
	texture[index] = SDL_CreateTextureFromSurface(renderer,image);
  if (texture[index] == NULL) SDL_ExitWithError("Impossible de creer la texture",window,renderer);
  image = NULL;

  SDL_FreeSurface(image);

}

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
// cd "f:\Mes Programes\C++\minigame\" ; if ($?) { g++ src\main.cpp -o main -I include -L lib -lmingw32 -lSDL2main -lSDL2} ; if ($?) { .\main }
//
// principal : g++ src\main.cpp -o main -I include -L lib -lmingw32 -lSDL2main -lSDL2
// ajouter "-mwindows" pour que le terminale ne se lance pas

// ubuntu (systeme unix) : les dossier lib et includes sont inutiles; le fichier sdl2-config est utile que pour la compilation
// cd "/home/mind/petit programmes/Mes Programes/C++/minigame/" && g++ scr/main.cpp -o main && "/home/mind/petit programmes/Mes Programes/C++/minigame/"main
//
// principal : g++ src\main.cpp -o main $(sdl2-config --cflags --libs)
