//New Program only to fit the Gao function no more 
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include <math.h>  
 #include <stdio.h>
 #include <stdlib.h>

 #define PI 3.14159265
const Int_t numinf=0;
const Int_t numsup=44000;
const int n=numsup-numinf;
float quality(float s[],int n,int db, float f0,float frec[]);
float maximo(float [],int);//Funciones para calcular el maximo de un conjuto de datos
float minimo(float [],int);
float maximofrec(float [],int);
float minimofrec(float [],int);
int Lowf(int f);
int highf(int f, int n);
int funtionf0();
TComplex S12[n],errorz(0.01,0);
TComplex func2(const double f, const double *xpar);
Int_t fwe=funtionf0();
Float_t AS12[n],frec[n],x[n],y[n],s;
const Int_t min1=30000;//Lowf(fwe);
const Int_t max1=33000;//highf(fwe,n);
const int nred=max1-min1;
Float_t xred[n],yred[n],freqredu[n];
int funtionf0(){

int f0;
ifstream in1;
in1.open("test.txt");
in1>>f0;

return f0;
}


int Lowf(int f){

if(f<=18000){return 0;}
else
   return f-10000;

}

int highf(int f,int n){

int g=n-f;
if(g<=18000){return n;}
else
  return f+18000;



}



TComplex func(const double f, const double *xpar){

  TComplex j;
  TComplex tmp;
  TComplex tmp2;
	TComplex tmp3,tmp4;
   Double_t Q;
   Double_t Qc;
   Double_t theta;
   Double_t f0;
   Double_t a;
   Double_t aphase;
   Double_t tau;

   Double_t dx;

	//Double_t tmp4;
  //for fit
  
  Q=xpar[0];
  Qc=xpar[1];
  theta=xpar[2];
  f0=xpar[3];
  a=xpar[4];
  aphase=xpar[5];
  tau=xpar[6];
   


  //  cout << "xpar[9]:" << xpar[9] << endl;
//My funtion  
  dx=(f-f0)/f0;
tmp3=TComplex(a*cos(-2*3.14159*tau*f+aphase),a*sin(-2*3.14159*tau*f+aphase));
tmp2=TComplex(Qc*cos(theta),Qc*sin(theta));
tmp=TComplex(1.,2.*Q*dx);
//j=TComplex(1,0);
tmp4=tmp3*(TComplex(1,0)-tmp2/tmp);

return tmp4;
}
////////////////////////////////////////////////////////////////////////////
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = n;//erro fatal
   //const Int_t fte=minimofrec(AS12,n);
   //cout<<fte<<endl; //break;
   //const Int_t nbins = 5;
   Int_t i;

//calculate chisquare
   Double_t chisq = 0,d;// delta;
   //TComplex delta;
	Double_t delta;
   for (i=min1;i<max1; i++) {
     //delta  = (x[i]-func(frec[i],par))/errorz;
	
 // delta  = (S12[i]-func(frec[i],par))*TComplex::Conjugate(S12[i]-func(frec[i],par))/errorz;
delta =(func(frec[i],par).Re()-x[i])*(func(frec[i],par).Re()-x[i])+(func(frec[i],par).Im()-y[i])*(func(frec[i],par).Im()-y[i]);
d=delta;     

chisq +=d;

  //Check later the definition of Redat -real fit and Imaginaria - imaginariafit  

	}
   f = chisq;
}


