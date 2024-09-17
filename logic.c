#define NULL 0


int linear_bonus(int level) {
	// -2,-1,0,+1,+2 
	 if (level < 10) {
		 return -2;
	 }
	 else if (level < 30) {
		 return -1;
	 }
	 else if (level < 50) {
		 return 0;
	 }
	 else if (level < 70) {
		 return 1;
	 }
	 else {
		 return 2;
	 }
}

void intectu_str(int level , char *ret ){
	 //Genius, Intelligent, Smart, Average, slow, Imbecile
	 if (level < 10) {
		 strcpy(ret, "Imbecile");
	 }
	 else if (level < 30) {
		 strcpy(ret, "Slow");
	 }
	 else if (level < 50) {
		 strcpy(ret, "Average");
	 }
	 else if (level < 70) {
		 strcpy(ret, "Smart");
	 }
	 else if (level < 90) {
		 strcpy(ret, "Intelligent");
	 }
	 else {
		 strcpy(ret, "Genius");
	 }
}

void skill_level_str(int level, char* ret) {
	//Terrible, Poor, Average, Good, Great, Excellent
	if (level < 10) {
		strcpy(ret, "Terrible");
	}
	else if (level < 30) {
		strcpy(ret, "Poor");
	}
	else if (level < 50) {
		strcpy(ret, "Average");
	}
	else if (level < 70) {
		strcpy(ret, "Good");
	}
	else if (level < 90) {
		strcpy(ret, "Great");
	}
	else {
		strcpy(ret, "Excellent");
	}
}

typedef struct _npc {
	char name[10]; 
	int age;
	int health;
	int education;

	//reputation
	int dread;
	int prestige;
	int piety;

	//skills
	int diplomacy;
	int martial;
	int stewardship;
	int intrigue;
	int learning;
	int prowess;
} npc;


//relation shipt type can be
// concubines , marriage, alliance, vassal,  rival, friend, enemy, lover, mentor. 
enum RelationshipType {
	CONCUBINES = 1,
	MARRIAGE,
	ALLIANCE,
	VASSAL,
	RIVAL,
	FRIEND,
	ENEMY,
	LOVER,
	MENTOR
};

typedef struct relationship {
	npc* npc1;
	npc* npc2;
	int type;   
} relationship;



typedef struct _concil {
	npc* confidant;
	npc* chaplain;
	npc* chancellor;
	npc* steward;
	npc *marshal;
	npc *spymaster;
} concil;

typedef struct _court {
	npc* hostages[5];
	npc* quest[10];
	npc* physician;
	npc* antiquarian;
	npc* caravan_master;
	npc* jester;
	npc* master_of_hunt;
	npc* seneschal;
	npc* tutor;
	npc* wet_nurse;
	npc* lady_in_waiting;
	npc* scholar;
} court;

//enum for types 
enum BuildingType {   
	//economic
	TRADEPOST=1 , //id = 1
	PLATATION,
	CROPFARM,
	LOGGINGCAMP,
	WINDMILL,
	QUARRY,
	CATTLEFARM,
	HOSPITAL,
	WORKSHOP,
	BATHHOUSE= 10,
	//military
	FORTRESS = 20,
	WATCHTOWER,
	BARRACKS,
	BLACKSMITH,
	HORSEBREEDER,
	STABLE,
	ARCHERYRANGE = 26,
	//religious
	CHAPEL= 30,
	MONASTERY,
	//cultural
	THEATER= 40,
	ACADEMY,
	//government
	COURTHOUSE=50,
	TOWNHALL,
	//special
	CASTLE=100  //only one per land
};
typedef struct _Building {
	int type;
	int level;	 //0 not build yet/destroied, 1 normal, 2 improved
} Building;

int building_cost(int type, int level) {
	if (level == 0) return 0; //not build yet
	//cost of the building
	 if (type < 20) {
		 return  0; 
	 }
	 const int costs_millitary[7][2] = {{FORTRESS,3} , {WATCHTOWER,1} , {BARRACKS,1} , {BLACKSMITH,3} , {HORSEBREEDER,5} , {STABLE,3} , {ARCHERYRANGE,2}};
	 const int costs_religious[2][2] = { {CHAPEL,2} , {MONASTERY,4} };
	 const int costs_cultural[2][2] = { {THEATER,2} , {ACADEMY,5} };
	 const int costs_government[2][2] = { {COURTHOUSE,10} , {TOWNHALL,5} };
	 const int costs_special[1][2] = { {CASTLE,100} };
	 
	 if (type < 30) {
		 for (int i = 0; i < 7; i++) {
			 if (costs_millitary[i][0] == type) {
				 return costs_millitary[i][1];
			 }
		 }
	 }
	 else if (type < 40) {
		 for (int i = 0; i < 2; i++) {
			 if (costs_religious[i][0] == type) {
				 return costs_religious[i][1];
			 }
		 }
	 }
	 else if (type < 50) {
		 for (int i = 0; i < 2; i++) {
			 if (costs_cultural[i][0] == type) {
				 return costs_cultural[i][1];
			 }
		 }
	 }
	 else if (type < 100) {
		 for (int i = 0; i < 2; i++) {
			 if (costs_government[i][0] == type) {
				 return costs_government[i][1];
			 }
		 }
	 }
	 else {
		 for (int i = 0; i < 1; i++) {
			 if (costs_special[i][0] == type) {
				 return costs_special[i][1];
			 }
		 }
	 }
	 return 0;
}


