
#define ironPrice 10
#define goldPrice 20
#define diamondPrice 50
#define copperPrice 5
#define rubyPrice 30
#define saphirPrice 30
#define amethystePrice 30
#define coalPrice 5


// + ou - 5%
#define avergeAskPrice *(float)(1+(rand()%10-5)/(float)100);

// int outItem = items[19];
bool craftingCore(int inItems[], int itemCheck1, int itemCheck2, int itemCheck3);


// effectue l'acction d'achetterr un item
void buy(int items[], int selectedItem, int place = 20){

  if(selectedItem == 21){ // iron
    money -= ironPrice;
    items[place] = iron;
  }
  else if(selectedItem == 22){ // gold
    money -= goldPrice;
    items[place] = gold;
  }
  else if(selectedItem == 23){ // diamond
    money -= diamondPrice;
    items[place] = diamond;
  }
  else if(selectedItem == 24){ // copper
    money -= copperPrice;
    items[place] = copper;
  }
  else if(selectedItem == 25){ // ruby
    money -= rubyPrice;
    items[place] = ruby;
  }
  else if(selectedItem == 26){ // sahpir
    money -= saphirPrice;
    items[place] = saphir;
  }
  else if(selectedItem == 27){ // amethyste
    money -= amethystePrice;
    items[place] = amethyste;
  }
  else if(selectedItem == 28){ // coal
    money -= coalPrice;
    items[place] = coal;
  }

}

// revoie le prix d'in item achettable selon la case clické
int buyPrice(int nb){

  switch(nb){
      case 21:
        return ironPrice;
        break;
      case 22:
        return goldPrice;
        break;
      case 23:
        return diamondPrice;
        break;
      case 24:
        return copperPrice;
        break;
      case 25:
        return rubyPrice;
        break;
      case 26:
        return saphirPrice;
        break;
      case 27:
        return amethystePrice;
        break;
      case 28:
        return coalPrice;
        break;
    }
  
  return -1;
}

// génère une demande
int askGenerator(int level, int money, bool levelUpdateState){
  
  int newAsk = -1;
  int list[] = {1,2,2,3,3,3,4,4,4,4,5,5,5,5,5};
  // liste de multiplicateur pour augementer l'apparition de demande complex
  if(!levelUpdateState){
    do{
      if(level == 1){                      // [11;22] (12 item)
        newAsk = rand() % 12 + baseIronSword;
      }
      else if(level == 2 && money >= 250){ // [23;34] (12 item)
        int numlist = rand() % 3; // multiplicateur 
        int num1 = rand() % 12; // nb de 0 à 11
        newAsk = num1 + 12 * (list[numlist] -1 ) + baseIronSword;
      }
      else if(level == 3 && money >= 450){ // [35;46] (12 item)
        int numlist = rand() % 6;// multiplicateur 
        int num1 = rand() % 12; // nb de 0 à 11
        newAsk = num1 + 12 * (list[numlist] -1 ) + baseIronSword;
      }
      else if(level == 4 && money >= 800){ // [47;58] (12 item)
        int numlist = rand() % 10;// multiplicateur 
        int num1 = rand() % 12; // nb de 0 à 11
        newAsk = num1 + 12 * (list[numlist] -1 ) + baseIronSword;
      }
      else if(level == 5 && money >= 900){ //[59;66] (8 item)
        int numlist = rand() % 15;// multiplicateur 
        int num1 = 0;
        if (numlist == 5){
          int num1 = rand() % 4; // nb de 0 à 3
        }
        else{
          int num1 = rand() % 12; // nb de 0 à 11
        }
        newAsk = num1 + 12 * (list[numlist] -1 ) + baseIronSword;
      }
      else if(level == 5 && money >= 2500){ //[59;66] (8 item)
        int numlist = rand() % 15;// multiplicateur 
        int num1 = 0;
        if (numlist == 5){
          int num1 = rand() % 8; // nb de 0 à 7
        }
        else{
          int num1 = rand() % 12; // nb de 0 à 11
        }
        newAsk = num1 + 12 * (list[numlist] -1 ) + baseIronSword;
      }
    }while (newAsk == ask);
  }
  else if(levelUpdateState){
    do{
      if(level == 1){                      // [11;22] (12 item)
        newAsk = rand() % 12 + baseIronSword;
      }
      else if(level == 2 && money >= 250){ // [23;34] (12 item)
        newAsk = rand() % 12 + longIronSword;
      }
      else if(level == 3 && money >= 450){ // [35;46] (12 item)
        newAsk = rand() % 12 + bigIronSword;
      }
      else if(level == 4 && money >= 800){ // [47;58] (12 item)
        newAsk = rand() % 12 + cinquedaIronSword;
      }
      else if(level == 5 && money >= 900){ //[59;66] (8 item)
        newAsk = rand() % 4 + dragonGoldSword;
      }
      else if(level == 5 && money >= 2500){ //[59;66] (8 item)
        newAsk = rand() % 4 + dragonDiamondSword;
      }
    }while (newAsk == ask);
  }


  if (newAsk == -1){
    std::cout << "askGenerator Error\n";
    newAsk = baseIronSword;
  }
  
  return newAsk;
}