void GaoOnlywithoutQc(TString nombrefile1= "100.txt"){
cout<<"min1="<<min1<<"\t"<<max1<<endl;
cout<<nred<<endl;
//int n=40000;
cout<<fwe<<endl;
cout<<"The name of the files is \t"<<nombrefile1<<endl;
ifstream in1;
in1.open(nombrefile1);//Nombre del archivo que 5quieres le
   Float_t x1,y1,z1,w1,e1,q1;
  
Int_t nlines = 0;
for(nlines=0;nlines<n;nlines++) {
     
     in1 >> x1 >> y1 >> z1>>w1>>e1>>q1;
     //Sr1[nlines]=w1;
  	   //Si1[nlines]=y1;
  	   //AS1[nlines]=10*log10(w1*w1+y1*y1);
  	   //freq1[nlines]=x1;
       S12[nlines]=TComplex(w1,y1);// changed to minus -1


AS12[nlines]=10*log10((S12[nlines]*TComplex::Conjugate(S12[nlines])).Re());
//phase[j]=S12[j].Theta();
//AS12[j]=(S12[j]*TComplex::Conjugate(S12[j])).Re();
x[nlines]=S12[nlines].Re();//To do the fit 
y[nlines]=S12[nlines].Im();// To do the fit with the function of the real and imaginary
//s=AS12[j];This is for graph in 3D
frec[nlines]=x1;
  	   //cout<<Sr1[nlines]<<endl;

	//cout<<freq1[nlines]<<"\t"<<Sr1[nlines]<<"\t"<<Si1[nlines]<<endl;
    


    }
    //TGraph *gr1  = new TGraph(nlines,x,y);
    //TGraph *AM1  = new TGraph(nlines,freq1,AS12);




  /// printf(" found %d points\n",nlines);
	in1.close();

int j1=0;
//gr1->Draw();
for (int i = min1; i < max1; ++i)
{
 xred[j1]=x[i];
 yred[j1]=y[i];
 freqredu[j1]=frec[i];
 j1++;
}





int f;
float f0;

TGraph *grred  = new TGraph(nred,xred,yred);
grred->Draw();



f=minimofrec(AS12,n);
f0=frec[f];
cout<<"the position of the resonance frequency is "<<f<<endl;
//int min,max;
//max=highf(f,n);

//cout<<"The Botton f is \t"<<min<<"\t up"<<max<<endl;

cout.precision(10);

float parameters[7];

parameters[3]=   f0;  //f0
parameters[0]= 6000;//quality( AS12,n,5, f0, frec);    //Qr
parameters[1]= 1; //parameters[0];//Qc
parameters[2]=-PI/3;  //theta
parameters[4]= sqrt(x[100]*x[100]+y[100]*y[100]) ;     //a
parameters[5]=  2.80;   //aphase
parameters[6]=  27.7;   //tau


for (int i = 0; i <7; ++i)
{
 cout<<parameters[i]<<endl;
}


TMinuit *gMinuit = new TMinuit(5);  //initialize TMinuit with a maximum of 5 params
   gMinuit->SetFCN(fcn);

   Double_t arglist[10];
   Int_t ierflg = 0;

   arglist[0] = 500;//i changed from 1 to 500
   arglist[1] = 1;
   gMinuit->mnexcm("MIGRAd", arglist ,1,ierflg);//change for set err fto MIGRAd the best algorith 

// Set starting values and step sizes for parameters
   static Double_t vstart[7] = {parameters[0], parameters[1],parameters[2],parameters[3],parameters[4],parameters[5],parameters[6]};
   static Double_t step[7] = {0.00000001 , 0.00000001,0.0000001,0.00000001,0.0000001,0.00000001,0.00000001  };
   gMinuit->mnparm(0, "Qr", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "Qc", vstart[1], step[1], 0,0,ierflg);
   //gMinuit->FixParameter(1);
   gMinuit->mnparm(2, "phi", vstart[2], step[2], 0,0,ierflg);
   gMinuit->mnparm(3, "f0", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "a", vstart[4], step[4], 0,0,ierflg);
   //gMinuit->FixParameter(4);
gMinuit->mnparm(5, "argaa", vstart[5], step[5], 0,0,ierflg);
   //gMinuit->FixParameter(5);
gMinuit->mnparm(6, "tau", vstart[6], step[6], 0,0,ierflg);
//gMinuit->FixParameter(6);
// Now ready for minimization step
   arglist[0] = 500;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

cout.precision(10);
cout << "\nPrint results from minuit\n";
  double parameters2[7];
  double fParamErr;
  gMinuit->GetParameter(0,parameters2[0],fParamErr);
  cout  << parameters2[0] <<"\t" <<fParamErr<<"\n";
  gMinuit->GetParameter(1,parameters2[1],fParamErr);
  cout  << parameters2[1] <<"\t" <<fParamErr<< "\n";
  gMinuit->GetParameter(2,parameters2[2],fParamErr);
  //parameters2[2]=-PI/3;
  cout << parameters2[2]*180/PI <<"\t" <<fParamErr<< "\n";
  gMinuit->GetParameter(3,parameters2[3],fParamErr);
  cout  << parameters2[3]<<"\t" <<fParamErr << "\n";
gMinuit->GetParameter(4,parameters2[4],fParamErr);
  cout  << parameters2[4] <<"\t" <<fParamErr<< "\n";

gMinuit->GetParameter(5,parameters2[5],fParamErr);
  cout  << parameters2[5]<<"\t" <<fParamErr << "\n";

gMinuit->GetParameter(6,parameters2[6],fParamErr);
  cout  << parameters2[6]<<"\t" <<fParamErr<< "\n";
//cout<<"thank for use israel's programs";

//float maxfre=frec[n-1];
//float minfrec=frec[0];
//float delta2=(maxfre-minfrec)/n;
float ko[n],ko2[n];
for(int i=0;i<n;i++){
//calis=func(frec[i],parameters);
ko2[i]=func(frec[i],parameters2).Re();//func(frec[i],parameters2).Re();
ko[i]=func(frec[i],parameters2).Im();//(func(frec[i],parameters2)).Im();

}


    TCanvas *c1 = new TCanvas("c1","Graph Example",200,10,700,500);

 TGraph *gr1FIT  = new TGraph(nlines,ko2,ko);
TMultiGraph *mgFIT = new TMultiGraph();
   //mg->SetTitle("E");
   

    //TGraph *AM1  = new TGraph(nlines,freq1,AS12);
   gr1FIT -> SetMarkerStyle(21);
gr1FIT -> SetMarkerColor(2);
gr1FIT -> SetLineColor(2);
gr1FIT -> SetMarkerSize(0.5);

 TGraph *gr2FIT = new TGraph(nlines,x,y);
//gr2FIT->SetTitle("2.78604 3433  ");
//gr1->Draw();
//gr2->DrawClone("Sames");
 double perr=12;
 gr2FIT -> SetMarkerStyle(21);
gr2FIT -> SetMarkerColor(9);
gr2FIT -> SetLineColor(9);
gr2FIT -> SetMarkerSize(0.5);
  

//gr1FIT->DrawClone("APE");
//gr2FIT->DrawClone("Sames");

mgFIT->Add(gr2FIT);
mgFIT->Add(gr1FIT);


mgFIT->Draw("APE");
Double_t val3=parameters2[0];
Double_t val = parameters2[3];
Double_t val22=parameters2[1];  


  ostringstream textOSS;
  textOSS  << val<<"\t\t"<<val3<<"\t\t"<<val22;

  cout << textOSS.str() << endl;



 TLegend *leg = new TLegend(0.1,0.7,0.7,0.9);
leg->AddEntry(gr1FIT,textOSS.str().c_str() ,"l");
leg->AddEntry(gr2FIT,"Experimental Data" ,"f");
//leg->AddEntry(gr,"The Data","p");
//leg->Draw();
// oops we forgot the blue line... add it after
//leg->AddEntry(fun2,"#sqrt{2#pi} P_{T} (#gamma) latex  formula","f");
// and add a header (or "title") for the legend
leg->SetHeader("Parameters \t f_{0}\t\tQ_{r}\t\t Q_{c}");



leg->Draw(); 


cout.precision(10);
TFile fcd("RESONADOR1.root","UPDATE");  
c1 ->Write("GaoFit");
     //c1 -> Update();
     //c1 -> Modified();

//mgFIT->Write("Critiereser");
std::ofstream outfile2 ("GaoParameters.txt");

outfile2 << parameters2[0]<<"\t"<< parameters2[1]<<"\t"<< parameters2[2]<<"\t"<< parameters2[3]<<"\t"<< parameters2[4]<<"\t"<< parameters2[5]<<"\t"<< parameters2[6]<<"\t" <<std::endl;

outfile2.close();





}








