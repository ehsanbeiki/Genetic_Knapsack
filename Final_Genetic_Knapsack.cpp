#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include <math.h>	    /* pow */

//		Ehsan Beiki,M.Sadegh Daghigh
//
using namespace std;

void CalculateFitness(int **Population , int i,int Fitness[]); // The function of calculating fitness for each chromosome
void CreateRandomPopulation (int **population,int Fitness[]); // The function of generating the initial population randomly
void Reproduce(int x[],int y[],int child[]); // The function of generating child chromosome from parent chromosomes
void mutation(int child[]); // The function of performing mutation on the child chromosome
int GeneticKnapsack(int **Population , int Fitness[],int BestChoro[]); // The function of gaining the optimal chromosome
int RandomSelection(int **Population , int Fitness[]); // The function of selecting parent chromosomes randomly

int const GenerationThreshold=100000; // A variable as the generation threshold  initialized with the value 100000
int n,Capacity,MaxChromosome; // Variables to store the number of items, the capacity of the backpack and the maximum number of chromosomes
vector <int> p,w,ChoroWeight; // Vectors to store the profit and weight of items and the weight of chromosomes


void CalculateFitness(int **Population , int i,int Fitness[])
{
	
	ChoroWeight[i]=0;
	Fitness[i]=0;
	
	for(int j=0 ; j<n ; j++)                            
		if(Population[i][j]==1)
			ChoroWeight[i]+=w[j]; 
			                                             
	if(ChoroWeight[i]<=Capacity)                              // The function of calculating fitness for each chromosome
	{
		for(int j=0 ; j<n ; j++)
			if(Population[i][j]==1)
				Fitness[i]+=p[j];		
	}

	else
		Fitness[i]=0;
	
}

void CreateRandomPopulation (int **population,int Fitness[])
{
	for(int i=0;i<MaxChromosome;i++)
	{	
		for(int j=0;j<n;j++)	                                  // The function of generating the initial population randomly
			population[i][j]=rand()%2;	
    	CalculateFitness(population , i , Fitness );			
	}
}

int RandomSelection(int **Population , int Fitness[])
{
	int sumfit[MaxChromosome]={0};
	sumfit[0]=Fitness[0];                                           
	
	for (int i=1;i<MaxChromosome;i++)
		sumfit[i]=sumfit[i-1]+Fitness[i];


	int RandomChoro = 1+rand()%sumfit[MaxChromosome-1];                 // The function of selecting parent chromosomes randomly
	
	if(RandomChoro<=sumfit[0])
	 return 0;
	for (int i=1;i<MaxChromosome;i++)
	{
		if(RandomChoro>sumfit[i-1] && RandomChoro<=sumfit[i])
			return i;			
	}
		
}
void Reproduce(int x[],int y[],int child[])
{
	int c = rand()%n;
	for(int i=0;i<c;i++)
		child[i]=x[i];                                       // The function of generating child chromosome from parent chromosomes
		
	for(int i=c;i<n;i++)
		child[i]=y[i];
		
}
void mutation(int child[])
{
	int m = rand()%n;
	if (child[m]==0)                                        // The function of performing mutation on the child chromosome
		child[m]=1;                                                
	else
		child[m]=0;
}
int GeneticKnapsack(int **Population , int Fitness[],int BestChoro[])
{
int generation=0;
		
while(generation<GenerationThreshold)
{
//++ctr;	
	int **NewPopulation;
	NewPopulation = new int *[MaxChromosome];                     
	for(int i = 0; i <MaxChromosome; i++)
		NewPopulation[i] = new int[n];	                          
		
	for(int k=0;k<MaxChromosome;k++)
	{		
		int xi=RandomSelection(Population,Fitness);	
		int yi=RandomSelection(Population,Fitness);
		
//		while (xi==yi)
//		{
//			yi=RandomSelection(Population,Fitness);	
//		}
		int* x=Population[xi];
		int* y=Population[yi];
		
		int child[n];
		Reproduce(x,y,child);
					
		if((rand()%100)<5)
			mutation(child);
		
		for(int j=0;j<n;j++)
			NewPopulation[k][j]=child[j];			                     // The function of gaining the optimal chromosome
	}
	
	for(int i=0;i<MaxChromosome;i++)
		for(int j=0;j<n;j++)
			Population[i][j]=NewPopulation[i][j];	

	for(int i=0;i<MaxChromosome;i++)
		CalculateFitness(Population , i , Fitness );
		
	++generation;

	if(generation>GenerationThreshold/100)
	{
		for(int j=0;j<MaxChromosome;j++)
			if(ChoroWeight[j]==Capacity)
			{
//				cout <<"\nChoroWeight[j]" <<ChoroWeight[j];
//				cout<<"\n\n*************************************\n;
//				cout <<"\nChoroWeight:" <<ChoroWeight[j]<<"\n";
//				cout <<"\nFitness:" <<Fitness[j]<<"\n";
				generation=GenerationThreshold;	
				break;	
			}
	
	}

}
	int best;
	best = 0;
 	for(int i=1;i<MaxChromosome;i++)
		if (Fitness[i]>Fitness[best])
			best=i;

	for(int j=0;j<n;j++)
		BestChoro[j]=Population[best][j];
//	cout<<"\nThe Best Chromosome Fitnes:\t"<<Fitness[best];
//	cout<<"\nThe Best Chromosome Weight:\t"<<ChoroWeight[best]<<"\n\n";
	
	return best;
}