#define MAX_BUILDINGS 5
typedef struct land_ {
	npc* owner;
	int tax;
	int levies;
	Building buildings[MAX_BUILDINGS];
} Land;
 
 
 
#define NUM_LANDS 20
#define NUM_RELATIONS 200
typedef struct _gamestate {
	npc *player;
	concil *conselho;
	court *corte;
	Land* lands[NUM_LANDS];
	relationship* rels[NUM_RELATIONS];


	//scores
	int gold;
}  gamestate;


int get_relationship_type(gamestate* g, npc* npc1, npc* npc2) {
	//get the relationship value between two npcs
	for (int i = 0; i < NUM_RELATIONS; i++) {
		if (g->rels[i] != NULL) {
			if (g->rels[i]->npc1 == npc1 && g->rels[i]->npc2 == npc2) {
				return g->rels[i]->type;
			}
			if (g->rels[i]->npc1 == npc2 && g->rels[i]->npc2 == npc1) {
				return g->rels[i]->type;
			}
		}
	}
	return 50; //default value
}

void compute_taxes_land(gamestate* g ) {
	for (int i = 0; i < NUM_LANDS; i++) {
		if (g->lands[i] != NULL) {
			g->lands[i]->tax = 1; //base for each land
			//each economic construction +1 
			for (int j = 0; j < MAX_BUILDINGS; j++) {
				if (g->lands[i]->buildings[j].type  >= 1 && g->lands[i]->buildings[j].type <= 10) {
					g->lands[i]->tax += 1;
				}
			}
			//if dont have any owner. cut by half
			if (g->lands[i]->owner == NULL) {
				g->lands[i]->tax = g->lands[i]->tax / 2;
			} 
			else {
				//bonus if the owner is a good steward
				int bonus = linear_bonus(g->lands[i]->owner->stewardship);				 
				g->lands[i]->tax += bonus;
			}
		}
	}
}


void compute_taxes(gamestate * g   ) {
			//compute taxes
			int received_taxes = 0;
			for (int i = 0; i < NUM_LANDS; i++)
			{
				if (g->lands[i] != NULL) {
					received_taxes += g->lands[i]->tax;
					//an king with low dread will receive less taxes, because the people will try to evade the taxes
					if (g->player->dread <  30) {
						received_taxes = received_taxes / 2;
					}
				}
			}
			//efficiency of the conselhor
			if (g->conselho->steward != NULL) {
				int bonus = linear_bonus(g->conselho->steward->stewardship);
				received_taxes += bonus * (int)(received_taxes/8);
			}
			//efficiency of the court
			if (g->corte->seneschal != NULL) {
				int bonus = linear_bonus(g->corte->seneschal->stewardship);
				received_taxes += bonus * (int)(received_taxes / 8);
			}
	 	    //efficiency of the player
			int bonus_p = linear_bonus(g->player->stewardship);
			received_taxes += bonus_p * (int)(received_taxes / 8);	 

			//the player will receive the taxes
			g->gold += received_taxes;

}


void compute_costs_council(gamestate* g) {
	 //compute costs of the council
	int costs = 0;
	if (g->conselho->confidant != NULL) {
		costs += 1;
	}
	if (g->conselho->chaplain != NULL) {
		costs += 1;
	}
	if (g->conselho->chancellor != NULL) {
		costs += 1;
	}
	if (g->conselho->steward != NULL) {
		costs += 1;
	}
	if (g->conselho->marshal != NULL) {
		costs += 1;
	}
	if (g->conselho->spymaster != NULL) {
		costs += 1;
	}
	g->gold -= costs;
}

void compute_costs_buildings(gamestate* g) {
	//compute costs of the military
	int costs = 0;
	for (int i = 0; i < NUM_LANDS; i++) {
		if (g->lands[i] != NULL) {
			for (int j = 0; j < MAX_BUILDINGS; j++) {
				if (g->lands[i]->buildings[j].type >= 20 && g->lands[i]->buildings[j].type <= 26) {
					costs += building_cost(g->lands[i]->buildings[j].type, g->lands[i]->buildings[j].level);
				}
			}
		}
	}
	g->gold -= costs;
}


void update_gamestate(gamestate* gs) {
	//update the gamestate

	//tax cicle
	compute_taxes_land(gs);
	compute_taxes(gs);
	
	//compute costs
	compute_costs_council(gs);
	compute_costs_buildings(gs);

	 
}