///////////////
float maximo(float vals[], int numels)
{

int i; float max;


  max = vals[0]; 

  for (i = 0; i < numels; i++) {
    if (vals[i] > max) 
    max = vals[i]; 
}
return max;
}

float minimo(float vals[], int numels)
{

int i; float max;


  max = vals[0]; 

  for (i = 0; i < numels; i++) {
    if (vals[i] < max) 
    max = vals[i]; 
}
return max;
}
//Funcion para devolver la posicion de la frecuencia al maximo valor

float maximofrec(float vals[], int numels)
{

int i; float max;
int j=0;


  max = vals[0]; 

  for (i = 0; i < numels; i++) {
    if (vals[i] > max){ 
    max = vals[i]; 
           j=i;}

}
return j;
}

//Funcion 

float minimofrec(float vals[], int numels)
{

int i; float max;
int j=0;

  max = vals[0]; 

  for (i = 0; i < numels; i++) {
    if (vals[i] < max) {
    max = vals[i]; 
j=i;}
}
return j;
}

float quality(float s[],int n,int db, float f0,float frec[]){
int i;
int j=0;
int q=0;
float maxim;
maxim=s[1]-db;
//cout<<maxim<<endl;
for(i=0;i<n;i++){

if(s[i]<maxim)
{
q=i;
j++;

}


}
//cout<<q<<"\t"<<j<<endl;
float Qr;
Qr=f0/(frec[q]-frec[q-j]);
return Qr;

}



