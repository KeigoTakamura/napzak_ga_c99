#include<stdlib.h>
#include<time.h>
#include<stdio.h>



int main(){
	srand((time_t)time(NULL));
	float frand=(float)RAND_MAX;
	printf("rand()%d %f\n",RAND_MAX, rand()/frand);

return 0;
}