int main() {
while(1)
{
	cout <<"Plz Enter The Number Of Items and The Capacity of Your KnapSack : " ;
	cin >> n >> Capacity;                                                              // Get the number of items and the capacity of the backpack
	
	p.resize(n);
	w.resize(n);
	
	MaxChromosome=2*n;//pow(2,n);
	
	int Fitness[MaxChromosome];
	ChoroWeight.resize(MaxChromosome);                                               // two arrays to store the fitness and weight of chromosomes
	
	for (int i=0 ; i<n ; i++)
	{
	    cout <<"Plz Enter The Weight And Then The Profit Of Item" << i<<":" ;
		cin >> w[i] >> p[i] ;	                                                    // Get and store the weight and profit of each item
	}
	int **Population;
	Population = new int *[MaxChromosome];
	for(int i = 0; i <MaxChromosome; i++)                                         // a two-dimensional array to store the initial population of chromosomes
		Population[i] = new int[n];

	srand(time(0));   // Randomize over time
int ctr=0;    // A counter initialized with 0
int solotion[n][n+2]; // An array to store the best chromosomes
while(ctr<n)
{
	CreateRandomPopulation(Population,Fitness);		 // Create a random initial population			

	int BestChoro[n];                                      // An array to store the best chromosome
	int best = GeneticKnapsack(Population ,Fitness,BestChoro);   // Calling the GeneticKnapsack function and storing the index of the best chromosome

//	cout <<"\nThe Solution is:\n";
//	for(int j=0;j<n;j++)
//		cout<<BestChoro[j]<<"\t";
//	cout << "\n\n\n";
	for(int j=0;j<n;j++)
		solotion[ctr][j]=BestChoro[j];	// Adding the best chromosome obtained each time the algorithm is executed to the solotion array
	solotion[ctr][n]=Fitness[best];
	solotion[ctr][n+1]=ChoroWeight[best];    // Adding the fitness and weight of the best chromosome obtained in the nth and n+1th elements of the solotion array, respectively
	++ctr;
}

int ans;
	ans=0;
 	for(int i=1;i<n;i++)
		if (solotion[i][n]>solotion[ans][n])           // Finding (index of) the best chromosome among the chromosomes stored in the solotion array
			ans=i;	
			
	cout<<"\nThe Best Chromosome Fitnes:\t"<<solotion[ans][n];
	cout<<"\nThe Best Chromosome Weight:\t"<<solotion[ans][n+1]<<"\n\n";		 // Display the fitness and weight of the best chromosome	
	cout <<"\nThe Solution is:\n";
	
	for(int j=0;j<n;j++)
		cout<<solotion[ans][j]<<"\t";          // Display the best chromosome (solution)
	cout << "\n\n\n";	
	
}		
    
return 0;

}





