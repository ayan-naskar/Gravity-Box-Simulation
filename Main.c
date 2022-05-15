/*
have vectors x,y
add force
damp vector
if caught by wall
reverse vectors
damp vector
print
*/

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<math.h>

#define gravity_strength 0.3
#define damping 0.01

typedef struct vector_VALUES vec;

struct vector_VALUES{
	float x,y;//These are vector components of the particle
	int mass;
	float posx,posy;//current position of the particle in the matrix
	int size_a,size_b;//size of the matrix in which the particle belongs()kind of opposite of x,y
};

void initialize(vec *p,int m,int a, int b){
	p->x=p->y=0.0;
	p->mass=m;
	p->size_a=a;
	p->size_b=b;
	p->posx=p->size_b/2;
	p->posy=p->size_a/2;
}

void changeState(int direction, vec *p){//clockwise from '0 is up' to '3 is left' and '-1 is no force'
	float new_state=(gravity_strength/p->mass)*(1-damping);
	switch(direction){
		case 0:
			p->y=p->y-new_state;
			break;
		case 1:
			p->x+=new_state;
			break;
		case 2:
			p->y+=new_state;
			break;
		case 3:
			p->x-=new_state;
	}
	p->x=p->x * (1-damping);
	p->y=p->y * (1-damping);
	p->posx+=p->x;
	p->posy+=p->y;
	/*if(p->posx<0 || p->posx>p->size_b)
		p->posx=(float)p->size_b-((int)p->posx % p->size_b);
	if(p->posy<0 || p->posy>p->size_a)
		p->posy=(float)p->size_a-((int)p->posy % p->size_a);*/
	if(p->posx<0){
		p->posx=-p->posx;
		p->x=-p->x;
	}
	if(p->posx>=p->size_b){
		p->posx=p->size_b-(p->posx-p->size_b);
		p->x=-p->x;
	}
	if(p->posy<0){
		p->posy=-p->posy;
		p->y=-p->y;
	}
	if(p->posy>=p->size_a){
		p->posy=p->size_a-(p->posy-p->size_a);
		p->y=-p->y;
	}
}

void showEnvironment(vec *p){
	int i,j;
	system("cls");
	printf("  ");
	for(i=0;i<p->size_b;i++) printf("# ");
	puts("");
	for(i=0;i<p->size_a;i++){
		printf("# ");
		for(j=0;j<p->size_b;j++){
			if((int)round(p->posx)==j && (int)round(p->posy)==i) printf("* ");
			else printf("  ");
		}
		printf("#\n");
	}
	printf("  ");
	for(i=0;i<p->size_b;i++) printf("# ");
	printf("\nposx=%f\tposy=%f",p->posx,p->posy);
}

int getDirection(){
	if(GetAsyncKeyState(VK_UP)) return 0;
	else if(GetAsyncKeyState(VK_RIGHT)) return 1;
	else if(GetAsyncKeyState(VK_DOWN)) return 2;
	else if(GetAsyncKeyState(VK_LEFT)) return 3;
	return -1;
}

void simulate(vec *p){
	while(1){
		changeState(getDirection(),p);
		showEnvironment(p);
		Sleep(50);
	}
}

vec* inputFromUser(){
	int m,a,b;
	vec *p=(vec*)malloc(sizeof(vec));
	printf("Enter the mass of the particle: ");
	scanf("%d",&m);
	printf("Enter the size of the Environment: ");
	scanf("%d%d",&a,&b);
	Sleep(3000);
	system("cls");
	initialize(p,m,a,b);
	return p;
}

int main(){
	vec *particle;
	particle=inputFromUser();
	simulate(particle);
}
/*
INTPUT

1
20 20

*/