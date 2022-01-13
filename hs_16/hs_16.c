//hs_18
//018313899
//Nicholas Schuran
#include<stdio.h>
#include<stdlib.h>
//#pragma pack(1)//Albtraum für RISC Prozessoren 

struct Geo
{
	double dLatitude;//8
	double dLongitude;//8
	float fAltitude;//4/8
};

struct Messwert
{
	int iMessungNummer;//4/8
	double dLuftdruck;//8
	float fTemperatur[3];//12/16
	struct Geo Position;//20/24
};

void ausgabe(struct Messwert);
void ausgabe_p(struct Messwert *);
struct Messwert set_mw(int);
//Main
int main(int argc, char* argv[]){
	//float temps[] = {12.2f, 12.6f, 13.4f};
	//struct Geo schatz = {51.419861, 7.254779, -1.5f};
	struct Messwert messung = {1, 0.9178,{12.2f, 12.6f, 13.4f} , {51.419861, 7.254779, -1.5f}};
	printf("Größe von Position: %ld\n", sizeof(messung.Position));
	printf("Größe von Messung: %ld\n", sizeof(messung));
	ausgabe_p(&messung);
	printf("fTemperatur[0] nach Änderung: %lf\n",messung.fTemperatur[0]);

	struct Messwert test = set_mw(3);
	ausgabe(test);
	return 0;
}

void ausgabe(struct Messwert pMess){
	//Ausgabe
	printf("iMessungNummer: %d\n",pMess.iMessungNummer);
	printf("dLuftdruck: %lf\n",pMess.dLuftdruck);
	for(int i = 0; i < sizeof(pMess.fTemperatur)/ sizeof(pMess.fTemperatur[0]); i++){
		printf("fTemperatur[%d]: %f\n",i,pMess.fTemperatur[i]);
	}
	printf("Geo:\n");
	printf(" dLatitude: %lf\n",pMess.Position.dLatitude);
	printf(" dLongitude: %lf\n",pMess.Position.dLongitude);
	printf(" fAltitude: %f\n",pMess.Position.fAltitude);
	//Array Ändern
	pMess.fTemperatur[0] = 50.2f;


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
	//Array Ändern
	(*pMess).fTemperatur[0] = 64.0f;


}

struct Messwert set_mw(int nummer){
	srand((unsigned int)nummer);
	double pressure = (1.0 + ((rand()%51)-25)/1000);
	struct Messwert ausg = {nummer, pressure, {0.0f,0.0f,0.0f} , {0.0, 0.0, 0.0f}};
	for(int i = 0; i < sizeof(ausg.fTemperatur)/ sizeof(ausg.fTemperatur[0]); i++){
		ausg.fTemperatur[i] = 20.0f +  (float)((rand()%31)-15)/10.0f;
	}
	ausg.Position.dLongitude = (double)(rand()%1801)/10.0;
	ausg.Position.dLatitude= (double)((rand()%1801)-900)/10.0;
	ausg.Position.fAltitude = (float)((rand()%10001)-5000)/10.0f;//Precision of float adds extra randomness. Nice!

	return ausg;
}
/*/
struct Messwert set_mw(int nummer){
	struct Messwert ausg = {nummer, 1.0, {17.0f,18.0f,19.0f} , {80.0, 70.0, 60.0f}};

	return ausg;
}
/*/