// augemente l'xp quand une item vendu est demendé : augemente la difficulté de craft
// le niveau est représenté par le nombre entier
int levelUpdate(){

  int oldLevel = (int)level;

  switch((int)level){
    case 1:
      level += 0.2;
      break;
    case 2:
      level += 0.15;
      break;
    case 3:
      level += 0.075;
      break;
    case 4:
      level += 0.04;
      break;
    case 5:
      level += 0.01;
      break;
  }

  return level-oldLevel; // renvoie 1 si le niveau à augemanté

}


// renvoie le prix d'un item à vendre
int sellPrice(int item, bool type){

  int itemPrice = -1;

  switch (item)
  {
    case -8: itemPrice = ironPrice; break;
    case -7: itemPrice = goldPrice; break;
    case -6: itemPrice = diamondPrice; break;
    case -5: itemPrice = copperPrice; break;
    case -4: itemPrice = rubyPrice; break;
    case -3: itemPrice = saphirPrice; break;
		case -2: itemPrice = amethystePrice; break;
		case -1: itemPrice = coalPrice; break;

    case baseIronSword:                 itemPrice = 20*1.2; break;
    case baseIronRubySword:             itemPrice = 60*1.2; break;
    case baseIronSaphirSword:           itemPrice = 60*1.2; break;
    case baseIronAmethysteSword:        itemPrice = 60*1.2; break;
    case baseGoldSword:                 itemPrice = 45*1.2; break;
    case baseGoldRubySword:             itemPrice = 85*1.2; break;
		case baseGoldSaphirSword:           itemPrice = 85*1.2; break;
		case baseGoldAmethysteSword:        itemPrice = 85*1.2; break;
		case baseDiamondSword:              itemPrice = 100*1.2; break;
		case baseDiamondRubySword:          itemPrice = 140*1.2; break;
		case baseDiamondSaphirSword:        itemPrice = 140*1.2; break;
		case baseDiamondAmethysteSword:     itemPrice = 140*1.2; break;

		case longIronSword:                 itemPrice = 40*1.2; break;
    case longIronRubySword:             itemPrice = 85*1.2; break;
    case longIronSaphirSword:           itemPrice = 85*1.2; break;
    case longIronAmethysteSword:        itemPrice = 85*1.2; break;
    case longGoldSword:                 itemPrice = 75*1.2; break;
    case longGoldRubySword:             itemPrice = 120*1.2; break;
    case longGoldSaphirSword:           itemPrice = 120*1.2; break;
    case longGoldAmethysteSword:        itemPrice = 120*1.2; break;
    case longDiamondSword:              itemPrice = 160*1.2; break;
		case longDiamondRubySword:          itemPrice = 205*1.2; break;
		case longDiamondSaphirSword:        itemPrice = 205*1.2; break;
		case longDiamondAmethysteSword:     itemPrice = 205*1.2; break;

		case bigIronSword:                  itemPrice = 75*1.2; break;
    case bigIronRubySword:              itemPrice = 125*1.2; break;
    case bigIronSaphirSword:            itemPrice = 125*1.2; break;
    case bigIronAmethysteSword:         itemPrice = 125*1.2; break;
    case bigGoldSword:                  itemPrice = 155*1.2; break;
    case bigGoldRubySword:              itemPrice = 205*1.2; break;
    case bigGoldSaphirSword:            itemPrice = 205*1.2; break;
    case bigGoldAmethysteSword:         itemPrice = 205*1.2; break;
    case bigDiamondSword:               itemPrice = 325*1.2; break;
		case bigDiamondRubySword:           itemPrice = 375*1.2; break;
		case bigDiamondSaphirSword:         itemPrice = 375*1.2; break;
		case bigDiamondAmethysteSword:      itemPrice = 375*1.2; break;

		case cinquedaIronSword:             itemPrice = 180*1.2; break;
    case cinquedaIronRubySword:         itemPrice = 235*1.2; break;
    case cinquedaIronSaphirSword:       itemPrice = 235*1.2; break;
    case cinquedaIronAmethysteSword:    itemPrice = 235*1.2; break;
    case cinquedaGoldSword:             itemPrice = 350*1.2; break;
    case cinquedaGoldRubySword:         itemPrice = 405*1.2; break;
    case cinquedaGoldSaphirSword:       itemPrice = 405*1.2; break;
    case cinquedaGoldAmethysteSword:    itemPrice = 405*1.2; break;
    case cinquedaDiamondSword:          itemPrice = 720*1.2; break;
		case cinquedaDiamondRubySword:      itemPrice = 775*1.2; break;
		case cinquedaDiamondSaphirSword:    itemPrice = 775*1.2; break;
		case cinquedaDiamondAmethysteSword: itemPrice = 775*1.2; break;

		case dragonGoldSword:               itemPrice = 730*1.2; break;
    case dragonGoldRubySword:           itemPrice = 790*1.2; break;
    case dragonGoldSaphirSword:         itemPrice = 790*1.2; break;
    case dragonGoldAmethysteSword:      itemPrice = 790*1.2; break;
    case dragonDiamondSword:            itemPrice = 2205*1.3; break;
    case dragonDiamondRubySword:        itemPrice = 3000; break;
		case dragonDiamondSaphirSword:      itemPrice = 3000; break;
		case dragonDiamondAmethysteSword:   itemPrice = 3000; break;
  }

  if(type){ // -10% si il n'est pas demendé
    if(item < baseIronSword) itemPrice *= 0.9;
    else itemPrice /= 1.3;
  }
  else{ // crée un prix avec un ajustement aléatoire de +-5%
    itemPrice = itemPrice avergeAskPrice;
  }
  
  return itemPrice;

}

