
#define ironPrice 10
#define goldPrice 20
#define diamondPrice 50
#define copperPrice 5
#define rubyPrice 30
#define saphirPrice 30
#define amethystePrice 30
#define coalPrice 5



#define avergeAskPrice *(float)(1+(rand()%10-5)/(float)100);

// int outItem = items[19];
bool craftingCore(int inItems[], int itemCheck1, int itemCheck2, int itemCheck3);


// effectue l'acction d'achetterr un item
void buy(int items[], int selectedItem){

  if(selectedItem == 21){ // iron
    money -= ironPrice;
    items[20] = iron;
  }
  else if(selectedItem == 22){ // gold
    money -= goldPrice;
    items[20] = gold;
  }
  else if(selectedItem == 23){ // diamond
    money -= diamondPrice;
    items[20] = diamond;
  }
  else if(selectedItem == 24){ // copper
    money -= copperPrice;
    items[20] = copper;
  }
  else if(selectedItem == 25){ // ruby
    money -= rubyPrice;
    items[20] = ruby;
  }
  else if(selectedItem == 26){ // sahpir
    money -= saphirPrice;
    items[20] = saphir;
  }
  else if(selectedItem == 27){ // amethyste
    money -= amethystePrice;
    items[20] = amethyste;
  }
  else if(selectedItem == 28){ // coal
    money -= coalPrice;
    items[20] = coal;
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
int askGenerator(int level, int money){

	if(level == 1){
		return rand() % 11 + baseIronSword;
	}
	else if(level == 2 && money >= 250){
		return rand() % 27 + baseIronSword;
	}
	else if(level == 3 && money >= 400){
		return rand() % 35 + baseIronSword;
	}
	else if(level == 4 && money >= 750){
		return rand() % 47 + baseIronSword;
	}
	else if(level == 5 && money >= 2000){
		return rand() % 55 + baseIronSword;
	}
  
  return 0;
}

// augemente l'xp quand une item vendu est demendé : augemente la difficulté de craft
void levelUpdate(){

  switch((int)level){
    case 1:
      level += 0.2;
      break;
    case 2:
      level += 0.15;
      break;
    case 3:
      level += 0.01;
      break;
    case 4:
      level += 0.08;
      break;
    case 5:
      level += 0.05;
      break;
  }

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

    case baseIronSword:                 itemPrice = 25; break;
    case baseIronRubySword:             itemPrice = 70; break;
    case baseIronSaphirSword:           itemPrice = 70; break;
    case baseIronAmethysteSword:        itemPrice = 70; break;
    case baseGoldSword:                 itemPrice = 55; break;
    case baseGoldRubySword:             itemPrice = 95; break;
		case baseGoldSaphirSword:           itemPrice = 95; break;
		case baseGoldAmethysteSword:        itemPrice = 95; break;
		case baseDiamondSword:              itemPrice = 105; break;
		case baseDiamondRubySword:          itemPrice = 150; break;
		case baseDiamondSaphirSword:        itemPrice = 150; break;
		case baseDiamondAmethysteSword:     itemPrice = 150; break;

		case longIronSword:                 itemPrice = 40; break;
    case longIronRubySword:             itemPrice = 85; break;
    case longIronSaphirSword:           itemPrice = 85; break;
    case longIronAmethysteSword:        itemPrice = 85; break;
    case longGoldSword:                 itemPrice = 80; break;
    case longGoldRubySword:             itemPrice = 120; break;
    case longGoldSaphirSword:           itemPrice = 120; break;
    case longGoldAmethysteSword:        itemPrice = 120; break;
    case longDiamondSword:              itemPrice = 170; break;
		case longDiamondRubySword:          itemPrice = 210; break;
		case longDiamondSaphirSword:        itemPrice = 210; break;
		case longDiamondAmethysteSword:     itemPrice = 210; break;

		case bigIronSword:                  itemPrice = 70; break;
    case bigIronRubySword:              itemPrice = 125; break;
    case bigIronSaphirSword:            itemPrice = 125; break;
    case bigIronAmethysteSword:         itemPrice = 125; break;
    case bigGoldSword:                  itemPrice = 155; break;
    case bigGoldRubySword:              itemPrice = 195; break;
    case bigGoldSaphirSword:            itemPrice = 195; break;
    case bigGoldAmethysteSword:         itemPrice = 195; break;
    case bigDiamondSword:               itemPrice = 330; break;
		case bigDiamondRubySword:           itemPrice = 385; break;
		case bigDiamondSaphirSword:         itemPrice = 385; break;
		case bigDiamondAmethysteSword:      itemPrice = 385; break;

		case cinquedaIronSword:             itemPrice = 155; break;
    case cinquedaIronRubySword:         itemPrice = 200; break;
    case cinquedaIronSaphirSword:       itemPrice = 200; break;
    case cinquedaIronAmethysteSword:    itemPrice = 200; break;
    case cinquedaGoldSword:             itemPrice = 335; break;
    case cinquedaGoldRubySword:         itemPrice = 390; break;
    case cinquedaGoldSaphirSword:       itemPrice = 390; break;
    case cinquedaGoldAmethysteSword:    itemPrice = 390; break;
    case cinquedaDiamondSword:          itemPrice = 735; break;
		case cinquedaDiamondRubySword:      itemPrice = 770; break;
		case cinquedaDiamondSaphirSword:    itemPrice = 770; break;
		case cinquedaDiamondAmethysteSword: itemPrice = 770; break;

		case dragonGoldSword:               itemPrice = 680; break;
    case dragonGoldRubySword:           itemPrice = 735; break;
    case dragonGoldSaphirSword:         itemPrice = 735; break;
    case dragonGoldAmethysteSword:      itemPrice = 735; break;
    case dragonDiamondSword:            itemPrice = 2200; break;
    case dragonDiamondRubySword:        itemPrice = 2500; break;
		case dragonDiamondSaphirSword:      itemPrice = 2500; break;
		case dragonDiamondAmethysteSword:   itemPrice = 2500; break;
  }

  if(type){ // -10% si il n'est pas demendé
    itemPrice -= (float)itemPrice*0.1;
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
    // iron                                                                                                           // cost : 
    if (craftingCore(items,iron,copper,0)) canCraft = baseIronSword;                                                  // 15 + 5
    else if (craftingCore(items,baseIronSword,copper,ruby)) canCraft = baseIronRubySword;                             // 50 + 10
    else if (craftingCore(items,baseIronSword,copper,saphir)) canCraft = baseIronSaphirSword;                         // 50 + 10
    else if (craftingCore(items,baseIronSword,copper,amethyste)) canCraft = baseIronAmethysteSword;                   // 50 + 10
    // gold
    else if (craftingCore(items,baseIronSword,gold,0)) canCraft = baseGoldSword;                                      // 35 + 10
    else if (craftingCore(items,baseGoldSword,copper,ruby)) canCraft = baseGoldRubySword;                             // 70 + 15
    else if (craftingCore(items,baseGoldSword,copper,saphir)) canCraft = baseGoldSaphirSword;                         // 70 + 15
    else if (craftingCore(items,baseGoldSword,copper,amethyste)) canCraft = baseGoldAmethysteSword;                   // 70 + 15
    // diamond
    else if (craftingCore(items,baseGoldSword,diamond,0)) canCraft = baseDiamondSword;								                // 85 + 15
    else if (craftingCore(items,baseDiamondSword,copper,ruby)) canCraft = baseDiamondRubySword;				                // 120 + 20
    else if (craftingCore(items,baseDiamondSword,copper,saphir)) canCraft = baseDiamondSaphirSword;			              // 120 + 20
    else if (craftingCore(items,baseDiamondSword,copper,amethyste)) canCraft = baseDiamondAmethysteSword;		          // 120 + 20

    // stage 2
    // iron
    else if (craftingCore(items,baseIronSword,iron,0)) canCraft = longIronSword;			                                // 25 + 10
    else if (craftingCore(items,longIronSword,copper,ruby)) canCraft = longIronRubySword;                             // 60 + 15
    else if (craftingCore(items,longIronSword,copper,saphir)) canCraft = longIronSaphirSword;			                    // 60 + 15
    else if (craftingCore(items,longIronSword,copper,amethyste)) canCraft = longIronAmethysteSword;		                // 60 + 15
    // gold
    else if (craftingCore(items,baseGoldSword,gold,0)) canCraft = longGoldSword;									                    // 55 + 15
    else if (craftingCore(items,longGoldSword,copper,ruby)) canCraft = longGoldRubySword;				                      // 90 + 20
    else if (craftingCore(items,longGoldSword,copper,saphir)) canCraft = longGoldSaphirSword;			                    // 90 + 20
    else if (craftingCore(items,longGoldSword,copper,amethyste)) canCraft = longGoldAmethysteSword;		                // 90 + 20
    // diamond
    else if (craftingCore(items,baseDiamondSword,diamond,0)) canCraft = longDiamondSword;								              // 135 + 20
    else if (craftingCore(items,longDiamondSword,copper,ruby)) canCraft = longDiamondRubySword;				                // 170 + 25
    else if (craftingCore(items,longDiamondSword,copper,saphir)) canCraft = longDiamondSaphirSword;			              // 170 + 25
    else if (craftingCore(items,longDiamondSword,copper,amethyste)) canCraft = longDiamondAmethysteSword;		          // 170 + 25

    // stage 3
    // iron
    else if (craftingCore(items,longIronSword,baseIronSword,iron)) canCraft = bigIronSword;								          	// 40 + 20
    else if (craftingCore(items,bigIronSword,copper,ruby)) canCraft = bigIronRubySword;				                        // 75 + 25
    else if (craftingCore(items,bigIronSword,copper,saphir)) canCraft = bigIronSaphirSword;			                      // 75 + 25
    else if (craftingCore(items,bigIronSword,copper,amethyste)) canCraft = bigIronAmethysteSword;		                  // 75 + 25
    // gold
    else if (craftingCore(items,longGoldSword,baseGoldSword,gold)) canCraft = bigGoldSword;								            // 110 + 30
    else if (craftingCore(items,bigGoldSword,copper,ruby)) canCraft = bigGoldRubySword;				                        // 145 + 35
    else if (craftingCore(items,bigGoldSword,copper,saphir)) canCraft = bigGoldSaphirSword;			                      // 145 + 35
    else if (craftingCore(items,bigGoldSword,copper,amethyste)) canCraft = bigGoldAmethysteSword;		                  // 145 + 35
    // diamond
    else if (craftingCore(items,longDiamondSword,baseDiamondSword,diamond)) canCraft = bigDiamondSword;							  // 270 + 40
    else if (craftingCore(items,bigDiamondSword,copper,ruby)) canCraft = bigDiamondRubySword;				                  // 305 + 45
    else if (craftingCore(items,bigDiamondSword,copper,saphir)) canCraft = bigDiamondSaphirSword;			                // 305 + 45
    else if (craftingCore(items,bigDiamondSword,copper,amethyste)) canCraft = bigDiamondAmethysteSword;		            // 305 + 45

    // stage 4
    // iron
    else if (craftingCore(items,bigIronSword,bigIronSword,iron)) canCraft = cinquedaIronSword;									      // 90 + 45
    else if (craftingCore(items,cinquedaIronSword,copper,ruby)) canCraft = cinquedaIronRubySword;				              // 125 + 50
    else if (craftingCore(items,cinquedaIronSword,copper,saphir)) canCraft = cinquedaIronSaphirSword;			            // 125 + 50
    else if (craftingCore(items,cinquedaIronSword,copper,amethyste)) canCraft = cinquedaIronAmethysteSword;		        // 125 + 50
    // gold
    else if (craftingCore(items,bigGoldSword,bigGoldSword,gold)) canCraft = cinquedaGoldSword;									      // 240 + 65
    else if (craftingCore(items,cinquedaGoldSword,copper,ruby)) canCraft = cinquedaGoldRubySword;				              // 275 + 70
    else if (craftingCore(items,cinquedaGoldSword,copper,saphir)) canCraft = cinquedaGoldSaphirSword;			            // 275 + 70
    else if (craftingCore(items,cinquedaGoldSword,copper,amethyste)) canCraft = cinquedaGoldAmethysteSword;		        // 275 + 70
    // diamond
    else if (craftingCore(items,bigDiamondSword,bigDiamondSword,gold)) canCraft = cinquedaDiamondSword;								// 590 + 85
    else if (craftingCore(items,cinquedaDiamondSword,copper,ruby)) canCraft = cinquedaDiamondRubySword;				        // 625 + 90
    else if (craftingCore(items,cinquedaDiamondSword,copper,saphir)) canCraft = cinquedaDiamondSaphirSword;			      // 625 + 90
    else if (craftingCore(items,cinquedaDiamondSword,copper,amethyste)) canCraft = cinquedaDiamondAmethysteSword;	  	// 625 + 90

    // stage 5
    // gold
    else if (craftingCore(items,cinquedaGoldSword,cinquedaGoldSword,copper)) canCraft = dragonGoldSword;						  // 485 + 130
    else if (craftingCore(items,dragonGoldSword,copper,ruby)) canCraft = dragonGoldRubySword;				                  // 520 + 135
    else if (craftingCore(items,dragonGoldSword,copper,saphir)) canCraft = dragonGoldSaphirSword;			                // 520 + 135
    else if (craftingCore(items,dragonGoldSword,copper,amethyste)) canCraft = dragonGoldAmethysteSword;		            // 520 + 135
    // diamond
    else if (craftingCore(items,dragonGoldSword,dragonGoldSword,cinquedaDiamondSword)) canCraft = dragonDiamondSword; // 1560 + 345
    else if (craftingCore(items,dragonDiamondSword,copper,ruby)) canCraft = dragonDiamondRubySword;				            // 1595 + 350
    else if (craftingCore(items,dragonDiamondSword,copper,saphir)) canCraft = dragonDiamondSaphirSword;			          // 1595 + 350
    else if (craftingCore(items,dragonDiamondSword,copper,amethyste)) canCraft = dragonDiamondAmethysteSword;		      // 1595 + 350
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

