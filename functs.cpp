#include <iostream>
#include <cstdlib>
#include "functs.h"
#include <cstring>
#include <vector>

using namespace std;

/////////////////////////////////////////////

Ecosystem:: Ecosystem(){
	//Arxikopoihsh / Klhsh ths create map

	dayOfYear=0;
	hourOfDay=0;
	Season=0;
	create_map();
}

Ecosystem:: ~Ecosystem(){
	cout<< endl << "Ecosystem Deleted!!!"<<endl;
}

void Ecosystem:: create_map(){

	// Eisagwgh mege8ous map / Dhmiourgia map
	int size=0;
	cout << "Please enter map size (>=10)" << endl;
	cin >> size;
	while(size<10){
		cout << "Invalid map size!! Please enter a valid size!" << endl;
		cin >> size;
	}
	TMap=new Map(size);
}

void Ecosystem:: delete_map(){
	//Khsh delete_map / Dhiagrafh map
	TMap->delete_map();
	delete TMap;
} 

void Ecosystem:: print_map(){
	// Ektypwsh xarth
	TMap->print_map();
}

void Ecosystem:: PlacePlants(int g,int a,int m,int o,int p){	// Ka8e metavlhth antixtoixei sto anallgo fyto kai periexei to arxiko plh8os tou
	TMap->PlacePlants(g,a,m,o,p);
}

void Ecosystem:: PlaceAnimals(int d,int r,int m,int s,int f,int w,int b){
	// Klhsh ths put_animal me tyxaies syntetagmenes (to 1)
	TMap->put_animal(d,'d',1);
	TMap->put_animal(r,'r',1);
	TMap->put_animal(m,'m',1);
	TMap->put_animal(s,'s',1);
	TMap->put_animal(f,'f',1);
	TMap->put_animal(w,'w',1);
	TMap->put_animal(b,'b',1);
}


void Ecosystem:: printTilesp(){	// Ektypwsh xarth
	TMap->printTilesp();
}

void Ecosystem:: printAnimals(){	// EKtypwsh pinaka zwwn me tis syntetagmenes kai to hunger count tous
	TMap->printAnimals();
}

void Ecosystem:: RunEcosystem(int day,int x){
	int newSeason=x;		//Arxikh epoxh

	dayOfYear=0;	//=1
	ApplySeason(newSeason);		//Efarmogh twn xarakthristikwn ths arxikhs epoxhs

// Arxh tou kykloy ths prosomoiwshs

	while(dayOfYear<=day){

	//Allagh tou new season otan xrhazetai
		newSeason=((dayOfYear)/90)+x;		// allagh epoxhs se 30 meres	// (d-1)/90 +x
		while(newSeason>4){
			newSeason=newSeason%4;
		}

	//Efarmogh ths neas epoxhs
		if(newSeason!=Season){
			ApplySeason(newSeason);
			//printAnimals();


		}

	//Reset hmeras
		DailyReset();
		
	//Animal Movement / Eating 
		while(hourOfDay<24){
			AnimalMovement(); //cout<<"ANIMALS MOVED" <<endl;
			AnimalEating(); //cout<< "tried to eat"<<endl;
			hourOfDay++;
		}

	//Afairesh nekrwn ontothtwn
		TMap->CheckDeadEntities();

	//Animal /Plant Breed
		if(dayOfYear%AHbreedingRepPeriod==0){
			TMap->AHBreed();
		}
		if(dayOfYear%ACbreedingRepPeriod==0)
			TMap->ACBreed();
		if(PbreedingRepPeriod!=0){
			if(dayOfYear%PbreedingRepPeriod==0)
				TMap->PBreed();
		}
		
	}

//Ektpywseis Teloys
	cout << endl << "///////////////////" << endl << endl;
	cout << "END OF SIMULATION !!! " << endl;
	cout << endl << "///////////////////" << endl << endl;

}

void Ecosystem:: ApplySeason(int x){
//Katallhlh allagh twn metavlhtwn gia PGrowth - AGrowth - PBreedingPeriod - AH/ACBreedingPeriod analoga me thn epoxh

	cout << endl << "///////////////////" << endl << endl;
	Season=x;
	if(x==1){		//Anoiksh
		PbreedingRepPeriod=10;
		PgrowthPeriod=5;

		AgrowthPeriod=20;
		AHbreedingRepPeriod=12;
		ACbreedingRepPeriod=11;

		TMap->Wake_Up();
		cout<<"New Season Applied Anoiksh"<<endl;
	}
	if(x==2){		//Kalokairi
		PbreedingRepPeriod=10;
		PgrowthPeriod=10;

		AgrowthPeriod=30;
		AHbreedingRepPeriod=8;
		ACbreedingRepPeriod=9;
		cout<<"New Season Applied Kalokairi"<<endl;
	}
	if(x==3){		//Fthinoporo
		PbreedingRepPeriod=20;
		PgrowthPeriod=0; //anti gia 0 gia na ginetai h diairesh

		AgrowthPeriod=15;
		AHbreedingRepPeriod=5;
		ACbreedingRepPeriod=9;
		cout<<"New Season Applied F8inopwro"<<endl;
	}
	if(x==4){		//Xeimwnas
		PbreedingRepPeriod=0;
		PgrowthPeriod=10;

		AgrowthPeriod=30;
		AHbreedingRepPeriod=18;
		ACbreedingRepPeriod=10;

		TMap->Sleep();	//Xeimeria narkh gia marmota kai arkouda
		cout<<"New Season Applied Xeimwnas"<<endl;
	}

//Ektypwseis Systhmatos
	PrintSystem();
	PrintPlantStatistics();
	PrintAnimalStatistics();
	
}



void Ecosystem:: DailyReset(){
	int temp=0;

	dayOfYear++;	//epomenh mera
	hourOfDay=0;	//mhdenismos ths monadas xronou

	TMap->set_Hungry(1);	//Arxikopiohsh ths peinas
	TMap->set_eatenFood(0);	//Arxikopoihsh tou faghtou pou exei fagw8ei apo ka8e zwo masemse mia mera

//AGrowth -PGrowth
	TMap->AGrowth(dayOfYear,AHbreedingRepPeriod,ACbreedingRepPeriod);

	if(PgrowthPeriod!=0){
		if(dayOfYear%PgrowthPeriod==0)
			TMap->PGrowth();
	}
}

int Ecosystem:: get_dayOfYear(){ // Epistrofh ths meras
	return dayOfYear;
}