int oldCoalUsage = 0;

// acction de craft un item
void crafting(int items[]){

  int coalNeeded = 0;

  if(canCraft <= baseDiamondAmethysteSword) coalNeeded = 1;
  else if(canCraft <= longDiamondAmethysteSword) coalNeeded = 2;
  else if(canCraft <= bigDiamondAmethysteSword) coalNeeded = 3;
  else if(canCraft <= cinquedaDiamondAmethysteSword) coalNeeded = 4;
  else if(canCraft <= dragonDiamondAmethysteSword) coalNeeded = 5;


  craftingTime = baseCraftingTime * coalNeeded;

  
  if(oldCoalUsage == 0){
    if(items[32] == coal){
      items[32] = nullIndex;
      oldCoalUsage++;
      canContunueCraftAnimation = 1;
      craftAnimationStartTime = SDL_GetTicks();
    }
  }
  else{
    if(craftAnimationState >= (int) (oldCoalUsage * 40 / coalNeeded)){
      canContunueCraftAnimation = 0;
      if(items[32] == coal){
        items[32] = nullIndex;
        oldCoalUsage++;
        canContunueCraftAnimation = 1;
        craftAnimationStartTime = SDL_GetTicks() - craftAnimationState * craftingTime / 39;
      }
    }
    else{
      canContunueCraftAnimation = 1;
    }
  }

  

  if(craftAnimationState == 39 && items[19] == nullIndex){
    craftAnimation = 0;
    craftAnimationState = 0;
    items[19] = canCraft;
    canCraft = 0;
    canContunueCraftAnimation = 0;
    oldCoalUsage = 0;
  }

}

