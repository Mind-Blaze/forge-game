/*
---------------------------------------
Index : numéro des items
---------------------------------------
*/



#define nullIndex 0

#define mainBackgroundIndex 1
#define shopBackgroundIndex 2

#define miniCoal 67


// Index

#define iron 3
#define gold 4
#define diamond 5
#define copper 6
#define ruby 7
#define saphir 8
#define amethyste 9
#define coal 10


// stage 1
// iron
#define baseIronSword 11
#define baseIronRubySword 12
#define baseIronSaphirSword 13
#define baseIronAmethysteSword 14
// gold
#define baseGoldSword 15
#define baseGoldRubySword 16
#define baseGoldSaphirSword 17
#define baseGoldAmethysteSword 18
// diamond
#define baseDiamondSword 19
#define baseDiamondRubySword 20
#define baseDiamondSaphirSword 21
#define baseDiamondAmethysteSword 22

// stage 2
// iron
#define longIronSword 23
#define longIronRubySword 24
#define longIronSaphirSword 25
#define longIronAmethysteSword 26
// gold
#define longGoldSword 27
#define longGoldRubySword 28
#define longGoldSaphirSword 29
#define longGoldAmethysteSword 30
// diamond
#define longDiamondSword 31
#define longDiamondRubySword 32
#define longDiamondSaphirSword 33
#define longDiamondAmethysteSword 34

// stage 3
// iron
#define bigIronSword 35
#define bigIronRubySword 36
#define bigIronSaphirSword 37
#define bigIronAmethysteSword 38
// gold
#define bigGoldSword 39
#define bigGoldRubySword 40
#define bigGoldSaphirSword 41
#define bigGoldAmethysteSword 42
// diamond
#define bigDiamondSword 43
#define bigDiamondRubySword 44
#define bigDiamondSaphirSword 45
#define bigDiamondAmethysteSword 46

// stage 4
// iron
#define cinquedaIronSword 47
#define cinquedaIronRubySword 48
#define cinquedaIronSaphirSword 49
#define cinquedaIronAmethysteSword 50
// gold
#define cinquedaGoldSword 51
#define cinquedaGoldRubySword 52
#define cinquedaGoldSaphirSword 53
#define cinquedaGoldAmethysteSword 54
// diamond
#define cinquedaDiamondSword 55
#define cinquedaDiamondRubySword 56
#define cinquedaDiamondSaphirSword 57
#define cinquedaDiamondAmethysteSword 58

// stage 5
// gold
#define dragonGoldSword 59
#define dragonGoldRubySword 60
#define dragonGoldSaphirSword 61
#define dragonGoldAmethysteSword 62
// diamond
#define dragonDiamondSword 63
#define dragonDiamondRubySword 64
#define dragonDiamondSaphirSword 65
#define dragonDiamondAmethysteSword 66




/*
---------------------------------------
          Initialise les image
---------------------------------------
*/

#define mainBackgroundPath "assets/gui/main7.bmp"
#define shopBackgroundPath "assets/gui/shop3.bmp"

SDL_Texture *texture[68];

void initTexturesCore(SDL_Window *window , SDL_Renderer *renderer, const char *path, int index){

  SDL_Surface *image;
  
  image = SDL_LoadBMP(path);
  if (image == NULL) SDL_ExitWithError("Impossible de charger l'image",window,renderer,path);
  texture[index] = SDL_CreateTextureFromSurface(renderer,image);
  if (texture[index] == NULL) SDL_ExitWithError("Impossible de creer la texture",window,renderer);
  image = NULL;

  SDL_FreeSurface(image);

}