int Ecosystem:: getAHbreedingRepPeriod(){	// Epistorfh tou AHBreeding Period
	return AHbreedingRepPeriod;
}

int Ecosystem:: getACbreedingRepPeriod(){	// Epistrofh tou AC Breeding Period
	return ACbreedingRepPeriod;
}

void Ecosystem:: AnimalMovement(){		// Klhsh ths ANimalMovement 
	TMap->AnimalMovement();
}

void Ecosystem:: AnimalEating(){		// Klhsh ths AnimalEating
	TMap->AnimalEating();
}

void Ecosystem:: PrintPlantStatistics(){	// KLjhsh ths Print PL Statistics gia Ektypwsh twn statistikwn twn fytwn
	TMap->PrintPlantStatistics();
}

void Ecosystem:: PrintAnimalStatistics(){	//Klhsh ths PrintAnimalStatixtics gia ektypwsh twn statistikwn twn zwwn
	TMap->PrintAnimalStatistics();
}

void Ecosystem:: PrintSystem(){			//Ektypwsh Systhmatos
	cout<<"DAY " <<dayOfYear<<endl;
	TMap->Print();
	TMap->PrintTotalLife();
}

/////////////////////////////////////////////


Map:: Map(int TerrainSize): terrainSize(TerrainSize){	//Crate Map -> desmeush pinaka
	
	map=new Tile*[terrainSize];
	
	int x=0;

	while(x<terrainSize){
		map[x]=new Tile[terrainSize];
		x++;
	}
//Arxikopoihsh metavlhtwn gia mege8os pinaka zwwn / plh8os lofwn 
	AnimalsTSize=0;
	HillsSize=0;

	set_hills();	// orismos ari8mou llofwn analoga me to Terrain Size
	MapGenerator();
}

Map:: ~Map(){
}

void Map:: delete_map(){// Diagrafh Xarth
	int x=0;
	int y=0;

// Deleting plants & map
	while(x<terrainSize){
		while(y<terrainSize){
			map[x][y].delete_plant();
			y++;
		}
		y=0;
		delete [] map[x];
		x++;
	}

	delete [] map;

// Deleting Anmal array
	while(AnimalsTSize>=0){
		delete AnimalsT[AnimalsTSize];
		AnimalsTSize--;
	}
}


void Map:: print_map(){	// EKtypwsh xarth
	int temp1=0;
	int temp2=0;

	while(temp1<terrainSize){
		while(temp2<terrainSize){
			cout<< map[temp1][temp2].get_tr()<<" ";
			temp2++;
		}
		cout << endl;
		temp2=0;
		temp1++;
	}
	//cout << "----------------" << endl;
}

void Map:: MapGenerator(){ 	// DHmiourgia River ~ Lake ~ HIlls ~ Meadow
	GenerateRiver();
	GenerateLake();
	GenerateHills();
	GenerateMeadow();
	
	
}

void Map:: GenerateRiver(){ 	// Dhmiourgia river
	int x=0;					// Tyxaio arxiko tile
	int y=rand() % (terrainSize-9) + 5;
	int flag=0;
	
	map[x] [y].change_to_w();	//Allagh arxikou token perivalontos se nero

	x++;	//epomenh seira

	while(x<terrainSize){
		flag=rand() % 3;	//an to flag ginei 1 to patami 8a perikleinei
		if(flag==1){		
			flag=rand() % 2;	//an to flag=0 to potami 8a paei deksia/=1 aristera
			if(flag==0){	//Deksia
				flag=rand() % 2;// flag=0 ->1 tile /~/ flag=1 ->2 tiles	
				if(flag==0 && y<terrainSize-1){
					y++;
				}
				if(flag==1 && y<terrainSize-2){
					y++;
					map[x][y].change_to_w();
					y++;
				}
			}
			
			if(flag==1){	//Aristera
				flag=rand() % 2 ;//flag=0 1 tile flag=1 2 tiles	
				if(flag==0 && y>1){
					y--;
				}
				if(flag==1 && y>2){
					y--;
					map[x][y].change_to_w();
					y--;
				}
			}
		}
		map[x][y].change_to_w();
		x++;
	}
}

void Map:: GenerateLake(){	//Dmiourgia Lake
	cout << "Please enter lake size (<" << terrainSize << ")" << endl;
	cin >> lakeSize;

//Lake siZE
	while(lakeSize>terrainSize){
		cout << "Lake too big!!! Please enter a valid lake size" << endl;
		cin >> lakeSize;
	}

//Arxikes syntetagmenes
	int x=rand() % (terrainSize-lakeSize);		//tyxaia tiles
	int y=rand() % (terrainSize-lakeSize);

	int x1=x;
	int y1=y;

	while(x1<x+lakeSize){
		while(y1<y+lakeSize){
			map[x1][y1].change_to_w();
			y1++;
		}
		y1=y;
		x1++;
	}
}


void Map:: set_hills(){
	// To plh8os to lofvn eksaratai apo to terrain Size
	hills=terrainSize/5;
}
	
void Map:: GenerateHills(){	// Topo8ethsh lofwn
	int count=hills;
	int size;
	int x,x1,y1,y;
	int flag=0;
	
	while(count>0){
		size=rand() % 3 + 2;
		HillsSize+=size*size;
		while(flag==0){
			x=rand() % (terrainSize-size);		//tyxaia  ARXIKA tiles ENOS lofou
			y=rand() % (terrainSize-size);

			x1=x;
			y1=y;
			flag=1;
		// Elegxos gia th dia8esimothta twn tiles me bash tis sygkekrimenes arxikes syntetagmenes
		// An to flag ginei 0 o lofos den topo8eteitai gt 8a yperkalypte tile diaforetikou terrain
			while(x1<x+size){
				while(y1<y+size){
					if(map[x1][y1].get_tr()=='#' || map[x1][y1].get_tr()=='^'){
						flag=0;
					}
					y1++;
				}
				y1=y;
				x1++;
			}
			if(flag==1){		// Gemisama twn tiles - Topo8ethsh lofou
				x1=x;
				y1=y;
				flag=1;
				while(x1<x+size){
					while(y1<y+size){
						map[x1][y1].change_to_h();
						y1++;
					}
					y1=y;
					x1++;
				}
			}
		}
		count--;
		flag=0;
	}
}

