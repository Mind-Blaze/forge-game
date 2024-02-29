#include <iostream>
#define ironPrice 10
#define goldPrice 20
#define diamondPrice 50
#define copperPrice 5
#define rubyPrice 30
#define saphirPrice 30
#define amethystePrice 30


#define ironIndex 66
#define goldIndex 67
#define diamondIndex 68
#define copperIndex 69
#define rubyIndex 70
#define saphirIndex 71
#define amethysteIndex 72

// int outItem = items[19];
bool craftingCore(int inItems[], int itemCheck1, int itemCheck2, int itemCheck3);

void buy(int items[], int *money, int selectedItem){

  if(selectedItem == 21){ // iron
    *money -= ironPrice;
    items[20] = 66;
  }
  else if(selectedItem == 22){ // gold
    *money -= goldPrice;
    items[20] = 67;
  }
  else if(selectedItem == 24){ // diamond
    *money -= diamondPrice;
    items[20] = 68;
  }
  else if(selectedItem == 23){ // copper
    *money -= copperPrice;
    items[20] = 69;
  }
  else if(selectedItem == 25){ // ruby
    *money -= rubyPrice;
    items[20] = 70;
  }
  else if(selectedItem == 26){ // sahpir
    *money -= saphirPrice;
    items[20] = 71;
  }
  else if(selectedItem == 28){ // amethyste
    *money -= amethystePrice;
    items[20] = 72;
  }
  else if(selectedItem == 27){ // coal
    *money -= 5;
    items[20] = 73;
  }

}

int sellPrice(int item){

  

  switch (item)
  {
    case 2: return 20; break;
    case 3: return 60; break;
    case 4: return 60; break;
    case 5: return 60; break;
    case 6: return 45; break;
    case 7: return 80; break;
		case 8: return 80; break;
		case 9: return 80; break;
		case 10: return 95; break;
		case 11: return 130; break;
		case 12: return 130; break;
		case 13: return 130; break;
		case 14: return 30; break;
    case 15: return 70; break;
    case 16: return 70; break;
    case 17: return 70; break;
    case 18: return 65; break;
    case 19: return 100; break;
    case 20: return 100; break;
    case 21: return 100; break;
    case 22: return 150; break;
		case 23: return 185; break;
		case 24: return 185; break;
		case 25: return 185; break;
		case 26: return 50; break;
    case 27: return 90; break;
    case 28: return 90; break;
    case 29: return 90; break;
    case 30: return 125; break;
    case 31: return 160; break;
    case 32: return 160; break;
    case 33: return 160; break;
    case 34: return 290; break;
		case 35: return 340; break;
		case 36: return 340; break;
		case 37: return 340; break;
		case 38: return 110; break;
    case 39: return 150; break;
    case 40: return 150; break;
    case 41: return 150; break;
    case 42: return 270; break;
    case 43: return 420; break;
    case 44: return 420; break;
    case 45: return 420; break;
    case 46: return 650; break;
		case 47: return 680; break;
		case 48: return 680; break;
		case 49: return 680; break;
		case 50: return 550; break;
    case 51: return 600; break;
    case 52: return 600; break;
    case 53: return 600; break;
    case 54: return 1800; break;
    case 55: return 2000; break;
		case 56: return 2000; break;
		case 57: return 2000; break;
    
    case ironIndex: return ironPrice; break;
    case goldIndex: return goldPrice; break;
    case diamondIndex: return diamondPrice; break;
    case copperIndex: return copperPrice; break;
    case rubyIndex: return rubyPrice; break;
    case saphirIndex: return saphirPrice; break;
		case amethysteIndex: return amethystePrice; break;
  }
  
  return -1;

}

