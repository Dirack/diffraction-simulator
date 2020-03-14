/* Version 1.0 - Generate diffraction simulated hyperbolas in the stacked section
 
Programer: Rodolfo A. C. Neves (Dirack) 14/09/2019

Email:  rodolfo_profissional@hotmail.com 

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <rsf.h>

int main(int argc, char* argv[])
{

	float pm0; // picked m0's in the stacked section
	float pt0; // picked t0's in the stacked section
	float v; // picked velocity for m0's and t0's
	float** stackedSection; // stacked section A(t0,m0)
	float aperture; // simulated hyperbolas aperture
	int nt0; // number of t0's in stacked section
	float dt0; // t0 axis sampling
	float ot0; // t0 axis origin
	int nm0; // number of m0's in stacked section
	float dm0; // m0 axis sampling
	float om0; // m0 axis origin
	bool verb; // verbose parameter

	/* RSF files I/O */
	sf_file in, out;

	/* RSF files axis */

	sf_init(argc,argv);

	in = sf_input("in");
	out = sf_output("out");

	/* Read stacked section geometry */
	if(!sf_histint(in,"n1",&nt0)) sf_error("No n1= in input");
	if(!sf_histfloat(in,"o1",&ot0)) sf_error("No o1= in input");
	if(!sf_histfloat(in,"d1",&dt0)) sf_error("No d1= in input");
	if(!sf_histint(in,"n2",&nm0)) sf_error("No n2= in input");
	if(!sf_histfloat(in,"d2",&dm0)) sf_error("No d2= in input");
	if(!sf_histfloat(in,"o2",&om0)) sf_error("No o2= in input");
	
	if(!sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	if(!sf_getfloat("v",&v)) v=1.5;
	/* Hyperbola velocity (Km/s) */

	if(!sf_getfloat("pm0",&pm0)) pm0=(om0+nm0*dm0)/2;
	/* picked m0 (Km) */

	if(!sf_getfloat("pt0",&pt0)) pt0=(ot0+nt0*dt0)/2;
	/* picked t0 (s) */

	if(!sf_getfloat("aperture",&aperture)) aperture=1;
	/* Diffraction hyperbolas aperture */

	if(verb){
		sf_warning("Active mode on!!!");
		sf_warning("Input file parameters: ");
		sf_warning("n1=%d d1=%f o1=%f",nt0,dt0,ot0);
		sf_warning("n2=%d d2=%f o2=%f",nm0,dm0,om0);
	}

	stackedSection = sf_floatalloc2(nt0,nm0);
	sf_floatread(stackedSection[0],nt0*nm0,in);
	sf_floatwrite(stackedSection[0],nt0*nm0,out);

}