void Map:: GenerateMeadow(){ //Dhmiourgia pediadas 
	int x=0;
	int y=0;

	while(x<terrainSize){
		while(y<terrainSize){
			if(map[x][y].get_tr()=='~'){		// To "~" apotelei to arxiko char ka8e tile
				map[x][y].change_to_m();	// Allagh tou token edafous se pediada
			}
			y++;
		}
		x++;
		y=0;
	}
}	

int Map:: get_terrainSize(){	// Epistrofh tou mege8ous tou xarth
	return terrainSize;
}

void Map:: printTilesp(){	//ektypwsh xarth me vash ta TOKEN TWN FYTWN
	int x=0;
	int y=0;
	cout<<"printing token map" <<endl;
	while(x<terrainSize){
		while(y<terrainSize){
			cout<< map[x][y].get_plant()<< " ";
			y++;
		}
		y=0;
		x++;
		cout<< endl;
	}
}

void Map:: Print(){	//Ektypwsh xarth me vash ta token twn ftywn KAI tou edafous
	int x=0;
	int y=0;

	cout << endl;
	cout << "   ";
	while(y<terrainSize){
		cout <<" ";
		
		cout << y;
		if(y<10)
			cout<< " ";
		y++;
	}
	y=0;
	cout<<endl;
	while(x<terrainSize){
		cout << x ;
		if(terrainSize>=10 && x <10)
			cout<< " ";
		cout<< " ";
		while(y<terrainSize){
			cout<< " ";
			if(map[x][y].get_plant()!='E')	// "E" apotelei to token fytou pou exei to tile otan den yparxei kapoio fyto se auto to tile
				cout<< map[x][y].get_plant()<< " ";
			else
				cout<< map[x][y].get_tr()<<" ";
				
				
			y++;
		}
		y=0;
		x++;
		cout << endl;
	}
	cout << endl;
}

void Map:: PrintTotalLife(){	//Ektypwsh plh8ous ftywn kai zwwn
	int x=0,y=0,count=0,h=0,c=0;

	cout << endl;

// Prospelash pinaka xarth gia ta fyta
	while(x<terrainSize){
		while(y<terrainSize){
			if(map[x][y].get_plflag()==1)
				count++;
			y++;
		}
		x++;
		y=0;
	}

	cout << "Total Plants: " << count << endl;

	cout << "Total Animals: " << AnimalsTSize << endl;
	
	count=0;

// Ektypwsh plh8ous sarkofag2n kai fytofagwn
	while(count<AnimalsTSize){
		if(AnimalsT[count]->get_token()=='H')
			h++;
		else
			c++;
		count++;
	}

	cout << " ~>Herbivores Animals: " << h << endl;
	cout << " ~>Carnivores Animals: " << c << endl;
}

void Map:: PlacePlants(int g,int a,int m,int o,int p){ //Elegxos ari8mou fytwn

// Elegxos tou arxikou katallhlothta tou plh8ous fytwn analoga me to Terrain kai to Lake Size tou xrhsth

	if(a>terrainSize+(lakeSize*lakeSize)-lakeSize)
		a=terrainSize+(lakeSize*lakeSize)-lakeSize;

	if(p>HillsSize)
		p=HillsSize;

	if(g>( (terrainSize*terrainSize) - (terrainSize+lakeSize+lakeSize*lakeSize) - HillsSize ) )
		g=(terrainSize*terrainSize) - (terrainSize+lakeSize+lakeSize*lakeSize) - HillsSize;

	if(o>( (terrainSize*terrainSize) - (terrainSize+lakeSize+lakeSize*lakeSize)  - HillsSize - g) )
		o=(terrainSize*terrainSize) - (terrainSize+lakeSize+lakeSize*lakeSize) - HillsSize - g;

	if(m>( (terrainSize*terrainSize) - (terrainSize+lakeSize*lakeSize) - g - p - o ) )
		m=(terrainSize*terrainSize) - (terrainSize+lakeSize+lakeSize*lakeSize) - g - p - o ;



// Topo8ethsh fytwn
	put_plant(a,'A'); //cout<<"fyki placed!" <<endl;
	put_plant(p,'P'); //cout<<"p placed!" <<endl;

	put_plant(g,'G'); //cout<< "grass placed!" <<endl;
	put_plant(m,'M'); //cout<<"m placed!" <<endl;
	put_plant(o,'O'); //cout<<"o placed!" <<endl;
}

void Map:: put_plant(int num,char p,int random,int x,int y){ //Top8ethsh fytwn
	
	while(num>0){	// to num antistoixei sto plh8os twn fytwn pou prepei na topo8eth8oyn
		if(random==0){	//tyxaies syntetagmenes
			x=rand()% terrainSize;
			y=rand()% terrainSize;
		}

	// Topo8ethsh twn fytwn
		if(p=='G'){		
			if(map[x][y].get_tr()=='"' && map[x][y].get_plflag()==0){
				map[x][y].set_grass();
				num--;
			}
		}
		else if(p=='A'){
			if(map[x][y].get_tr()=='#' && map[x][y].get_plflag()==0){
				map[x][y].set_algae();
				num--;
			}
		}
		else if(p=='M'){
			if(map[x][y].get_tr()!='#' && map[x][y].get_plflag()==0){
				map[x][y].set_maple();
				num--;
			}
		}
		else if(p=='O'){
			if(map[x][y].get_tr()=='"' && map[x][y].get_plflag()==0){
				map[x][y].set_oak();
				num--;
			}
		}
		else if(p=='P'){
			if(map[x][y].get_tr()=='^' && map[x][y].get_plflag()==0){
				map[x][y].set_pine();
				num--;
			}
		}
	}
}

