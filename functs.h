#include <vector>


//void mike(char **terrain,int size);
class Map;
class Tile;
class Plants;
class Animals;


class Ecosystem{
	private:
		int dayOfYear;	//metrhths hmerwn
		int hourOfDay;	//monada xronou mesa se mia mera
		int Season; //1_Anoiksh 2_Kalokairi 3_Fthinoporo 4_Xeimwnas
		Map* TMap;	//deikths gia klash Map
		

		int PbreedingRepPeriod;		//BreedingRep gia PLANTS
		int PgrowthPeriod;		//Growth gia PLANTS
		int AgrowthPeriod;		//Growth gia ANIMALS
		int AHbreedingRepPeriod;	//BreedingRrp gia HER-ANIMALS
		int ACbreedingRepPeriod;	//BreedingRep gia CAR-ANImls
		
	public:
		Ecosystem();
		~Ecosystem();
		
		void create_map();	//diavazei diastaseis xarth kai desmeyei to deikth TMap

		void print_map();	//kalei thn print_map ths klashs Map
		void printTilesp();	//kalei thn printTilesP ths klashs Map
		void printAnimals();	//kalei thn PrintAnimals ths klashs Map
		void PrintSystem();	//ektypwnei thn hmera kai kalei tis: Print , PrintTotalLife

		void delete_map();	//kalei thn delete_map ths klashs Map kai apodesmeyei th deikth TMap

		void RunEcosystem(int day,int x);	//O kyklos ths prosomoiwshs

		void ApplySeason(int x);	//Efarmozei ta xarakthristika ths ka8e epoxhs
		void DailyReset();		//day++ , hour=0 , kalei: set_Hungry , set_eatenFood
		void AnimalMovement();		//Kalei thn AnimalMovement ths klashs Map
		void AnimalEating();		//kalei thn AnimalEating ths kalshs Map

		
		void PlacePlants(int g,int a,int m,int o,int p);	//kalei thn Placeplants ths klashs Map
		void PlaceAnimals(int d,int r,int m,int s,int f,int w,int b);	//kalei tis katallhles put_animal ths klashs Map


		int get_dayOfYear();	//epistrefei thn twtinh hmera
		int getAHbreedingRepPeriod();	//Epistrefei to AHBreeding Period
		int getACbreedingRepPeriod();	//

		void PrintPlantStatistics();	//kalei thn plant statistics ths klshs Map
		void PrintAnimalStatistics();	//kalei thn print animals ths klashs Map

};

	
using std:: vector;

class Map{
	protected:
		const int terrainSize;		//Diastash map
		int lakeSize;			//Tiles pou katalamvanei h limhn
		int HillsSize;			//Synolika tiles pou katalamvanoun oi lofoi
		int hills;			// plh8os hils
		Tile **map;			//deikths gia klash Tile
		vector <Animals*> AnimalsT;	//pinakas zwwn
		int AnimalsTSize;		//Mege8os pinaka zwwwn
		
		
		
	public:
		Map(int TerrainSize);
		~Map();

		void set_hills();	//orizei to plh8os twn lofwn

		void MapGenerator();
		int FindFreeTile();	//

		void GenerateRiver();
		void GenerateLake();
		void GenerateHills();
		void GenerateMeadow();

		void delete_map();
		void print_map();	//ektypwsh xarth xrhsimopoiwntas apokliestika to token edafous
		void printTilesp();	//ektypwsh xarth mono ma vash ta token fytwn
		void printAnimals();	//ektyopwsh olwn twn zwwn, ths 8eshs tous kai ths peinas tous (me ayth th seira)
		void Print();	//ektypwsh xarth me vash ta tokwn KAI fytwn KAI edafous
		void PrintTotalLife();	//ektypwsh ply8ous fytwn kai zwwn

		int get_terrainSize();

		void PlacePlants(int g,int a,int m,int o,int p);	//elegxos twn arxikwn mege8wn twn fytwn
		void put_plant(int num,char p,int random=0,int x=0,int y=0);
		void put_animal(int num,char a,int flag,int x=0,int y=0); //to num einai gia to plh8os ths kathgorias zown, to flag gia to an 8a gennh8ei me max stats h oxi kai x,y sthn periptwsh pou 8eloume sygkekrimenes syntetagmenes

		int get_AnimalsTSize();

		void Wake_Up();
		void Sleep();

		void set_Hungry(int x);
		void set_eatenFood(int x);
		void AGrowth(int day,int AH,int AC);
		void PGrowth();
		void AnimalMovement();
		void AnimalEating();
		void checkFood();
		void CheckDeadEntities();
		void CheckHunger();
		void AHBreed();
		void ACBreed();
		void PBreed();
		int FindFreeTile(int x,int y);

		void PrintPlantStatistics();
		void PrintAnimalStatistics();

		

};

class Tile{
	private:
		char tr;
		int plflag;	//Flag gia yparksh fytoy sto tile
		Plants *plant;	//Deikths se plant
	public:
		Tile(char x='~');
		~Tile();

		char get_tr();

		int get_plflag();
		int get_plSize();
		char get_plant();

		void change_to_w();
		void change_to_h();
		void change_to_m();

