///* 
// * File:   main.cpp
// * Author: vania
// *
// * Created on September 18, 2013, 3:50 PM
// */
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

bool hasduplicate(string);
bool checks(string);
int MisplacedNumbers(string ,string);
int CorrectPositions(string ,string);
string numtostr(int,int,int,int);
string givefeedback(string,string);
void eliminateprobability(int);
string givefeedback(string,string);
void generateProbabilities(void);

int probabilitycount=0;
string probabilities[362880]; /*(9! possibilities not excluding duplicates*/


int main()
{

srand(time(0));
cout<<endl;
cout << "Let's play Mastermind" <<endl;


short int correct,wrongplace,i;
int GuessCounter;
string result;
string feedback;
string lastguess;

string Temp[362880]; 
/*Valid numbers 0 -9*/
/*9! == 362880 possibilities */        

GuessCounter = 0;
i=0;

generateProbabilities();
do 
{
        if(GuessCounter==0)
        {
                cout<<"Feedback will be displayed in the following format: xAyB " <<endl; 
                cout << "Enter in number:";
                cin >> result; //Store number from Human Player
                cout <<endl;
        }

lastguess=probabilities[rand()%probabilitycount];
cout<<"Computer Guesses: "<< lastguess <<endl <<endl;


feedback = givefeedback(lastguess,result); // look at last guess computer gives and

correct = (feedback[0] - '0');
wrongplace = (feedback[2] - '0');
GuessCounter++;
i=0;


do
{
if ((CorrectPositions(probabilities[i],lastguess)!=correct) || (MisplacedNumbers(probabilities[i],lastguess)!=wrongplace))
{
        eliminateprobability(i); 
}
else
i++;
} while ((i<probabilitycount) && (probabilitycount>=0));

} while (((correct!=4) || (wrongplace!=0) )&& (probabilitycount>0));


if (probabilitycount<=0)
{ 
        cout<<" The feedback you have provided is invalid.\n";
        return -1;
}

cout<<"\n I found it in " << GuessCounter <<" Guesses "<<endl;

return 0;
}



bool hasduplicate(string number)
{
int i;
int j;
for (i=0;i<4;i++)
for (j=0;j<4;j++)
{
	if (i!=j)
	if (number[i]==number[j])
        {
            return true;
        }
}
return false;
}



bool checks(string number)
{
if (number.length()!=4) 
    return false; //if not 4 numbers
if (hasduplicate(number))
    return false; // duplicates not allowed
return true;
}



int CorrectPositions(string solution,string guess)
{
int t=0;
for(int i=0;i<4;i++)
{		
if (solution[i]==guess[i])
    t++;
}
return t;
}



int MisplacedNumbers(string solution, string guess)
{
int l=0;
for(int i=0;i<4;i++)
{
        for(int j=0;j<4;j++)
        if((solution[i]==guess[j])&&(i!=j))
        	l++;
}
	return l;
}


 string numtostr(int i,int j,int k,int l)
 {
 string result="";
// add '0' to convert to str
 result+= i + '0';
 result+= j + '0';
 result+= k + '0';
 result+= l + '0';
 return result;
 }


 void eliminateprobability(int i)
 {
     /*Iterate through array and give rid of probabilities that aren't possible*/
        int x;
        for (x=i;x<=probabilitycount;x++)
        {       
                /*Reposition elements in the array*/
                probabilities[x]=probabilities[x+1];
        }
        
        probabilitycount=probabilitycount-1;
 }
 
 string givefeedback(string guess,string sol)
{
     string feedback = ""; // CorrectPosition
     int correctpos=CorrectPositions(sol,guess);
     int correctnums=MisplacedNumbers(sol,guess);
     feedback+= correctpos + '0';
     feedback+="A";
     feedback+=correctnums + '0';
     feedback+="B";
     cout << "Feedback: " <<feedback <<endl;
     return feedback;
  
}
 
 void generateProbabilities()
 {
     int i;
     int j;
     int k;
     int l;
       
        //Generate probability List
        //gives range 0 - 9 
        for (i=0;i<10;i++) 
        for (j=0;j<10;j++) 
        for (k=0;k<10;k++) 
        for (l=0;l<10;l++)
        {
            
           if (checks( numtostr(i,j,k,l) )==true) // add non duplicated numbers to array is ascending order
                {
                        probabilities[probabilitycount]= numtostr(i,j,k,l);
                        probabilitycount+=1;
                }       
        }
   
 }