void Map:: put_animal(int num,char a,int flag,int x, int y){	//klhsh me flag=1 -> rand x,y

	int temp=AnimalsTSize;	//mege8os pinaka zwwn

	while(num>0){		//num= plh8os zwwwn pou prepei na topo8eth8oun apo ka8e eidos

		temp=AnimalsTSize;

		if(flag==1){	//paragwgh tyxaiwn x,y an xreiazontai
			x=rand() % terrainSize;
			y=rand() % terrainSize;
		}		

		if(a=='d' && (map[x][y].get_tr()=='"' || flag==0)){
			if(flag==1)
				AnimalsT.push_back(new Deer(flag,x,y));	//klhsh tou constr me flag gia na exoun max sts ta zwa
			else
				AnimalsT.push_back(new Deer(x,y));
			AnimalsTSize++;			
			num--;
		}

		else if(a=='r' && (map[x][y].get_tr()=='"' || flag==0)){
			if(flag==1)
				AnimalsT.push_back(new Rabbit(flag,x,y));
			else
				AnimalsT.push_back(new Rabbit(x,y));
			num--;
			AnimalsTSize++;
		}

		else if(a=='m' && (map[x][y].get_tr()=='"' || flag==0)){
			if(flag==1)
				AnimalsT.push_back(new Marmot(flag,x,y));
			else
				AnimalsT.push_back(new Marmot(x,y));
			num--;
			AnimalsTSize++;
		}

		else if(a=='s' && (map[x][y].get_tr()=='#' || flag==0)){
			AnimalsT.push_back(new Salmon(flag,x,y));
			num--;
			AnimalsTSize++;
		}

		else if(a=='f' && (map[x][y].get_tr()=='"' || flag==0)){
			if(flag==1)
				AnimalsT.push_back(new Fox(flag,x,y));
			else
				AnimalsT.push_back(new Fox(x,y));
			num--;
			AnimalsTSize++;
		}

		else if(a=='w' && (map[x][y].get_tr()!='#' || flag==0)){
			if(flag==1)
				AnimalsT.push_back(new Wolf(flag,x,y));
			else
				AnimalsT.push_back(new Wolf(x,y));
			num--;
			AnimalsTSize++;
		}

		else if(a=='b' && (map[x][y].get_tr()=='^' || flag==0)){
			if(flag==1)
				AnimalsT.push_back(new Bear(flag,x,y));
			else
				AnimalsT.push_back(new Bear(x,y));
			num--;
			AnimalsTSize++;
		}
	}
}


void Map:: printAnimals(){	//Ektypwsh zwwn: onoma, stntetagmenes, hunger
	int temp=0;
	cout<<endl;
	while(temp<AnimalsTSize){
		cout<< AnimalsT[temp]->get_name() << " " << AnimalsT[temp]->get_x() << " " << AnimalsT[temp]->get_y() << " hunger:"<< AnimalsT[temp]->get_Hungry()  << endl;
		temp++;
	}
	cout <<endl;
}

int Map:: get_AnimalsTSize(){ 	// Epistrodfh tou mege8ou s tou pinaka zwwn
	return AnimalsTSize;
}

void Map:: Wake_Up(){		// Eksodos apo xeimeria narkh
	int temp=0;
	while(temp<AnimalsTSize){
		AnimalsT[temp]->Wake_Up();
		temp++;
	}
}

void Map:: Sleep(){		//Eisodos se xeiria narkh
	int temp=0;
	while(temp<AnimalsTSize){
		AnimalsT[temp]->Sleep();
		temp++;
	}
}

void Map:: set_Hungry(int x){	//Arxikopihsh tou Hunger sta zwa pou den vriskonati se xeiria nakrh
	int temp=0;
	while(temp<AnimalsTSize){
		if(AnimalsT[temp]->get_Hibernation()==0)
			AnimalsT[temp]->set_Hungry(x);
		temp++;
	}
}

void Map:: set_eatenFood(int x){ //Arxikopoihsh tou ths posothtas tou faghtou pou exei fagwetai sth diarkeia mias meras
	int temp=0;
	while(temp<AnimalsTSize){
		AnimalsT[temp]->set_eatenFood(x);
		temp++;
	}
}


void Map:: AGrowth(int day,int AH,int AC){ // Animal Growth gia H kai C analoga me th mera
	int temp=0;
	char* name;
	while(temp<AnimalsTSize){	//prospelash pinaka zwwn
		if(AnimalsT[temp]->get_token()=='H'){
			if(day%AH==0){
				AnimalsT[temp]->Growth(AnimalsT[temp]->get_name(),AnimalsT[temp]->get_token()=='H');		//klhsh growth gia H
			}
		}

		else if(AnimalsT[temp]->get_token()=='C'){
			if(day%AC==0){
				AnimalsT[temp]->Growth(AnimalsT[temp]->get_name(),AnimalsT[temp]->get_token()=='H');		//klhsh growth gia C
			}
		}
		temp++;
	}
}
	
void Map:: AnimalMovement(){	//Metakinhs zwwn ana zwo
	int temp=0;
	while(temp<AnimalsTSize){	//prospelash pinaka
		if(AnimalsT[temp]->get_Hibernation()==0)
			AnimalsT[temp]->Move(terrainSize,map);	//klhsh move
		temp++;
	}
}

void Map:: AnimalEating(){	//Kalei thn eat gia ka8e zwo tpu pinaka ksexwrista
	int temp=0;
	int z=0;
	while(temp<AnimalsTSize){	//prospelash pinaka zwwn
		if(AnimalsT[temp]->get_Hibernation()==0)
			AnimalsT[temp]->Eat(map,AnimalsTSize,AnimalsT);		//klhsh eat
		temp++;
	}
	z++;

}


void Map:: CheckDeadEntities(){	//Elegxos nekrwn ontothtwn kai diagrafh tous
	int temp=0;
	int x=0;
	int y=0;

// Elegxos neekrown fytwn
	while(x<terrainSize){
		while(y<terrainSize){
			if(map[x][y].get_plflag()==1){		//elegxos tou deikth fytou tou ka8e tile
				if(map[x][y].get_life()==0){	//elegxos zwhs
					map[x][y].delete_plant();	//diagrafh fytou
					//cout<< "REMOVED ONE DEAD PLANT!" <<endl;
				}
			}
			y++;
		}
		x++;
		y=0;
	}

// Elegxos peinas zwwn + kill zwwn
	CheckHunger();

// Diagrafh nekrwn zwwn
	temp=0;
	
	while(temp<AnimalsTSize){
		if(AnimalsT[temp]->get_isAlive()==0){
			AnimalsT.erase(AnimalsT.begin()+temp);	// Diagrfh zwou
			temp=0;
			AnimalsTSize--;
		}
		temp++;
	}
}

void Map:: CheckHunger(){ //Elegxos ths peinas enos zwou + kill
	int temp=0;

	while(temp<AnimalsTSize){
		if(AnimalsT[temp]->get_Hungry()>9){
			AnimalsT[temp]->kill();
		}
		temp++;
	}
}

void Map:: PGrowth(){	// Plants Growth
	int x=0;
	int y=0;
	while(x<terrainSize){
		while(y<terrainSize){
			if(map[x][y].get_plflag()==1)	//elegxos deikth fytou
				map[x][y].PGrowth();
			y++;
		}
		y=0;
		x++;
	}
}