// vérifie si un item peut être craft
void canCrafting(int items[]){
  
  if(!craftAnimation){

    canCraft = 0;
    
    // stage 1
    // iron                                                                                                           // cost : base material + coal = total
    if (craftingCore(items,iron,copper,0)) canCraft = baseIronSword;                                                  // 15 + 5 = 20
    else if (craftingCore(items,baseIronSword,copper,ruby)) canCraft = baseIronRubySword;                             // 50 + 10 = 60
    else if (craftingCore(items,baseIronSword,copper,saphir)) canCraft = baseIronSaphirSword;                         // 50 + 10 = 60
    else if (craftingCore(items,baseIronSword,copper,amethyste)) canCraft = baseIronAmethysteSword;                   // 50 + 10 = 60
    // gold
    else if (craftingCore(items,baseIronSword,gold,0)) canCraft = baseGoldSword;                                      // 35 + 10 = 45
    else if (craftingCore(items,baseGoldSword,copper,ruby)) canCraft = baseGoldRubySword;                             // 70 + 15 = 85
    else if (craftingCore(items,baseGoldSword,copper,saphir)) canCraft = baseGoldSaphirSword;                         // 70 + 15 = 85
    else if (craftingCore(items,baseGoldSword,copper,amethyste)) canCraft = baseGoldAmethysteSword;                   // 70 + 15 = 85
    // diamond
    else if (craftingCore(items,baseGoldSword,diamond,0)) canCraft = baseDiamondSword;								                // 85 + 15 = 100
    else if (craftingCore(items,baseDiamondSword,copper,ruby)) canCraft = baseDiamondRubySword;				                // 120 + 20 = 140
    else if (craftingCore(items,baseDiamondSword,copper,saphir)) canCraft = baseDiamondSaphirSword;			              // 120 + 20 = 140
    else if (craftingCore(items,baseDiamondSword,copper,amethyste)) canCraft = baseDiamondAmethysteSword;		          // 120 + 20 = 140

    // stage 2
    // iron
    else if (craftingCore(items,baseIronSword,iron,0)) canCraft = longIronSword;			                                // 25 + 15 = 40
    else if (craftingCore(items,longIronSword,copper,ruby)) canCraft = longIronRubySword;                             // 60 + 25 = 85
    else if (craftingCore(items,longIronSword,copper,saphir)) canCraft = longIronSaphirSword;			                    // 60 + 25 = 85
    else if (craftingCore(items,longIronSword,copper,amethyste)) canCraft = longIronAmethysteSword;		                // 60 + 25 = 85
    // gold
    else if (craftingCore(items,baseGoldSword,gold,0)) canCraft = longGoldSword;									                    // 55 + 20 = 75
    else if (craftingCore(items,longGoldSword,copper,ruby)) canCraft = longGoldRubySword;				                      // 90 + 30 = 120
    else if (craftingCore(items,longGoldSword,copper,saphir)) canCraft = longGoldSaphirSword;			                    // 90 + 30 = 120
    else if (craftingCore(items,longGoldSword,copper,amethyste)) canCraft = longGoldAmethysteSword;		                // 90 + 30 = 120
    // diamond
    else if (craftingCore(items,baseDiamondSword,diamond,0)) canCraft = longDiamondSword;								              // 135 + 25 = 160
    else if (craftingCore(items,longDiamondSword,copper,ruby)) canCraft = longDiamondRubySword;				                // 170 + 35 = 205
    else if (craftingCore(items,longDiamondSword,copper,saphir)) canCraft = longDiamondSaphirSword;			              // 170 + 35 = 205
    else if (craftingCore(items,longDiamondSword,copper,amethyste)) canCraft = longDiamondAmethysteSword;		          // 170 + 35 = 205

    // stage 3
    // iron
    else if (craftingCore(items,longIronSword,baseIronSword,iron)) canCraft = bigIronSword;								          	// 40 + 35 = 75
    else if (craftingCore(items,bigIronSword,copper,ruby)) canCraft = bigIronRubySword;				                        // 75 + 50 = 125
    else if (craftingCore(items,bigIronSword,copper,saphir)) canCraft = bigIronSaphirSword;			                      // 75 + 50 = 125
    else if (craftingCore(items,bigIronSword,copper,amethyste)) canCraft = bigIronAmethysteSword;		                  // 75 + 50 = 125
    // gold
    else if (craftingCore(items,longGoldSword,baseGoldSword,gold)) canCraft = bigGoldSword;								            // 110 + 45 = 155
    else if (craftingCore(items,bigGoldSword,copper,ruby)) canCraft = bigGoldRubySword;				                        // 145 + 60 = 205
    else if (craftingCore(items,bigGoldSword,copper,saphir)) canCraft = bigGoldSaphirSword;			                      // 145 + 60 = 205
    else if (craftingCore(items,bigGoldSword,copper,amethyste)) canCraft = bigGoldAmethysteSword;		                  // 145 + 60 = 205
    // diamond
    else if (craftingCore(items,longDiamondSword,baseDiamondSword,diamond)) canCraft = bigDiamondSword;							  // 270 + 55 = 325
    else if (craftingCore(items,bigDiamondSword,copper,ruby)) canCraft = bigDiamondRubySword;				                  // 305 + 70 = 375
    else if (craftingCore(items,bigDiamondSword,copper,saphir)) canCraft = bigDiamondSaphirSword;			                // 305 + 70 = 375
    else if (craftingCore(items,bigDiamondSword,copper,amethyste)) canCraft = bigDiamondAmethysteSword;		            // 305 + 70 = 375

    // stage 4
    // iron
    else if (craftingCore(items,bigIronSword,bigIronSword,iron)) canCraft = cinquedaIronSword;									      // 90 + 90 = 180
    else if (craftingCore(items,cinquedaIronSword,copper,ruby)) canCraft = cinquedaIronRubySword;				              // 125 + 110 = 235
    else if (craftingCore(items,cinquedaIronSword,copper,saphir)) canCraft = cinquedaIronSaphirSword;			            // 125 + 110 = 235
    else if (craftingCore(items,cinquedaIronSword,copper,amethyste)) canCraft = cinquedaIronAmethysteSword;		        // 125 + 110 = 235
    // gold
    else if (craftingCore(items,bigGoldSword,bigGoldSword,gold)) canCraft = cinquedaGoldSword;									      // 240 + 110 = 350
    else if (craftingCore(items,cinquedaGoldSword,copper,ruby)) canCraft = cinquedaGoldRubySword;				              // 275 + 130 = 405
    else if (craftingCore(items,cinquedaGoldSword,copper,saphir)) canCraft = cinquedaGoldSaphirSword;			            // 275 + 130 = 405
    else if (craftingCore(items,cinquedaGoldSword,copper,amethyste)) canCraft = cinquedaGoldAmethysteSword;		        // 275 + 130 = 405
    // diamond
    else if (craftingCore(items,bigDiamondSword,bigDiamondSword,gold)) canCraft = cinquedaDiamondSword;								// 590 + 130 = 720
    else if (craftingCore(items,cinquedaDiamondSword,copper,ruby)) canCraft = cinquedaDiamondRubySword;				        // 625 + 150 = 775
    else if (craftingCore(items,cinquedaDiamondSword,copper,saphir)) canCraft = cinquedaDiamondSaphirSword;			      // 625 + 150 = 775
    else if (craftingCore(items,cinquedaDiamondSword,copper,amethyste)) canCraft = cinquedaDiamondAmethysteSword;	  	// 625 + 150 = 775

    // stage 5
    // gold
    else if (craftingCore(items,cinquedaGoldSword,cinquedaGoldSword,copper)) canCraft = dragonGoldSword;						  // 485 + 245 = 730
    else if (craftingCore(items,dragonGoldSword,copper,ruby)) canCraft = dragonGoldRubySword;				                  // 520 + 270 = 790
    else if (craftingCore(items,dragonGoldSword,copper,saphir)) canCraft = dragonGoldSaphirSword;			                // 520 + 270 = 790
    else if (craftingCore(items,dragonGoldSword,copper,amethyste)) canCraft = dragonGoldAmethysteSword;		            // 520 + 270 = 790
    // diamond
    else if (craftingCore(items,dragonGoldSword,dragonGoldSword,cinquedaDiamondSword)) canCraft = dragonDiamondSword; // 1560 + 645 = 2205
    else if (craftingCore(items,dragonDiamondSword,copper,ruby)) canCraft = dragonDiamondRubySword;				            // 1595 + 670 = 2265
    else if (craftingCore(items,dragonDiamondSword,copper,saphir)) canCraft = dragonDiamondSaphirSword;			          // 1595 + 670 = 2265
    else if (craftingCore(items,dragonDiamondSword,copper,amethyste)) canCraft = dragonDiamondAmethysteSword;		      // 1595 + 670 = 2265
  }

}

