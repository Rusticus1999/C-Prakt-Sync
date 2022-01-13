//hs_17
//018313899
//Nicholas Schuran
#include<stdio.h>
#include<stdlib.h>
//#pragma pack(1)//Albtraum für RISC Prozessoren 

struct Geo
{
	double dLatitude;
	double dLongitude;
	float fAltitude;
};

struct Messwert
{
	int iMessungNummer;
	double dLuftdruck;
	float fTemperatur[3];
	struct Geo Position;
	struct Messwert *pNext;
};

void ausgabe_p(struct Messwert *);
struct Messwert set_mw(int);
int addToList(struct Messwert **, struct Messwert);
int printList(struct Messwert *);
void emptyList(struct Messwert **);

//Main
int main(int argc, char* argv[]){
	struct Messwert *pStart = NULL;
	struct Messwert e = set_mw(1);
	struct Messwert f = set_mw(2);
	struct Messwert g = set_mw(3);
	addToList(&pStart, g);
	addToList(&pStart, f);
	addToList(&pStart, e);
	int anz = printList(pStart);
	printf("\n Die Liste hat %d einträge.\n",anz);
	printf("\n Liste leeren und Speicher freigeben...\n");
	emptyList(&pStart);
	anz = printList(pStart);
	printf("\n Die Liste hat %d einträge.\n",anz);

	return 0;
}

void emptyList(struct Messwert **ppStart){
	struct Messwert *pStart = *ppStart;
	struct Messwert *pPrev;
	while(pStart != NULL){
		pPrev = pStart;
		pStart = pStart->pNext;
		free(pPrev);
	}
	*ppStart = NULL;
}


int printList(struct Messwert *pLauf){
	int counter = 0;
	while(pLauf != NULL){
		counter++;
		printf("\n ----Knoten Nr. %d----\n",counter);
		ausgabe_p(pLauf);
		pLauf = (pLauf->pNext);
	}
	return counter;
}

//Pointer auf den pointer übergeben, weil auch ein Pointer "by Value" übergeben wird.
int addToList(struct Messwert **pStart, struct Messwert Mess){
	//Speicher für ein listenelement reservieren.
	struct Messwert *element = (struct Messwert *) malloc(sizeof(*element));
	//Bei fehlschlag -1 zurück geben.
	if(element == NULL)
	{
		return -1;
	}
	//Das als Kopie übergebene Element in den mit malloc reservierten Speicher kopieren.
	*element = Mess;
	//Den Verkettungszeiger des neuen Elements auf den originalen Zeiger von pStart aus der Main Funktion ändern.
	element->pNext = *pStart;
	//Den originalen pStart Zeiger auf das neue Element zeigen lassen.
	*pStart = element;
	return 0;
}



void ausgabe_p(struct Messwert *pMess){
	//Ausgabe
	printf("iMessungNummer: %d\n",pMess->iMessungNummer);
	printf("dLuftdruck: %lf\n",pMess->dLuftdruck);
	for(int i = 0; i < sizeof(pMess->fTemperatur)/ sizeof(pMess->fTemperatur[0]); i++){
		printf("fTemperatur[%d]: %f\n",i,pMess->fTemperatur[i]);
	}
	printf("Geo:\n");
	printf(" dLatitude: %lf\n",pMess->Position.dLatitude);
	printf(" dLongitude: %lf\n",pMess->Position.dLongitude);
	printf(" fAltitude: %f\n",pMess->Position.fAltitude);
	if(pMess->pNext == NULL)printf("Der Messwert ist der Letzte in der Liste!\n");
}

struct Messwert set_mw(int nummer){
	srand((unsigned int)nummer);
	double pressure = 1.0 + ((rand()%51)-25)/1000;
	struct Messwert ausg = {nummer, pressure, {0.0f,0.0f,0.0f} , {0.0, 0.0, 0.0f}, NULL};
	for(int i = 0; i < sizeof(ausg.fTemperatur)/ sizeof(ausg.fTemperatur[0]); i++){
		ausg.fTemperatur[i] = 20.0f +  (float)((rand()%31)-15)/10.0f;
	}
	ausg.Position.dLongitude = (double)(rand()%1801)/10.0;
	ausg.Position.dLatitude= (double)((rand()%1801)-900)/10.0;
	ausg.Position.fAltitude = (float)((rand()%10001)-5000)/10.0f;//Precision of float adds extra randomness. Nice!

	return ausg;
}