void crafting(int items[]){

  // 66 = iron
  // 67 = gold
  // 68 = diamond
  // 69 = copper
  // 70 = ruby
  // 71 = saphir
  // 72 = amethyste
  // 73 = coal
  
  
  // stage 1
  // iron                                                                       // cost : 
  if (craftingCore(items,ironIndex,copperIndex,0)) items[19] = 2;               // 15
  else if (craftingCore(items,2,copperIndex,rubyIndex)) items[19] = 3;          // 50
  else if (craftingCore(items,2,copperIndex,saphirIndex)) items[19] = 4;        // 50
  else if (craftingCore(items,2,copperIndex,amethysteIndex)) items[19] = 5;     // 50
  // gold
  else if (craftingCore(items,2,goldIndex,0)) items[19] = 6;                    // 35
  else if (craftingCore(items,6,copperIndex,rubyIndex)) items[19] = 7;          // 70
  else if (craftingCore(items,6,copperIndex,saphirIndex)) items[19] = 8;        // 70
  else if (craftingCore(items,6,copperIndex,amethysteIndex)) items[19] = 9;     // 70
  // diamond
  else if (craftingCore(items,6,diamondIndex,0)) items[19] = 10;								// 85
  else if (craftingCore(items,10,copperIndex,rubyIndex)) items[19] = 11;				// 120
  else if (craftingCore(items,10,copperIndex,saphirIndex)) items[19] = 12;			// 120
  else if (craftingCore(items,10,copperIndex,amethysteIndex)) items[19] = 13;		// 12063
  else if (craftingCore(items,14,copperIndex,saphirIndex)) items[19] = 16;			// 60
  else if (craftingCore(items,14,copperIndex,amethysteIndex)) items[19] = 17;		// 60
  // gold
  else if (craftingCore(items,14,goldIndex,0)) items[19] = 18;									// 55
  else if (craftingCore(items,18,copperIndex,rubyIndex)) items[19] = 19;				// 90
  else if (craftingCore(items,18,copperIndex,saphirIndex)) items[19] = 20;			// 90
  else if (craftingCore(items,18,copperIndex,amethysteIndex)) items[19] = 21;		// 90
  // diamond
  else if (craftingCore(items,18,diamondIndex,0)) items[19] = 22;								// 135
  else if (craftingCore(items,22,copperIndex,rubyIndex)) items[19] = 23;				// 170
  else if (craftingCore(items,22,copperIndex,saphirIndex)) items[19] = 24;			// 170
  else if (craftingCore(items,22,copperIndex,amethysteIndex)) items[19] = 25;		// 170

  // stage 3
  // iron
  else if (craftingCore(items,14,2,ironIndex)) items[19] = 26;									// 40
  else if (craftingCore(items,26,copperIndex,rubyIndex)) items[19] = 27;				// 75
  else if (craftingCore(items,26,copperIndex,saphirIndex)) items[19] = 28;			// 75
  else if (craftingCore(items,26,copperIndex,amethysteIndex)) items[19] = 29;		// 75
  // gold
  else if (craftingCore(items,18,6,goldIndex)) items[19] = 30;									// 110
  else if (craftingCore(items,30,copperIndex,rubyIndex)) items[19] = 31;				// 145
  else if (craftingCore(items,30,copperIndex,saphirIndex)) items[19] = 32;			// 145
  else if (craftingCore(items,30,copperIndex,amethysteIndex)) items[19] = 33;		// 145
  // diamond
  else if (craftingCore(items,22,10,diamondIndex)) items[19] = 34;							// 270
  else if (craftingCore(items,34,copperIndex,rubyIndex)) items[19] = 35;				// 305
  else if (craftingCore(items,34,copperIndex,saphirIndex)) items[19] = 36;			// 305
  else if (craftingCore(items,34,copperIndex,amethysteIndex)) items[19] = 37;		// 305

  // stage 4
  // iron
  else if (craftingCore(items,26,26,ironIndex)) items[19] = 38;									// 90
  else if (craftingCore(items,38,copperIndex,rubyIndex)) items[19] = 39;				// 125
  else if (craftingCore(items,38,copperIndex,saphirIndex)) items[19] = 40;			// 125
  else if (craftingCore(items,38,copperIndex,amethysteIndex)) items[19] = 41;		// 125
  // gold
  else if (craftingCore(items,30,30,goldIndex)) items[19] = 42;									// 240
  else if (craftingCore(items,42,copperIndex,rubyIndex)) items[19] = 43;				// 375
  else if (craftingCore(items,42,copperIndex,saphirIndex)) items[19] = 44;			// 275
  else if (craftingCore(items,42,copperIndex,amethysteIndex)) items[19] = 45;		// 275
  // diamond
  else if (craftingCore(items,34,34,goldIndex)) items[19] = 46;									// 590
  else if (craftingCore(items,46,copperIndex,rubyIndex)) items[19] = 47;				// 625
  else if (craftingCore(items,46,copperIndex,saphirIndex)) items[19] = 48;			// 625
  else if (craftingCore(items,46,copperIndex,amethysteIndex)) items[19] = 49;		// 625

  // stage 5
  // gold
  else if (craftingCore(items,42,42,copperIndex)) items[19] = 50;								// 485
  else if (craftingCore(items,50,copperIndex,rubyIndex)) items[19] = 51;				// 520
  else if (craftingCore(items,50,copperIndex,saphirIndex)) items[19] = 52;			// 520
  else if (craftingCore(items,50,copperIndex,amethysteIndex)) items[19] = 53;		// 520
  // diamond
  else if (craftingCore(items,50,50,46)) items[19] = 54;												// 1560
  else if (craftingCore(items,54,copperIndex,rubyIndex)) items[19] = 55;				// 1595
  else if (craftingCore(items,54,copperIndex,saphirIndex)) items[19] = 56;			// 1595
  else if (craftingCore(items,54,copperIndex,amethysteIndex)) items[19] = 57;		// 1595
  

}
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
    inItems[16] = 0;
    inItems[17] = 0;
    inItems[18] = 0;
    return 1;
  }


  


  std::cout << "ERROR : craftigCore";
  return 0;
}