// vérifie les items un par un et cherche sur tout les entrées dans n'importe quelle ordre
bool craftingCore(int inItems[], int itemCheck1, int itemCheck2, int itemCheck3){

  int inItem1 = inItems[16];
  int inItem2 = inItems[17];
  int inItem3 = inItems[18];
  bool check1 = 0;
  bool check2 = 0;
  bool check3 = 0;

  if(inItem1 == itemCheck1){
    inItem1 = inItem2;
    inItem2 = inItem3;
    // inItem3 = NULL;
    check1 = true;
  }
  else if(inItem2 == itemCheck1){
    inItem2 = inItem3;
    // inItem3 = NULL;
    check1 = true;
  }
  else if(inItem3 == itemCheck1){
    // inItem3 = NULL;
    check1 = true;
  }
  else return 0;

  if(inItem1 == itemCheck2){
    inItem1 = inItem2;
    // inItem2 = NULL;
    check2 = true;
  }
  else if(inItem2 == itemCheck2){
    // inItem2 = NULL;
    check2 = true;
  }
  else return 0;

  if(inItem1 == itemCheck3){
    // inItem1 = NULL;
    check3 = true;
  }
  else return 0;

  if(check1 && check2 && check3){
    return 1;
  }


  std::cout << "ERROR : craftigCore";
  return 0;
}

