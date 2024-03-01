#define ScMulti *3

#define maxFPS 1000/ 60


int baseCraftingTime = 1000;
int craftingTime = baseCraftingTime;
int craftAnimationState = 0;
long craftAnimationStartTime = 0;

/*
---------------------------------------
  Affichage suplémentaire de la forge
---------------------------------------
*/

void refreshMain(SDL_Window *window , SDL_Renderer *renderer, int items[], SDL_Rect highlightRectangle){
  
  SDL_Rect rectangle;
  rectangle.x = 0;
  rectangle.y = 0;


  // affiche l'arière plan de la forge
  rectangle.w = 240 ScMulti;
  rectangle.h = 320 ScMulti;
  if(SDL_RenderCopy(renderer,texture[mainBackgroundIndex],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"main");
  rectangle.w = 32 ScMulti;
  rectangle.h = 32 ScMulti;

  // affiche les items en entré de la table de craft
  rectangle.x = 16 ScMulti;
  rectangle.y = 44 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[16]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"item 16");
  rectangle.x = 64 ScMulti;
  rectangle.y = 44 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[17]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 17");
  rectangle.x = 112 ScMulti;
  rectangle.y = 44 ScMulti;
  if(SDL_RenderCopy(renderer,texture[items[18]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 18");
  //affiche l'item en sorti de la forge
  if (canCraft == 0){
    rectangle.x = 193 ScMulti;
    rectangle.y = 44 ScMulti;
    if(SDL_RenderCopy(renderer,texture[items[19]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 19");
  }

  // affiche les cases charbon de la forge
  rectangle.x = 161 ScMulti;
  rectangle.y = 86 ScMulti;
  rectangle.w = 16 ScMulti;
  rectangle.h = 16 ScMulti;
  if(SDL_RenderCopy(renderer,texture[coal],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Furnace coal");
  if(items[32] != coal) { // si c'est vide (ajoute un effect rougeatre)
    if(SDL_SetRenderDrawColor(renderer,255,100,100,200)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
  }

  rectangle.x = 141 ScMulti;
  rectangle.y = 90 ScMulti;
  if(SDL_RenderCopy(renderer,texture[coal],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Furnace coal");
  if(items[33] != coal) { // si c'est vide (ajoute un effect rougeatre)
    if(SDL_SetRenderDrawColor(renderer,255,100,100,200)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
  }

  rectangle.x = 181 ScMulti;
  rectangle.y = 90 ScMulti;
  if(SDL_RenderCopy(renderer,texture[coal],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Furnace coal");
  if(items[34] != coal) { // si c'est vide (ajoute un effect rougeatre)
    if(SDL_SetRenderDrawColor(renderer,255,100,100,200)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
  }

  
  // si un item peut être crafter
  if(canCraft != 0 && craftAnimation == 0){

    // affiche le début de la flèche (parti que fait juste un trait)
    rectangle.x = 149 ScMulti;
    rectangle.y = 56 ScMulti;
    rectangle.w = 27 ScMulti;
    rectangle.h = 8 ScMulti;
    if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    // affiche la fin de la flèche
    for(int i = 0; i <= 11; i++){

      rectangle.x = (176 + i) ScMulti;
      rectangle.y = (48 + 1 * i) ScMulti;
      rectangle.w = 1 ScMulti;
      rectangle.h = (24 - 2 * i) ScMulti;
      if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    }

    // affiche l'item qu'il est possible de crafter en assombrit
    rectangle.x = 193 ScMulti;
    rectangle.y = 44 ScMulti;
    rectangle.w = 32 ScMulti;
    rectangle.h = 32 ScMulti;
    if(SDL_RenderCopy(renderer,texture[canCraft],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Can Craft Item");
    if(SDL_SetRenderDrawColor(renderer,50,50,50,100)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
  }
  else if(craftAnimation){

    rectangle.x = 193 ScMulti;
    rectangle.y = 44 ScMulti;
    rectangle.w = 32 ScMulti;
    rectangle.h = 32 ScMulti;
    if(SDL_RenderCopy(renderer,texture[items[19]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 19");

    if(craftAnimationState == 0){
      craftAnimationStartTime = SDL_GetTicks();
    }

    // affiche progressivement le début de la flèche (parti que fait juste un trait)
    if(craftAnimationState <= 27){
      rectangle.x = 149 ScMulti;
      rectangle.y = 56 ScMulti;
      rectangle.w = craftAnimationState ScMulti;
      rectangle.h = 8 ScMulti;
      if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    } // affiche progressivement la fin de la flèche
    if(craftAnimationState > 27){

      rectangle.x = 149 ScMulti;
      rectangle.y = 56 ScMulti;
      rectangle.w = 27 ScMulti;
      rectangle.h = 8 ScMulti;
      if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);

      for(int i = 0; i <= craftAnimationState-27; i++){
        rectangle.x = (176 + i) ScMulti;
        rectangle.y = (48 + 1 * i) ScMulti;
        rectangle.w = 1 ScMulti;
        rectangle.h = (24 - 2 * i) ScMulti;
        if(SDL_RenderFillRect(renderer, &rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
      }
    }

    if(craftAnimationState * craftingTime / 39 + craftAnimationStartTime <= SDL_GetTicks() && canContunueCraftAnimation) craftAnimationState++;
    
  }

}


/*
---------------------------------------
    Affichage suplémentaire du shop
---------------------------------------
*/

void refreshShop(SDL_Window *window , SDL_Renderer *renderer, int items[], SDL_Rect highlightRectangle, TTF_Font *font, SDL_Color *color){
  
  SDL_Rect rectangle;
  rectangle.x = 0;
  rectangle.y = 0;


// affiche l'arière plan du shop
  rectangle.w = 240 ScMulti;
  rectangle.h = 320 ScMulti;
  if(SDL_RenderCopy(renderer,texture[shopBackgroundIndex],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"shop");
  rectangle.w = 16 ScMulti;
  rectangle.h = 16 ScMulti;

  // affiche l'argent 
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

  // affiche le prix d'un item
  char priceChar[10];
  sprintf(moneyChar,"%d",price);
  surface = TTF_RenderText_Solid(font,moneyChar, *color);
  if(surface == NULL) SDL_ExitWithError("Impossible de crée la surface",window,renderer);
  SDL_Texture *priceText = SDL_CreateTextureFromSurface(renderer, surface);
  if(priceText == NULL) SDL_ExitWithError("Impossible de crée la texture",window,renderer);
  if (SDL_QueryTexture(priceText, NULL, NULL, &rectangle.w, &rectangle.h) != 0) SDL_ExitWithError("Impossible de précharger la texture",window,renderer);
  rectangle.x = 185 ScMulti;
  if (SDL_RenderCopy(renderer, priceText, NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de préafficher la texture",window,renderer);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(priceText);
    

  rectangle.w = 32 ScMulti;
  rectangle.h = 32 ScMulti;
  rectangle.x = 193 ScMulti;
  rectangle.y = 44 ScMulti;
  
  // affiche l'item du la case shop
  if (items[20] != 0){ // si il y a un item
    if(SDL_RenderCopy(renderer,texture[items[20]],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 20");
  }
  else{ // si il y a pas d'item -> l'item demendé est affiché
    if(SDL_SetRenderDrawColor(renderer,0,0,0,100)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    if(SDL_RenderCopy(renderer,texture[ask],NULL, &rectangle) != 0) SDL_ExitWithError("Impossible de charger la texture à l'écran",window,renderer,"Item 20");
    if(SDL_RenderFillRect(renderer,&rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
  }

  // met en rougeatre si ce n'est pas l'item demendé
  if(items[20] >= baseIronSword && items[20] != ask){
    if(SDL_SetRenderDrawColor(renderer,255,100,100,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
    if(SDL_RenderFillRect(renderer,&rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
    if(SDL_SetRenderDrawColor(renderer,255,255,255,150)) SDL_ExitWithError("Impossible de changer de couleur",window,renderer);
  }// met en surbrillance si c'est le bon item
  else if(items[20] >= baseIronSword){
    if(SDL_RenderFillRect(renderer,&rectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
  }

  
}


/*
---------------------------------------
          Affichage principale
---------------------------------------
*/

void refresh(SDL_Window *window , SDL_Renderer *renderer, int items[], SDL_Rect highlightRectangle, TTF_Font *font, SDL_Color *color){

  if(SDL_RenderClear(renderer) != 0) SDL_ExitWithError("Impossible d'effacer le redu de l'écran",window,renderer);

  SDL_Rect rectangle;
  rectangle.x = 0;
  rectangle.y = 0;
  rectangle.w = 32 ScMulti;
  rectangle.h = 32 ScMulti;
  
  // affichage en fonction de la page
  if(!page){
    refreshMain(window,renderer,items,highlightRectangle);
  }
  else if(page){
    refreshShop(window,renderer,items,highlightRectangle,font,color);
  }

  // Items dans l'inventaire :
  // du haut en bas par paragraphe
  // de la gauche vers la droite par individue

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

  if(SDL_RenderFillRect(renderer, &highlightRectangle) != 0) SDL_ExitWithError("Impossible crée le rectangle",window,renderer);
  

  SDL_RenderPresent(renderer);

}




