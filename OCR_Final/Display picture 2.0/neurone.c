#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double sigmoid(double x)
{
  return 1 / ( 1 + exp(-x));
}




// This function give the result expected by the network
double xor(double x,double y)
{
  if (x==y)
    {
      return 0;
    }
  else
    return 1;

}


double xorn(double x,double y)
{

  // all variables used

  double z = 0;// values of activation.
  double h = 0;
  double bz = 1;// values of bias
  double bh = 1;
  double poids_yh = 0;//values of the weight of connection
  double poids_xh = 0;
  double poids_bhh = 0;
  double poids_yz = 0;
  double poids_xz = 0;
  double poids_hz = 0;
  double poids_bzz = 0;
  double target = 0;// value of the result expected
  double zerror = 0;// values of the error between exppected and the result
  double herror = 0;
  //double bherror = 0;
  //double bzerror = 0;
  double pas_v = 0.1;//value of the speed of learning

  
  target = xor(x,y); // find the result expected
  for (int i = 0; i< 24000; i++)
    {     
      h = sigmoid( x * poids_xh + bh * poids_bhh + y * poids_yz );// compute the values of activation
      z = sigmoid( x * poids_xz + h * poids_hz + y * poids_yz );
      zerror = ( target -  z ) * ( z * ( 1 - z ));//Compute the error of the output
      poids_xz = ( pas_v * zerror * x ) - poids_xz; // compute the weights of connections linked with the output
      poids_yz = ( pas_v * zerror * y ) - poids_yz ; 
      poids_hz = ( pas_v * zerror * h ) - poids_hz;
      poids_bzz = ( pas_v * zerror * bz ) - poids_bzz;
      herror = ( h * ( 1  - h)) * poids_hz * zerror;// compute the error of the hidden neurone
      poids_xh = ( pas_v * herror * x ) - poids_xh ;// compute the weights of the conectiokns linked with the hidden neurone
      poids_yh =  ( pas_v * herror * y ) - poids_yh;
      poids_bhh = (pas_v *herror * bh ) - poids_bhh;
    }
  return z ; 
}