		void set_grass();
		void set_algae();
		void set_maple();
		void set_oak();
		void set_pine();

		int get_life();
		int LoseLife(int z);
		int LoseSeeds(int z);
		void delete_plant();
		void PGrowth();
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class Plants{
	protected:
		const char *name;
		char token;
		const int breedingProb;
		const int illnessProb;
		int life;
		const int lifeFactor;

		int size;

	public:
		Plants(char Token='E',int Life=0,int BreedingProb=0,int IllnessProb=0,int LifeFactor=0,int Size=0);
		~Plants();



		int LoseLife(int z);

		char get_token();
		void set_name(char z);
		void delete_plant();
		int get_breedingProb();
		int get_illnessProb();
		int get_lifeFactor();
		int get_Size();
		int get_life();
		virtual void Growth(){};
		virtual int LoseSeeds(int z){return 0;};
};

class Seedless: public Plants{
	private:

	public:
		Seedless(char T,int Li, int Br,int Ill,int Lf);
		~Seedless();

		void Growth() override;
		void Breed();
};

class Seeded: public Plants{
	private:
		int foliage;
		int seeds;
		int size;

	public:
		Seeded(char T,int Size,int Se,int Fo,int Ill,int Br,int Lf);
		~Seeded();

		int LoseSeeds(int z) override;
		int LoseFoliage(int z);
		void Growth() override;
		void Breed();
};


class Grass: public Seedless{
	private:

	public:
		Grass();
		~Grass();
};

class Algae: public Seedless{
	private:

	public:
		Algae();
		~Algae();

};

class Oak: public Seeded{
	private:

	public:
		Oak();
		~Oak();
};

class Pine: public Seeded{
	private:

	public:
		Pine();
		~Pine();
};

class Maple: public Seeded{
	private:

	public:
		Maple();
		~Maple();
};
/////////////////////////////////////////////////////////////////////////////////////////////////
class Animals{
	protected:
		const char *name;
		char token;

		int size;
		int speed;
		int neededFood;

		int hungerCount;
		int eatenFood;
		int eatCount;

		const int maxSize;
		const int maxSpeed;
		const int maxNeededFood;

		int x;
		int y;

		int isAlive;
		int isHungry;
		int inHeat;

		int hibernates; //=0
		int inHibernation; //=0
		int max; //=0
	public:
		Animals(int MaxSize,int MaxSpeed,int MaxNF,char N,int Size,int Speed,int NF,int EatCount,int X,int Y,char Token);
		~Animals();

		void Eat(Tile** &map,int AnimalsTSize,vector <Animals*> &AnimalsT);

		void set_name(char z);

		int get_x();
		int get_y();

		const char* get_name();

		void delete_animal();
		void Wake_Up();
		void Sleep();
		void Growth(const char* a,char token);
		void Move(int Ts,Tile** map);
		void set_Hungry(int x);
		void set_eatenFood(int x);
		void checkFood();
		int get_Hungry();
		char get_token();
		int get_Size();
		int get_Speed();
		int get_isAlive();
		int get_max();
		void Rise();
		virtual int get_Defence(){return 0;};
		virtual int get_Attack(){return 0;};
		void kill();
		int get_Hibernation();

};
/////////////////////////////////
class Herbivores: public Animals{
	protected:
		int canClimb;

		const int maxEatCount;
	public:
		Herbivores(int MaxSize,int MaxSpeed,int MaxNF,int NeededFood,int MaxEatCount,int CanClimb,char N,int Size,int Speed,int NF,int X,int Y);
		~Herbivores();


		int get_EatCount();
		int get_canClimb();
		
};

//////////////////////////////////

class Carnivores: public Animals{
	private:
		int attack;
		int defence;
		int maxAttack;
		int maxDefence;

	public:
		Carnivores(int MaxAttack,int MaxDefence,int MaxSize,int MaxSpeed,int MaxNF,char N,int Attack, int Defence,int Size, int Speed,int NF, int X, int Y);
		~Carnivores();

		
		int get_Defence() override;
		int get_Attack() override;
};

/////////////////////////////////

class Deer:public Herbivores{
	private:
	public:
		Deer(int Max,int X,int Y);
		Deer(int X,int Y);
		~Deer();
};

class Rabbit:public Herbivores{
	private:
	public:
		Rabbit(int Max,int X,int Y);
		Rabbit(int X,int Y);
		~Rabbit();
};

class Marmot:public Herbivores{
	private:
	public:
		Marmot(int Max,int X,int Y);
		Marmot(int X,int Y);
		~Marmot();
};

class Salmon:public Herbivores{
	private:
	public:
		Salmon(int Max,int X,int Y);
		~Salmon();
};

/////////////////////////////////////////////////////////////

class Fox:public Carnivores{
	private:
	public:
		Fox(int Max,int X,int Y);
		Fox(int X,int Y);
		~Fox();
};

class Wolf:public Carnivores{
	private:
	public:
		Wolf(int Max,int X,int Y);
		Wolf(int X,int Y);
		~Wolf();
};

class Bear:public Carnivores{
	private:
	public:
		Bear(int Max,int X,int Y);
		Bear(int X,int Y);
		~Bear();
};

	
