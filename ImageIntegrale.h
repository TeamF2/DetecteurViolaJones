#ifndef IMAGEINTEGRALEH
#define IMAGEINTEGRALEH

#include <vector>
#include <thread>
#include <sstream>
#include "CImg.h"

//Affiche une matrice
void printData(std::vector<std::vector<long> >& data);


//Calcul de l'image integrale d'une image (img)
std::vector<std::vector<long>> SAT(const cimg_library::CImg<long>& img);


//Classe auxiliare qui represente une caracteristique
class feature{
public:
	int x,y,w,h;
	char type;

	feature(int,int,int,int,char);
};


//Calcule la caracteristique f pour l'image dont la matrice image integrale est sat
long calcFeat(std::vector<std::vector<long>>& sat, feature& f);


//Cree des feat de type 'type', avec largeur maximale wMax et hauteur maximale hMax
void featVect(std::vector<feature>& feats, char type,int& wMax, int& hMax);


//Cree des feats en parallele
std::vector<feature> distFeat(int& width, int& height);


//Classe auxiliare qui represente un classifieur
class classifier{
public:
	double w1,w2;
	classifier();
	int calc(double);
};


//readImgs et distII : lecture et creation des matrices de II pour les images d'un repertoire
void readImgs(int& nTasks, int taskId,bool pos,int& nPos, std::vector<std::vector<std::vector<long>>>& iis ,std::string rep);

std::vector<std::vector<std::vector<long> > > distII(int& nTasks, int& nPos,int& nNeg, std::string rep);


//train et parTrain : Entrainement en parallele des classifieurs dans classf; parametres : eps et K
//methode du perceptron
void train(int& nTasks, int taskId,int& nPos, std::vector<std::vector<std::vector<long>>>& tables,
		std::vector<classifier>& classf, std::vector<feature>& feats, double& eps, int& K);

void parTrain(int& nTasks,int& nPos, std::vector<std::vector<std::vector<long>>>& tables,
		std::vector<classifier>& classf, std::vector<feature>& feats, double& eps, int& K);


//Fonction d'erreur definie en 2.2
bool error(classifier& classf, int c,feature& feat,std::vector<std::vector<long>>& sat);


//chooseClasf et parChooseClasf : choix du classifieur faible minimisant l'erreur ponderee
void chooseClasf(int& nTasks, int taskId, int& nPos, double& currerr,int& ind,
std::vector<classifier>& classf, std::vector<double>& weights,
std::vector<feature>& feats, std::vector<std::vector<std::vector<long>>>& tables);

int parChooseClasf(int& nTasks, int& nPos, double& error,int ind, 
std::vector<classifier>& classf, std::vector<double>& weights, std::vector<bool>& c, 
std::vector<feature>& feats, std::vector<std::vector<std::vector<long>>>& tables);


//updateWeights et parUpdateWeights : mise a jour des poids
void updateWeights(int& nTasks, int Taskid,std::vector<double>& weights,double& alfak,classifier& classf, std::vector<std::vector<std::vector<long>>>& tables, int nPos, std::vector<feature>& feats, int clas);

void parUpdateWeights(std::vector<double>& weights,double& alfak,classifier& classf, std::vector<std::vector<std::vector<long>>>& tables, int& nTasks, int& Npos, std::vector<feature>& feats, int& clas);


//algorithme Adaboost
std::vector<double> boost(int& nTasks,int& nPos, std::vector<classifier>& classf,std::vector<std::vector<std::vector<long>>>& tables, std::vector<feature>& feats);


//F, parF : Calcul de F(x), le classifieur final
int F(std::vector<double>& alfa, std::vector<feature>& feats,std::vector<classifier>& classf, std::vector<std::vector<long>>& sat,double theta);

void parF(int& nTasks, int taskId, int& nPos, std::vector<long>& fauxNP, std::vector<double>& weights,std::vector<feature>& feats,std::vector<classifier>& classf, std::vector<std::vector<std::vector<long>>>& sats,double theta);


//fontion de test : renvoie le taux de faux negatifs et le taux de faux positifs
std::vector<long> test(int& nTasks, std::vector<double>& weights, std::vector<feature>& feats, int& nPos,
		std::vector<classifier>& classf, std::vector<std::vector<std::vector<long>>>& sats,double theta);

#endif