void initTextures(SDL_Window *window , SDL_Renderer *renderer){

  initTexturesCore(window,renderer,mainBackgroundPath,mainBackgroundIndex);
  initTexturesCore(window,renderer,shopBackgroundPath,shopBackgroundIndex);

  initTexturesCore(window,renderer,"assets/resource/20000.bmp",iron);
  initTexturesCore(window,renderer,"assets/resource/21000.bmp",gold);
  initTexturesCore(window,renderer,"assets/resource/22000.bmp",diamond);
  initTexturesCore(window,renderer,"assets/resource/23000.bmp",copper);
  initTexturesCore(window,renderer,"assets/resource/24000.bmp",ruby);
  initTexturesCore(window,renderer,"assets/resource/25000.bmp",saphir);
  initTexturesCore(window,renderer,"assets/resource/26000.bmp",amethyste);
  initTexturesCore(window,renderer,"assets/resource/27000.bmp",coal);

  initTexturesCore(window,renderer,"assets/resource/27100.bmp",miniCoal);

  initTexturesCore(window,renderer,"assets/resource/0.bmp",nullIndex);
  initTexturesCore(window,renderer,"assets/item/10000.bmp",baseIronSword);
  initTexturesCore(window,renderer,"assets/item/10001.bmp",baseIronRubySword);
  initTexturesCore(window,renderer,"assets/item/10002.bmp",baseIronSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10003.bmp",baseIronAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10010.bmp",baseGoldSword);
  initTexturesCore(window,renderer,"assets/item/10011.bmp",baseGoldRubySword);
  initTexturesCore(window,renderer,"assets/item/10012.bmp",baseGoldSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10013.bmp",baseGoldAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10020.bmp",baseDiamondSword);
  initTexturesCore(window,renderer,"assets/item/10021.bmp",baseDiamondRubySword);
  initTexturesCore(window,renderer,"assets/item/10022.bmp",baseDiamondSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10023.bmp",baseDiamondAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10100.bmp",longIronSword);
  initTexturesCore(window,renderer,"assets/item/10101.bmp",longIronRubySword);
  initTexturesCore(window,renderer,"assets/item/10102.bmp",longIronSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10103.bmp",longIronAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10110.bmp",longGoldSword);
  initTexturesCore(window,renderer,"assets/item/10111.bmp",longGoldRubySword);
  initTexturesCore(window,renderer,"assets/item/10112.bmp",longGoldSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10113.bmp",longGoldAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10120.bmp",longDiamondSword);
  initTexturesCore(window,renderer,"assets/item/10121.bmp",longDiamondRubySword);
  initTexturesCore(window,renderer,"assets/item/10122.bmp",longDiamondSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10123.bmp",longDiamondAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10200.bmp",bigIronSword);
  initTexturesCore(window,renderer,"assets/item/10201.bmp",bigIronRubySword);
  initTexturesCore(window,renderer,"assets/item/10202.bmp",bigIronSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10203.bmp",bigIronAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10210.bmp",bigGoldSword);
  initTexturesCore(window,renderer,"assets/item/10211.bmp",bigGoldRubySword);
  initTexturesCore(window,renderer,"assets/item/10212.bmp",bigGoldSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10213.bmp",bigGoldAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10220.bmp",bigDiamondSword);
  initTexturesCore(window,renderer,"assets/item/10221.bmp",bigDiamondRubySword);
  initTexturesCore(window,renderer,"assets/item/10222.bmp",bigDiamondSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10223.bmp",bigDiamondAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10300.bmp",cinquedaIronSword);
  initTexturesCore(window,renderer,"assets/item/10301.bmp",cinquedaIronRubySword);
  initTexturesCore(window,renderer,"assets/item/10302.bmp",cinquedaIronSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10303.bmp",cinquedaIronAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10310.bmp",cinquedaGoldSword);
  initTexturesCore(window,renderer,"assets/item/10311.bmp",cinquedaGoldRubySword);
  initTexturesCore(window,renderer,"assets/item/10312.bmp",cinquedaGoldSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10313.bmp",cinquedaGoldAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10320.bmp",cinquedaDiamondSword);
  initTexturesCore(window,renderer,"assets/item/10321.bmp",cinquedaDiamondRubySword);
  initTexturesCore(window,renderer,"assets/item/10322.bmp",cinquedaDiamondSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10323.bmp",cinquedaDiamondAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10410.bmp",dragonGoldSword);
  initTexturesCore(window,renderer,"assets/item/10411.bmp",dragonGoldRubySword);
  initTexturesCore(window,renderer,"assets/item/10412.bmp",dragonGoldSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10413.bmp",dragonGoldAmethysteSword);
  initTexturesCore(window,renderer,"assets/item/10420.bmp",dragonDiamondSword);
  initTexturesCore(window,renderer,"assets/item/10421.bmp",dragonDiamondRubySword);
  initTexturesCore(window,renderer,"assets/item/10422.bmp",dragonDiamondSaphirSword);
  initTexturesCore(window,renderer,"assets/item/10423.bmp",dragonDiamondAmethysteSword);

}