void Map:: AHBreed(){	//Animals Breed gia H ~ Klhsh put annimal me katallhla orismata
	int temp=0;
	while(temp<AnimalsTSize){
		if(AnimalsT[temp]->get_max()==1 && AnimalsT[temp]->get_Hibernation()==0){
			if(AnimalsT[temp]->get_name()=="Deer"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'d',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
			else if(AnimalsT[temp]->get_name()=="Rabbit"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'r',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
			else if(AnimalsT[temp]->get_name()=="Marmot"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'m',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
			else if(AnimalsT[temp]->get_name()=="Salmon"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'s',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
		}
		temp++;
	}
}

void Map:: ACBreed(){	//Animals breed gia C ~ Klhsh put animal me katallhla orismata
	int temp=0;
	while(temp<AnimalsTSize){
		if(AnimalsT[temp]->get_max()==1 && AnimalsT[temp]->get_Hibernation()==0){
			if(AnimalsT[temp]->get_name()=="Fox"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'f',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
			else if(AnimalsT[temp]->get_name()=="Wolf"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'w',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
			else if(AnimalsT[temp]->get_name()=="Bear"){
				//cout<<"PLACED NEW ANIMAL!!!!!! : "<<AnimalsT[temp]->get_name()<<endl;
				put_animal(1,'b',0,AnimalsT[temp]->get_x(),AnimalsT[temp]->get_y());
			}
		}
		temp++;
	}
}


void Map:: PBreed(){	//Plants Breed ~ klhsh put plant
	int flag;
	int x=0;
	int y=0;
	while(x<terrainSize){
		while(y<terrainSize){
			if(map[x][y].get_plflag()==1){
				flag=FindFreeTile(x,y);	// KLhsh FindFreeTile
				if(flag==1){
					put_plant(1,map[x][y].get_plant(),1,x,y-1);
					//cout<<"PLACED NEW PLANT!!!!!!"<<endl;
				}
				if(flag==2){
					put_plant(1,map[x][y].get_plant(),1,x,y+1);
					//cout<<"PLACED NEW PLANT!!!!!!"<<endl;
				}
				if(flag==3){
					put_plant(1,map[x][y].get_plant(),1,x+1,y);
					//cout<<"PLACED NEW PLANT!!!!!!"<<endl;
				}
				if(flag==4){
					put_plant(1,map[x][y].get_plant(),1,x-1,y);
					//cout<<"PLACED NEW PLANT!!!!!!"<<endl;
				}
			}
			y++;
		}
		x++;
		y=0;
	}
}

int Map:: FindFreeTile(int x,int y){	//Euresh geitonikou tile xwris fyto
	int flag=0;
	char pl=map[x][y].get_plant();
	char ban1;
	char ban2;

// Orismos katallhlou edafous analoga me to plant
	if(pl=='G'){
		ban1='^';
		ban2='#';
	}
	if(pl=='A'){
		ban1='^';
		ban2='"';
	}
	if(pl=='O'){
		ban1='#';
		ban2='^';
	}
	if(pl=='M'){
		ban1='#';
		ban2='&';
	}
	if(pl=='P'){
		ban1='#';
		ban2='"';
	}
// Anazhthsh eley8erou Tile me th seira: aristera -> deksia -> panw -> katw
	if(y>0){
		if(map[x][y-1].get_plflag()==0 && map[x][y-1].get_tr()!=ban1 && map[x][y-1].get_tr()!=ban2){
			flag=1;
			return flag;
		}
	}
	if(y<terrainSize-1){
		if(map[x][y+1].get_plflag()==0 && map[x][y+1].get_tr()!=ban1 && map[x][y+1].get_tr()!=ban2){
			flag=2;
			return flag;
		}
	}
	if(x<terrainSize-1){
		if(map[x+1][y].get_plflag()==0 && map[x+1][y].get_tr()!=ban1 && map[x+1][y].get_tr()!=ban2){
			flag=3;
			return flag;
		}
	}
	if(x>0){
		if(map[x-1][y].get_plflag()==0 && map[x-1][y].get_tr()!=ban1 && map[x-1][y].get_tr()!=ban2){
			flag=4;
			return flag;
		}
	}
	return flag;
}

void Map:: PrintPlantStatistics(){	//Ektypwsh Statistikwn Fytwn
	int x=0,y=0;
	int g=0,a=0,m=0,o=0,p=0;

	while(x<terrainSize){		//Prospelash xarth kai elegxos ka8e tile
		while(y<terrainSize){
			if(map[x][y].get_plflag()==1){
				if(map[x][y].get_plant()=='G')
					g++;
				else if(map[x][y].get_plant()=='A')
					a++;
				else if(map[x][y].get_plant()=='M')
					m++;
				else if(map[x][y].get_plant()=='O')
					o++;
				else if(map[x][y].get_plant()=='P')
					p++;
			}
			y++;
		}
		y=0;
		x++;
	}
	cout<< endl << "Plants Statistics:"<< endl;
	cout<< "\tGrass: " << g << endl;
	cout<< "\tAlgae: " << a << endl;
	cout<< "\tMapple: " << m << endl;
	cout<< "\tOak: " << o << endl;
	cout<< "\tPine: " << p << endl;
}


void Map:: PrintAnimalStatistics(){	//Ektypwsh Statistikwn Zwwn
	int d=0,r=0,m=0,s=0,w=0,f=0,b=0;
	int x=0;

	while(x<AnimalsTSize){	//Prospelah pinaka zwwn
		if(AnimalsT[x]->get_name()=="Deer")
			d++;
		else if(AnimalsT[x]->get_name()=="Rabbit")
			r++;
		else if(AnimalsT[x]->get_name()=="Marmot")
			m++;
		else if(AnimalsT[x]->get_name()=="Salmon")
			s++;
		else if(AnimalsT[x]->get_name()=="Wolf")
			w++;
		else if(AnimalsT[x]->get_name()=="Fox")
			f++;
		else if(AnimalsT[x]->get_name()=="Bear")
			b++;
		x++;
	}

	cout << endl << "Animals Statistics" << endl;	//Ektypwseis
	cout << "\tDeers: " << d << endl;
	cout << "\tRabbits: " << r << endl;
	cout << "\tMarmots: " << m << endl;
	cout << "\tSalmons: " << s << endl;
	cout << "\tWolfes: " << w << endl;
	cout << "\tFoxes: " << f << endl;
	cout << "\tBears: " << b << endl;
}

/////////////////////////////////////////////

Tile:: Tile(char x){
	plflag=0;
	tr=x;
}

Tile:: ~Tile(){
}

char Tile:: get_tr(){	//Epistrofh token edafous
	return tr;
}

void Tile:: change_to_w(){	//Allagh token edafous se nero
	tr='#';
}

void Tile:: change_to_h(){	//Allagh token edafous se lofo
	tr='^';
}

void Tile:: change_to_m(){	//Allagh token edafous se pediada
	tr='"';
}

void Tile:: set_grass(){	//Desmeysh deikth fytou enos tile se grass
	plant=new Grass();
	plflag=1;
}

void Tile:: set_algae(){	//Desmeysh deikth fytou enos tile se algae
	plant=new Algae();
	plflag=1;
}

void Tile:: set_oak(){		//Desmeysh deikth fytou enos tile se oak
	plant=new Oak();
	plflag=1;
}

void Tile:: set_pine(){		//Desmeysh deikth fytou enos tile se pine
	plant=new Pine();
	plflag=1;
}

void Tile:: set_maple(){	//Desmeysh deikth fytou enos tile se malpe
	plant=new Maple();
	plflag=1;
}


char Tile:: get_plant(){	//Epistrofh token fytou enos tile
	if(plflag==1)
		return plant->get_token();
	
	else
		return 'E';
}


int Tile:: get_life(){		//Epistrofh ths zwhs enos fytou enos tile
	return plant->get_life();
}

void Tile:: delete_plant(){	//Diagrafh fytou + allagh plant flag
	if(plflag==1){
		delete plant;
		plflag=0;
	}
}

int Tile:: get_plflag(){	//Epistrofh plant flag
	return plflag;
}

int Tile:: LoseLife(int z){	//Klhsh kai epistrofh LOseLofe enos fytou
	return plant->LoseLife(z);
}

int Tile:: LoseSeeds(int z){	//Klhsh kai epistrofh LoseSeeds enos fytou
	return plant->LoseSeeds(z);
}

int Tile:: get_plSize(){	//Klhsh kai epistrofh plSize
	return plant->get_Size();
}

void Tile:: PGrowth(){		// Klhsh plante Growth
	plant->Growth();
}
/////////////////////////////////////////////
Plants:: Plants(char Token,int Life,int BreedingProb,int IllnessProb,int LifeFactor,int Size): token(Token), life(Life), breedingProb(BreedingProb),illnessProb(IllnessProb), lifeFactor(LifeFactor),size(Size){
	
}

Plants:: ~Plants(){
}

void Plants:: set_name(char z){		//Orismos onomatos fytou me vash to token tou
	if(z=='g')
		name="Grass";
	if(z=='a')
		name="Algae";
	if(z=='o')
		name="Oak";
	if(z=='m')
		name="Maple";
	if(z=='p')
		name="Pine";
}

char Plants:: get_token(){		//Epistrofh Token fytou
	return token;
}

int Plants:: LoseLife(int z){		//meiwsh zwhs enos fytou kai epistrofh tou posou pou th meiwse
	if(z>life){
		z=life;
	}
	life=life-z;
	return z;
}

int Plants:: get_breedingProb(){	//Epistrofh BreedingProb
	return breedingProb;
}

int Plants:: get_illnessProb(){		//Epistrofh illnessProb
	return illnessProb;
}

int Plants:: get_lifeFactor(){		//Epistrofh LifeFactor
	return lifeFactor;
}

int Plants:: get_Size(){		//Epistrofh Size
	return size;
}

int Plants:: get_life(){		//Epistrofh LIfe
	return life;
}

/////////////////////////////////////////////
Grass:: Grass():Seedless('G',5,15,15,4) {
	set_name('g');
}

Grass:: ~Grass(){
}
/////////////////////////////////////////////
Algae:: Algae():Seedless('A',5,25,25,2){
	set_name('a');
}

Algae:: ~Algae(){
}
/////////////////////////////////////////////
Pine:: Pine():Seeded('P',5,20,40,15,15,20){
	set_name('p');
}

Pine:: ~Pine(){
}
/////////////////////////////////////////////
Oak:: Oak():Seeded('O',5,15,30,20,20,15){
	set_name('o');
}

Oak:: ~Oak(){
}
/////////////////////////////////////////////
Maple:: Maple():Seeded('M',2,10,20,5,5,10){
	set_name('m');
}

Maple:: ~Maple(){
}
/////////////////////////////////////////////
Seedless:: Seedless(char T,int Li,int Br,int Ill,int Lf):Plants(T,Li,Br,Ill,Lf){
}

Seedless:: ~Seedless(){
}

void Seedless:: Growth(){
	int flag;
	int y;
	flag=rand() % 100 + 1;
	if(flag<=illnessProb)//get_illnessProb())
		y=LoseLife(lifeFactor);
	else
		y=LoseLife(-1*lifeFactor);
}

/*void Seedless:: Breed(){
	int flag;
	flag=rand()% 100 + 1;
	/*if(flag<=get_breedingProb())
		PlantBreeding();
}*/

////////////////////////////////////////////

Seeded:: Seeded(char T,int Size,int Se,int Fo,int Ill,int Br,int Lf): size(Size),seeds(Se),foliage(Fo),Plants(T,Fo,Br,Ill,Lf,Size){
} 

Seeded:: ~Seeded(){
}

int Seeded:: LoseSeeds(int z){		//Meiwsh karpwn kai epistrofh toy posou pou meiw8hke
	if(z>seeds){			//Ean sto z>seeds meiwnetai kai to fyllwma
		z=z-seeds;
		seeds=0;
		return z+LoseFoliage(z);

	}
	else{
		seeds=seeds-z;
		return z;
	}
}

int Seeded:: LoseFoliage(int z){	//Meiwsh Fyllwmatos kai epistrofh tou posou pou meiw8hke
	int keep=0;

	if(z>foliage){
		z=z-foliage;
		LoseLife(foliage);
		foliage=0;
		return z;
	}
	else{
		foliage=foliage-z;
		LoseLife(z);
		return z;
	}
}

void Seeded:: Growth(){			//Growrth fytwn
	int flag;
	int y;
	int Lf=lifeFactor;

	flag=rand() % 100 + 1;

	if(flag<=get_illnessProb()){	//arrwstia
		y=LoseLife(Lf);
		foliage=foliage-Lf;
		seeds=seeds-(2*Lf);
		if(foliage==Lf)
			size--;
	}
	else{
		y=LoseLife(-1*Lf);	//Growth
		foliage=foliage+Lf;
		seeds=seeds+(2*Lf);
		if(foliage==Lf)
			size++;
	}
}

/*void Seeded:: Breed(){
	int flag;
	flag=rand()% 100 + 1;
	/*if(flag<=get_breedingProb())
		PlantBreeding();
}*/


//////////////////////////////////////////////////////////////////////////
Animals:: Animals(int MaxSize,int MaxSpeed,int MaxNF,char N,int Size,int Speed,int NF,int EatCount,int X,int Y,char Token): maxSize(MaxSize), maxSpeed(MaxSpeed), maxNeededFood(MaxNF), neededFood(NF),size(Size), speed(Speed), eatCount(EatCount), x(X), y(Y){

	set_name(N);
	token=Token;
	hungerCount=0;
	eatenFood=0;

	isAlive=1;
	isHungry=0;
	inHeat=0;

	hibernates=0;
	inHibernation=0;
	max=0;
}

Animals:: ~Animals(){
}

void Animals:: set_name(char z){	//Orismos onomatos zwwn
	if(z=='D'){
		name="Deer";
	}
	if(z=='R'){
		name="Rabbit";
	}
	if(z=='M'){
		name="Marmot";
	}
	if(z=='S'){
		name="Salmon";
	}
	if(z=='F')
		name="Fox";
	if(z=='W')
		name="Wolf";
	if(z=='B')
		name="Bear";
}

void Animals:: delete_animal(){		//diagrafh zwou
	delete name;
}

int Animals:: get_x(){			//epistrofh x
	return x;
}

int Animals:: get_y(){			//epistrofh y
	return y;
}

const char* Animals:: get_name(){	//epistrofh onomatos zwou
	return name;
}

void Animals:: Wake_Up(){		//Eksodos xeimerias narkhs
	if(inHibernation==1)
		inHibernation=0;
}

void Animals:: Sleep(){			//Eisodos se xeiria narkh
	if(hibernates==1)
		inHibernation=1;
}

void Animals:: set_Hungry(int x){	//Allagh hungry
	if(x==0)
		isHungry=0;
	else
		isHungry+=x;
}

void Animals:: set_eatenFood(int x){	//Faghto pou fagw8hke se mia mera
	eatenFood=x;
}

int Animals:: get_Hungry(){		//Epistrofh hungry
	return isHungry;
}

char Animals:: get_token(){		//Epistrofh token zwou
	//cout<<token<<endl;;
	return token;
}

int Animals:: get_isAlive(){		//epistrofh isAlive
	return isAlive;
}

void Animals:: Growth(const char*a ,char token){	//Animals Growth
	if(token=='H'){		// Animals H
		if(size<maxSize && a!="Solomon")
			size++;
		if(speed<maxSpeed && a!="Solomon"){		
			if(a=="Deer" || a== "Rabbit")
				size=size+2;
			else
				size++;
		}
		if(neededFood<maxNeededFood && a!="Solomon"){
			if(a=="Deer")
				neededFood=neededFood+2;
			else
				neededFood++;
		}
	}
	if(token=='C'){		// Animals C
		if(size<maxSize){
			if(a=="Bear")
				size=size+2;
			else
				size++;
		}
		if(speed<maxSpeed){		
			if(a=="Wolf" || a== "Bear")
				size=size+2;
			else
				size++;
		}
		if(neededFood<maxNeededFood){
				if(a=="Wolf" || a=="Bear")
				neededFood=neededFood+2;
			else
				neededFood++;
		}
	}

	if(size==maxSize){	// Elegxos gia mas stats
		if(speed==maxSpeed){
			if(neededFood==maxNeededFood)
				max=1;
		}
	}
}


void Animals:: Move(int Ts,Tile** map){	// kinountai tyxaio plh8os tiles mirkotero h isio ths taxythtas tous/2 ka8e wra me ka8e allagh ths kateu8unshs tous na ginetai pros tyxaia kateu8unsh h menei akinhto

	int temp=rand()% (speed+1)/2;
	//cout << "speed: "<< speed<<endl;
	int flag=0;
	char ban1='&';
	char ban2='&';

	// Apagoreyseis perivalllontos analoga me to zwo
	if(name=="Rabbit")
		ban1='^';
	if(name=="Marmot")
		ban1='#';
	if(name=="Salmon"){
		ban1='"';
		ban2='^';
	}
	// Anazhths katey8ynshs - allagh syntetagmenwn twn zwwn
	while(temp>0){
		//cout<<name<<endl;		
		flag=rand()%5;
		//cout<<"x BEFORE: "<< x << endl;
		if(flag==0 && x-1>0){
			if(map[x-1][y].get_tr()!=ban1 && map[x-1][y].get_tr()!=ban2){
				x--;
				temp--;
			}
		}
		if(flag==1 && x+1<Ts){
			if(map[x+1][y].get_tr()!=ban1 && map[x+1][y].get_tr()!=ban2){
				x++;
				temp--;
			}
		}
		if(flag==2 && y-1>0){
			if(map[x][y-1].get_tr()!=ban1 && map[x][y-1].get_tr()!=ban2){
				y--;
				temp--;
			}
		}
		if(flag==3 && y+1<Ts){
			if(map[x][y+1].get_tr()!=ban1 && map[x][y+1].get_tr()!=ban2){
				y++;
				temp--;
			}
		}
		if(flag==4 && y+1<Ts){
			temp--;
		}
	}
}


void Animals:: Eat(Tile** &map,int AnimalsTSize,vector <Animals*> &AnimalsT){		//Animals Eat
	int pltoken;
	int keep=0;

	if(token=='H' && isHungry>=1 && isAlive==1){	//FYTOFAGA
		int Hseed=0;
		if(name=="Deer")
			Hseed=4;
		if(name=="Marmot")
			Hseed=2*size;
		if(name=="Rabbit")
			Hseed=0;

		if(map[x][y].get_plflag()==1){		//elegxos yparkshs fytou sto tile tou zwou
			pltoken=map[x][y].get_plant();

			if(pltoken=='G' && name!="Salmon"){ 
				keep=map[x][y].LoseLife(eatCount);	//kalw lose life ~ h keep krataei to poso pou telika afire8hke
				eatenFood=eatenFood+keep;
			}

			if(pltoken=='A' && name!="Rabbit" && name!="Marmot"){
				keep=map[x][y].LoseLife(eatCount);	//kalw lose life
				eatenFood=eatenFood+keep;
			}

			else if(size+Hseed>=map[x][y].get_plSize() && name!="Salmon"){
				keep=map[x][y].LoseSeeds(eatCount);
				eatenFood=eatenFood+keep;

			}
			if(eatenFood==neededFood){
				isHungry=-7;
			}
		}
	}

	else if(token=='C' && isHungry>=1 && isAlive==1){	//SARKOFAGA
		int x2=0;
		int y2=0;
		int temp=0;
		
		while(temp<AnimalsTSize){	//prospelash pinaka zwwn gia eyresh zwou sto idio tile
			if(AnimalsT[temp]->get_x()==x && AnimalsT[temp]->get_y()==y ){
				if(AnimalsT[temp]->get_token()=='H'){
					if(name=="Fox" || name =="Wolf"){	//Elegxos xarakthristikwn
						if(AnimalsT[temp]->get_Size()<=size && AnimalsT[temp]->get_Speed()<speed && AnimalsT[temp]->get_name()!="Salmon"){
							AnimalsT[temp]->kill();
							isHungry=0;
						}
					}
					else{
						if(AnimalsT[temp]->get_Size()<=size && AnimalsT[temp]->get_Speed()<speed){
							AnimalsT[temp]->kill();
							isHungry=0;
						}

					}
				}
				if(AnimalsT[temp]->get_token()=='C' && isHungry>8 && name!=AnimalsT[temp]->get_name()){		//eat enos allo sarkofagou + apotrroph kanivalismou
					if(AnimalsT[temp]->get_Size()<=size && AnimalsT[temp]->get_Defence()<this->get_Attack()){
						AnimalsT[temp]->kill();
						isHungry=0;
					}
				}
			}
			temp++;
		}
	}
}

int Animals:: get_Size(){	//Epistrofh SIze
	return size;
}

int Animals:: get_Speed(){	//Epistrofh Speed
	return size;
}

void Animals:: kill(){		//Allagh isAlve se 0
	isAlive=0;
}

/*void Animals:: checkFood(){
	if(isHungry==1)
		isHUngry++;
	else{
		if(token=="H")
			isHungry=-6;
		else
			isHUngry=0;
	}
}*/

int Animals:: get_max(){	//Epistrrofh max
	return max;
}

int Animals :: get_Hibernation(){	//Epistrofh flag gia th xeimeria narkh
		return inHibernation;
}
//////////////////////////////////////////////////////////////////////////
Herbivores:: Herbivores(int MaxSize,int MaxSpeed,int MaxNF,int NeededFood,int MaxEatCount,int CanClimb,char N,int Size,int Speed,int NF,int X,int Y): maxEatCount(MaxEatCount), canClimb(CanClimb), Animals(MaxSize,MaxSpeed,MaxNF,N,Size,Speed,NF,MaxEatCount,X,Y,'H'){

}

Herbivores:: ~Herbivores(){
}


int Herbivores:: get_EatCount(){	//Epistrrofh maxEatcount
	return maxEatCount;
}
int Herbivores:: get_canClimb(){	//Epistrofh canClimb
	return canClimb;
}



///////////////////////////////////////////////////////////////////////////
Carnivores:: Carnivores(int MaxAttack,int MaxDefence,int MaxSize,int MaxSpeed,int MaxNF,char N,int Attack, int Defence, int Size, int Speed, int NF, int X, int Y): maxAttack(MaxAttack),maxDefence(MaxDefence),attack(Attack), defence(Defence), Animals(MaxSize, MaxSpeed, MaxNF, N, Size, Speed,NF,0, X, Y,'C') {
}

Carnivores:: ~Carnivores(){
}


int Carnivores:: get_Defence(){		//Epistrofh Defence
	return defence;
}

int Carnivores:: get_Attack(){		//Epistrofh attack
	return attack;
}


////////////////////////////////////////////////////////////////////////////

Deer:: Deer(int Max,int X,int Y): Herbivores(5,8,8,8,2,0,'D',5,8,8,X,Y){	//MAX STATS
	max=1;
}

Deer:: Deer(int X,int Y): Herbivores(5,8,8,4,2,0,'D',2,4,4,X,Y){
}
Deer:: ~Deer(){
}

/////////////////////////////////////////////////////////////////////////////

Rabbit:: Rabbit(int Max,int X,int Y): Herbivores(2,6,4,4,1,0,'R',2,6,4,X,Y){	//MAX STATS
	max=1;
}

Rabbit:: Rabbit(int X,int Y): Herbivores(2,6,4,2,1,0,'R',1,2,2,X,Y){
}

Rabbit:: ~Rabbit(){
}

/////////////////////////////////////////////////////////////////////////////

Marmot:: Marmot(int Max,int X,int Y): Herbivores(3,5,5,5,1,1,'M',3,5,5,X,Y){	//MAX STATS
	hibernates=1;
	max=1;
}

Marmot:: Marmot(int X,int Y): Herbivores(2,3,3,3,1,1,'M',2,3,3,X,Y){
	hibernates=1;
}

Marmot:: ~Marmot(){
} 

/////////////////////////////////////////////////////////////////////////////

Salmon:: Salmon(int Max,int X,int Y): Herbivores(1,5,1,1,1,0,'S',1,5,1,X,Y){
}

Salmon:: ~Salmon(){
}

/////////////////////////////////////////////////////////////////////////////

Fox:: Fox(int Max,int X,int Y): Carnivores(5,5,4,6,6,'F',5,5,4,6,6,X,Y){	//MAX STATS
	max=1;
}

Fox:: Fox(int X,int Y): Carnivores(5,5,4,6,6,'F',1,1,1,1,2,X,Y){
}

Fox:: ~Fox(){
}
/////////////////////////////////////////////////////////////////////////////

Wolf:: Wolf(int Max,int X,int Y): Carnivores(8,6,7,6,8,'W',8,6,7,6,8,X,Y){	//MAX STATS
	max=1;
}

Wolf:: Wolf(int X,int Y): Carnivores(8,6,7,6,8,'W',2,3,1,2,2,X,Y){
}

Wolf:: ~Wolf(){
}

//////////////////////////////////////////////////////////////////////////////

Bear:: Bear(int Max,int X,int Y): Carnivores(10,10,10,4,10,'B',10,10,10,4,10,X,Y){	//MAX STATS
	hibernates=1;
	max=1;
}

Bear:: Bear(int X,int Y): Carnivores(10,10,10,4,10,'B',6,6,3,4,5,X,Y){
	hibernates=1;
}

Bear:: ~Bear(){
}



