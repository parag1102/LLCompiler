#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stack>
//#include "../LL1/header1.h"
#include "../LL1/header2.h"
//#include "../LL1/header3.h"
//#include "../LL1/header4.h"

using namespace std;

//int l=0;
int flag=0,ambig_flag=0;
int error_table[10][10];									//declaring global arrays and variables
char line[500];
char tokenized[10][10][50];
char tokenized_first_rhs[10][10][50] = {{""}};
char tokenized_follow_rhs[10][10][50];
char tokenized_input[10][50];
/*char non_term[10][10] = {"E" , "E'" , "T" , "T'" , "F" , {'\0'}};
char term[10][10] = {"+" , "*" , "id" , "(" , ")" , "$" , {'\0'}};
char start[10] = "E";
char productions_lhs[10][10] = {"E",
				//"E",
				//"E",
				"E'",
				"E'",
				"T",
				//"T",
				"T'",
				"T'",
				"T'",
				"F",
				"F",
				{'\0'}};

char productions_rhs[10][50] = {"T' E' T'",
				//"T",
				//"E + T",				
				//"T E1",
				"+ T E'",
				"eps",
				//"F",
				//"T * F",				
				"F T'",
				"F T'",
				"* F T'",
				"eps",				
				"id",
				"( E )",
				{'\0'}};*/

char first_table[10][50] = {""};
char follow_table[10][50] = {""};
char first_table_rhs[10][50] = {""};
char follow_table_rhs[10][50] = {""};
int ll1_table[10][10];

void put_eps_in_all_or_not(int bit);
void remove_spacestabs(char *line);
void interpreting_grammar(char *file_name);	               	   		//function declarations
void first(int f,char *nt);
void follow(int f,char *nt);
void tokenize_input(char*,char*);
void create_table();
void tokenize(char*);
void parsing(char*);
void left_recursion();
void check_ll1();


int main()
	{
		char inp[50];		
		int h=0,w=0,l1=0,l2=0;
		for(h=0; h<10;h++)
			{
			for(w=0;w<10;w++)			
				{ll1_table[h][w]=-1;error_table[h][w]=1;}
			//strcpy(tokenized[h][w],"");
			}
		
		/*char file[50];
		cout<<"Enter the file name (write multiply.txt)"<<endl;		        //length of the file name can be 50 characters long.
		cin.getline(file,50);*/   	                               		//That's why 51 is given as the second argument in 'getline'
		//cout<<non_term[0]<<endl;		
		char str[10];
		int b=0;

		left_recursion();

		/*h=0;
		while(non_term[h][0] != '\0')
			{cout<<h<<" "<<non_term[h]<<endl;h++;}	*/	
		h=0;
		while(productions_rhs[h][0] != '\0')
			{
			cout<<h<<" "<<productions_lhs[h]<<"\t-> ";
			w=0;			
			while( (tokenized[h][w][0]) != '\0')			
				{cout<<tokenized[h][w]<<" ";/*"; "*/;
				w++;}
			cout<<endl;
			h++;
			}

		//cout<<tokenized[0][2]<<endl;
		
		put_eps_in_all_or_not(0);
	
		/*cout<<endl<<"FIRST values:"<<endl;
		while(non_term[b][0] != '\0')
			{
			strcpy(str,non_term[b]);			
			strcpy(first_table[b],str);
			strcat(first_table[b],":\t");			
			first(b,str);							//calling the function 'first'
			cout<<first_table[b]<<endl;
			b++;		
			}*/

		b=0;
		cout<<endl<<endl<<"---------FOLLOW values:----------"<<endl;
		while(non_term[b][0] != '\0')
			{
			strcpy(str,non_term[b]);			
			strcpy(follow_table[b],str);
			strcat(follow_table[b],":\t");			
			follow(b,str);							//calling the function 'follow'
			cout<<follow_table[b]<<endl;
			b++;		
			}
		
		/*strcpy(str," ");
		tokenize(str)	;*/	
		/*h=0;
		while(productions_rhs[h][0] != '\0')
			{
			w=0;			
			while( (tokenized_follow_rhs[h][w][0]) != '\0')			
				{cout<<tokenized_follow_rhs[h][w]<<"; ";
				w++;}
			cout<<endl;
			h++;
			}	*/
		
		create_table();

		cout<<endl<<endl;
		check_ll1();

		cout<<endl<<endl<<"-----------------------------------------LL1 TABLE:------------------------------------------"<<endl<<endl<<endl;
		h=0;
		while(non_term[h][0] != '\0')
			{
			cout<<"\t  ";
			l2=0;
			if(h==0)
				while(term[l2][0] != '\0')				
					{cout<<term[l2]<<"\t\t  ";l2++;}
			cout<<endl;

			cout<<non_term[h]<<"\t  ";

			w=0;
			while(term[w][0] != '\0')
				{				
			
				if(ll1_table[h][w] != -1)
					{
					cout<<productions_lhs[ ll1_table[h][w] ]<<" -> ";					
					l1=0;
					while( strcmp(tokenized[ ll1_table[h][w] ][l1],"") != '\0')
						{cout<<tokenized[ ll1_table[h][w] ][l1]<<" ";l1++;}
					cout<<"\t  ";		
					/*leng1=strlen(productions_lhs[ ll1_table[h][w] ]);
					leng2=strlen(productions_rhs[ ll1_table[h][w] ]);
					cout.write(productions_lhs[ (ll1_table[h][w]) ],leng1)<<" -> ";
					cout.write(productions_rhs[ (ll1_table[h][w]) ],leng2)<<"\t\t";*/
					/*l1=0;
					while(productions_lhs[h][l1] != '\0')
						{
						cout<<productions_lhs[ ll1_table[h][w] ][l1];
						l1++;					
						}
					cout<<" -> ";					

					l2=0;
					while(productions_rhs[h][l2] != '\0')
						{
						cout<<productions_rhs[ ll1_table[h][w] ][l2];
						l2++;					
						}
					cout<<"\t\t";*/
					}
				else if(ll1_table[h][w] == -1)
					cout<<"NL"<<"\t\t  ";
				//cout<<ll1_table[h][w]<<"\t";
				w++;
				}
			cout<<endl;
			h++;
			}

		/*cout<<endl<<endl<<"ERROR TABLE:"<<endl;
		h=0;
		while(non_term[h][0] != '\0')
			{
			w=0;
			while(term[w][0] != '\0')
				{cout<<error_table[h][w]<<"\t  ";w++;}
			cout<<endl;
			h++;
			}*/
		//strcpy(inp,"");
		//string fhg ="id + + id";
		strcpy(inp,"id + id * id");
		//strcpy(inp,"id + + id");
		//strcpy(inp,"( ( ( ) ( ) ) ( ) )");
		//strcpy(inp,"a b a b a b");
		
		if(flag == 0)
			{parsing(inp);
			return 0;}
		else
			{cout<<endl<<endl<<endl<<"-------------------PARSING NOT VALID for this Grammar-----------------"<<endl<<endl<<endl;
			 cout<<endl<<endl<<"---------------------EXITING------------------------"<<endl<<endl<<endl;
			return 0;}

	}


void remove_spacestabs(char* line)
	{
		char arr1[100];
		int j=0;
		for(int i=0;line[i]!='\0'&&line[i]!='#';i++)          				//checking for the end of the line or the start of the comment
			{
				if(line[i]==' ' || line[i]=='\t')				//removing spaces and tabs
					continue;
				else
					{
						arr1[j]=line[i];                                //copying the contents of 'line' in 'arr1' without any spaces or tabs
						j++;
					}
			}
		arr1[j]='\0';									//making the character array 'arr1' a string
		if(arr1[0]=='\0')
			line[0]='\0';
		else
			strcpy(line,arr1);                                                	//now 'line' contains no spaces or tabs
	}


/*void interpreting_grammar(char *file)
	{
		ifstream fin;
		fin.open(file,ios::in);        						//opening the requested file
		fin.getline(line,100);                                          //instruction are of maximum length 100 characetrs .We can increase it if we wish to
		remove_spacestabs(line);

		cout<<"The variable names and their corresponding values are -:"<<endl;
		int g=0;
		for(g=0;g<3;g++)     		                                		//checking the lines before '.end'
			{
				if( (strcmp(line,"\0")==0) || (strcmp(line,".start")==0) )      //skipping '.start' keyword or any blank line
					{
						fin.getline(line,100);
						remove_spacestabs(line);
						continue;
					}
				char *s;
				s=strchr(line,'}');						//checking the end of the non-terminals list in the grammar file
				char *p;
				p=strchr(line,'{');				
				char variable_name[50];
				int x=0;				
				int k=0;
				//char *pointer = line;				
				while((p!=s))
					{
							for(x=0;(*p)!=',';x++)
								{
								non_term[k][x]=*p;              //getting the name of the non_terminals or terminals or start-symbol 

								cout<<non_term[k][x];								
								p++;

								}

						non_term[k][x]='\0';                           	//making the character array 'non_term[k]' a string

						p++;						//moving the pointer to skip ','		
						k++;

					}

				

				char* parag=non_term[k];

				int z=strlen(parag);

				cout.write(parag,z)<<endl;

			}
	}*/


void first(int f, char* nt)
	{
		int len = strlen(nt);
		//cout<<"haha";		
		
		char tokens[10][50];	
		char temp[50];	
		int list[10];	
		int j=0,o=0,m=0,c,i=0;	
		for(j=0;j<10;j++)
			{
			if( (strcmp(productions_lhs[j],nt)) == 0 )
				{list[o]=j;o++;}
			}
		int b=0;
		for(int n=0;n<o;n++)
			{
			b=0;
			/*int l=0;
			int len = strlen (productions_rhs[list[n]]);
			cout<<len<<"haha"<<endl;
			while(productions_rhs[list[n]][m] != '\0')
				{
				while( (productions_rhs[list[n]][m] != ' ') && (productions_rhs[list[n]][m] != '\0') )			
					{
					tokens[l][c]=productions_rhs[list[n]][m];
					m++;c++;
					}
				tokens[l][c]='\0';
				cout<<tokens[l]<<endl;
				l++;c=0;
				if( m < len )
					m++;				
				}*/

			int h=0;
			/*char *u = strtok(productions_rhs[list[n]], " ");
		
			int l=0;		
			while (u != NULL)
				{
				//cout<<u<<endl;
				strcpy(tokens[l],u);
				strcpy(tokenized[list[n]][l],u);
				if(list[n]==0)				
					cout<<tokenized[list[n]][l]<<endl;
				u = strtok(NULL, " ");
				l++;
				}
			strcpy(tokens[l],"");*/

								
			//b=0;
			//i=0;
			again1:		
			for(i=0;i<10;i++)
				{
				//b=0;
				//again1;
				//if(f==0)				
					//{cout<<i<<"list"<<list[n]<<" "<<tokenized[ list[n] ][b]<<endl;}
				if( (strcmp(term[i],tokenized[ list[n] ][b])) == 0 )
					{
					strcpy(temp,",");
					strcat(temp,tokenized[ list[n] ][b]);				
					strcat(first_table_rhs[f],temp);
					strcat(first_table[f],temp);
					//cout<<j<<endl;
					//table[f][i] = (list[n]);
					break;				
					}
				else 
					{
					if((strcmp(non_term[i],tokenized[ list[n] ][b])) == 0)					
						{
						//again1:
						//cout<<i<<tokenized[ list[n] ][b]<<endl;						
						if(strcmp(tokenized[ list[n] ][b],"") != 0)						
							{
							//cout<<b<<" haha "<<tokens[b]<<endl;
							first(f,tokenized[ list[n] ][b]);
							h=0;
							while(first_table[f][h] != '\0'){
								if(first_table[f][h+1] == '\0'){break;}
								else if(first_table[f][h+2] == '\0'){break;}

								if( (first_table[f][h] == 'e') && (first_table[f][h+1] == 'p') &&(first_table[f][h+2]== 's') )
									{
								if(strcmp(tokenized[ list[n] ][b+1],"") != 0){
									//cout<<b<<"haha"<<endl;
									if(first_table[f][h+3] != ',')
										{first_table[f][h]=first_table[f][h+1]=first_table[f][h+2]='\0';}
									else
										{
										if(first_table[f][h+4] != '\0')
											first_table[f][h]=first_table[f][h+4];
										else					
											first_table[f][h]='\0';				
	
										if(first_table[f][h+5] != '\0')
											first_table[f][h+1]=first_table[f][h+5];
										else					
											first_table[f][h+1]='\0';				

										if(first_table[f][h+6] != '\0')
											first_table[f][h+2]=first_table[f][h+6];
										else					
											first_table[f][h+2]='\0';				

										}
										}
									b++;i=0;
									//cout<<b<<"haha"<<endl;
									goto again1;								
									}
								h++;
								}
							}
							break;
						}
					
					else if( (strcmp("eps",tokenized[ list[n] ][b])) == 0 )
						{
						strcpy(temp,",");
						strcat(temp,tokenized[ list[n] ][b]);				
						strcat(first_table_rhs[f],temp);
						strcat(first_table[f],temp);
						//cout<<j<<endl;
						//table[f][i] = (list[n]);
						break;				
						}
				
					}
				}
			}	
		

		int g=0,s=0,v=0;
		while(non_term[g][0] != '\0')
				{
				strcpy(first_table_rhs[g],"");			
				char *u = strtok(first_table[g], ",");
		
				int y=0;		
				while (u != NULL)
				{
					//cout<<u<<endl;
					strcpy(tokens[y],u);
					/*if(y!=0)				
						strcpy(tokenized_follow_rhs[g][y-1],tokens[y]);*/
					
					u = strtok(NULL, ",");
					/*if(y==0)
						continue;*/
					y++;
					}
				//cout<<y<<endl;			
				strcpy(first_table[g],tokens[0]);			
				for(s=0;s<y;s++)
				for(v=s+1;v<y;v++)
					if( strcmp(tokens[s],tokens[v]) == 0 )
						strcpy(tokens[v],"");
			
				for(s=1;s<y;s++)
					{
					if ( strcmp(tokens[s],"") != 0 )
						{
						strcpy(temp,",");					
						strcat(temp,tokens[s]);
						strcpy(tokenized_first_rhs[g][s-1],tokens[s]);
						strcat(first_table_rhs[g],temp);		
						strcat(first_table[g],temp);
						}
					}				
				g++;
				}
		
	}


void follow(int f, char *nt)
	{
		char tokens[10][100];	
		char temp[50];	
		int list[10];	
		int j=0; int o=0; int d=0; int m=0; int e=0; int l=0; int c=0,h=0,b=1;
				
		
		if(strcmp(start,nt) == 0)
			{
			strcpy(temp,",");
			strcat(temp,"$");	
			//strcat(follow_table_rhs[f],temp);
			strcat(follow_table[f],temp);
			}
		
		while(productions_rhs[j][0] != '\0' )
			{
			
			/*int len = strlen (productions_rhs[j]);
			//cout<<len<<"haha"<<endl;
			while(productions_rhs[j][m] != '\0')
				{
				while( (productions_rhs[j][m] != ' ') && (productions_rhs[j][m] != '\0') )			
					{
					tokens[l][c]=productions_rhs[j][m];
					m++;c++;
					}
				tokens[l][c]='\0';
				//cout<<tokens[l]<<endl;
				l++;c=0;
				//if( m < len )
					m++;				
				}

			/*char *u = strtok(productions_rhs[j], " ");
		
			int l=0;		
			while (u != NULL)
				{
				cout<<u<<endl;
				strcpy(tokens[l],u);
				u = strtok(NULL, " ");
				l++;
				}*/
			l=0;			
			while( (tokenized[j][l][0]) != '\0')			
				{
				strcpy(tokens[l],tokenized[j][l]);			
				l++;
				}

			b=1;
			for(d=0;d<l;d++)
				{
				if (strcmp(tokens[d],nt) == 0)
					{
					again3:					
					if( (d+b) != l)
						{
						for(e=0;e<10;e++)
							{
												
						if(strcmp(tokens[d+b],"") != 0)						
							{
							if( (strcmp(non_term[e],tokens[d+b])) == 0 )
											// 'e' gives the index of 'tokens[d+b]' in the table 'non_term' 
								{
								strcpy(temp,"");
								strcat(temp,first_table_rhs[e]);
								//strcat(follow_table_rhs[f],temp);
								strcat(follow_table[f],temp);

							h=0;
							while(follow_table[f][h] != '\0'){
								if(follow_table[f][h+1] == '\0'){break;}
								else if(follow_table[f][h+2] == '\0'){break;}

								if( (follow_table[f][h] == 'e') && (follow_table[f][h+1] == 'p') &&(follow_table[f][h+2]== 's') )
									{
									if(follow_table[f][h+3] != ',')
										{follow_table[f][h]=follow_table[f][h+1]=follow_table[f][h+2]='\0';}
									else
									{
										if(follow_table[f][h+4] != '\0')
											follow_table[f][h]=follow_table[f][h+4];
										else					
											follow_table[f][h]='\0';				
		
										if(follow_table[f][h+5] != '\0')
											follow_table[f][h+1]=follow_table[f][h+5];
										else					
											follow_table[f][h+1]='\0';				

										if(follow_table[f][h+6] != '\0')
											follow_table[f][h+2]=follow_table[f][h+6];
										else					
											follow_table[f][h+2]='\0';				
								
									}
										b++;
										goto again3;								
									}
								h++;
								}

								break;
								}

							else if( (strcmp(term[e],tokens[d+b])) == 0 )
											// 'e' gives the index of 'tokens[d+b]' in the table 'term' 
								{
								strcpy(temp,",");
								strcat(temp,term[e]);
								//cout<<temp<<endl;
								//strcat(follow_table_rhs[f],temp);
								strcat(follow_table[f],temp);
								break;
								}
							}
							
							}
						}
					else
						{
						if( strcmp(productions_lhs[j],tokens[d]) != 0 )						
							follow(f,productions_lhs[j]);
						}
					}
				}
			j++;
			}

										//removing duplicates in "follow_table"
		int g=0,s=0,v=0;
		while(non_term[g][0] != '\0')
			{
			strcpy(follow_table_rhs[g],"");			
			char *u = strtok(follow_table[g], ",");
		
			int y=0;		
			while (u != NULL)
				{
				//cout<<u<<endl;
				strcpy(tokens[y],u);
				/*if(y!=0)				
					strcpy(tokenized_follow_rhs[g][y-1],tokens[y]);*/
				
				u = strtok(NULL, ",");
				/*if(y==0)
					continue;*/
				y++;
				}
			//cout<<y<<endl;			
			strcpy(follow_table[g],tokens[0]);			
			for(s=0;s<y;s++)
				for(v=s+1;v<y;v++)
					if( strcmp(tokens[s],tokens[v]) == 0 )
						strcpy(tokens[v],"");
			
			for(s=1;s<y;s++)
				{
				if ( strcmp(tokens[s],"") != 0 )
					{
					strcpy(temp,",");					
					strcat(temp,tokens[s]);
					strcpy(tokenized_follow_rhs[g][s-1],tokens[s]);
					strcat(follow_table_rhs[g],temp);		
					strcat(follow_table[g],temp);
					}
				}				
			g++;
			}
			
		/*g=0;s=0;v=0;
		while(non_term[g][0] != '\0')
			{
			char *u = strtok(follow_table_rhs[g], ",");
		
			int y=0;		
			while (u != NULL)
				{
				//cout<<u<<endl;
				strcpy(tokens[y],u);
				u = strtok(NULL, ",");
				y++;
				}
			//cout<<y<<endl;			
			//strcpy(follow_table_rhs[g],tokens[0]);			
			for(s=0;s<y;s++)
				for(v=s+1;v<y;v++)
					if( strcmp(tokens[s],tokens[v]) == 0 )
						strcpy(tokens[v],"");
			
			for(s=1;s<y;s++)
				{
				if ( strcmp(tokens[s],"") != 0 )
					{
					strcpy(temp,",");					
					strcat(temp,tokens[s]);
					strcat(follow_table_rhs[f],temp);				
					//strcat(follow_table[g],temp);
					}
				}				
			g++;
			}*/
				


	}


void create_table()		
	{
		int q,w,h,m,r,z,k,flag=1;		
		char nt[10],t[10],temp[50];		
		/*for(q=0;q<10;q++)
			ll1_table[0][q] = q;

		for(q=0;q<10;q++)
			ll1_table[q][0] = q;*/
		
		for(r=0;r<10;r++)
			{
			strcpy(nt,non_term[r]);		
			for(q=0;q<10;q++)
				{
				flag=1;
				strcpy(t,term[q]);
				//cout<<t<<endl;
				//strcpy(nt,non_term[q]);
				int u=0,p=0;				
				w=0;			
				while( (tokenized_first_rhs[r][w][0]) != '\0' )			
					{
					if ( strcmp(tokenized_first_rhs[r][w],t) == 0 )
						{
						h=0;						
						while(productions_lhs[h][0] != '\0')							
							{
							if ( strcmp(non_term[r],productions_lhs[h]) == 0 )
								{
							again2:							
							if ( tokenized[h][u][0] != '\0')
								{
								strcpy(temp,tokenized[h][u]);
								//cout<<temp<<endl;
								m=0;
								while( (non_term[m][0]) != '\0')
									{
									if( strcmp(non_term[m],temp) == 0)
										{break;}
									m++;
									}
								//cout<<m<<endl;
								z=0;
								while( (tokenized_first_rhs[m][z][0]) != '\0' )			
									{
									//cout<<t<<endl;
									if ( strcmp(tokenized_first_rhs[m][z],t) == 0 )
										{
										//cout<<r<<" "<<q<<endl;
										//cout<<h<<endl;
										ll1_table[r][q]=h;
										(error_table[r][q])--;//=flag--;
										break;
										}
									z++;
									}
								//cout<<z<<endl;

								k=0;
								while( (term[k][0]) != '\0')
									{
									if( strcmp(term[k],temp) == 0)
										{break;}
									k++;
									}
								if( strcmp(temp,t) == 0 )
									{
									ll1_table[r][q]=h;
									(error_table[r][q])--;//=flag--;
									}	
								//break;
								p=0;
								while( (tokenized_first_rhs[m][p][0]) != '\0' )			
									{
									//cout<<t<<endl;
									if ( strcmp(tokenized_first_rhs[m][p],"eps") == 0 )
										{
										//cout<<r<<" "<<q<<endl;
										//cout<<h<<endl;							
										//ll1_table[r][q]=h;
										//error_table[r][q]=flag--;
										u++;
										goto again2;
										break;
										}
									p++;
									}
								}

								}
							h++;
							}
						//cout<<h<<endl;						
						break;
						}
					w++;	
					}

				
				//cout<<w<<endl;
				}

				int jk=0,e=0,sk=0,xz=0,bit=0,gk=0,pk=0;
				w=0;			
				while( (tokenized_first_rhs[r][w][0]) != '\0' )			
					{
					if ( strcmp(tokenized_first_rhs[r][w],"eps") == 0 )
						{
						h=0;						
						while(productions_lhs[h][0] != '\0')							
							{
							if ( strcmp(non_term[r],productions_lhs[h]) == 0 )
								{
								strcpy(temp,tokenized[h][0]);
								if ( strcmp(temp,"eps") == 0 )
									{
									jk=0;
									while(tokenized_follow_rhs[r][jk][0] != '\0')
										{
										for(e=0;e<10;e++)
											{	
											if( (strcmp(term[e],tokenized_follow_rhs[r][jk])) == 0 )
												{ll1_table[r][e]=h;
												(error_table[r][e])--;
												/*if( strcmp(non_term[r],"E'") == 0 )
													cout<<error_table[r][e]<<endl;*/	
												break;}
											}
										jk++;
										}
									}
								else
									{
									sk=0;
									while(tokenized[h][sk][0] != '\0') //&& (strcmp()
										{
										for(xz=0;xz<10;xz++)
											{	
											if( (strcmp(non_term[xz],tokenized[h][sk])) == 0 )
												{
												gk=0;
												while(tokenized_first_rhs[xz][gk][0] != '\0')
													{
													if( strcmp(tokenized_first_rhs[xz][gk],"eps") ==0 )
														{bit+=1;break;}
													gk++;
													}
												break;
												}
											}
										sk++;
										}

									if(bit==sk)
										{
										pk=0;
										while(tokenized_follow_rhs[r][pk][0] != '\0')
											{
											for(e=0;e<10;e++)
												{	
												if( (strcmp(term[e],tokenized_follow_rhs[r][pk])) == 0 )
													{ll1_table[r][e]=h;
													(error_table[r][e])--;break;}
												}
											pk++;
											}
										}
										//ll1_table[r][e]=h;
										//(error_table[r][e])--;break;}
									
									}


								}
							h++;
							}
						}
					w++;
					}	
										
							/*again2:							
							if ( tokenized[h][u][0] != '\0')
								{
								strcpy(temp,tokenized[h][u]);*/
			//cout<<q<<endl;
			}
	}

void tokenize(char* delim)
	{
	int l=0,h=0,b=0,n=0;
	char *u;
	n=0;
	while(productions_rhs[n][0] != '\0')
		{
		u = strtok(productions_rhs[n],delim );

		l=0;				
		while (u != NULL)
			{
			//cout<<u<<endl;
			//strcpy(tokens[l],u);
			strcpy(tokenized[n][l],u);
			//cout<<tokenized[list[n]][l]<<endl;
			u = strtok(NULL, delim);
			l++;
			}

		n++;
		}


	//strcpy(tokens[l],"");
	/*char *u = strtok(productions_rhs[list[n]], " ");
		
			int l=0,h=0,b=0;		
			while (u != NULL)
				{
				//cout<<u<<endl;
				strcpy(tokens[l],u);
				strcpy(tokenized[list[n]][l],u);
				//cout<<tokenized[list[n]][l]<<endl;
				u = strtok(NULL, " ");
				l++;
				}
			strcpy(tokens[l],"");*/
	}


void left_recursion()
	{
		cout<<endl<<endl<<"--------LEFT FACTORING ELIMINATED and LEFT RECURSION ELIMINATED:---------"<<endl<<endl;
		char str[10],st[50],temp3[50];
		strcpy(str," ");
		tokenize(str);
		int h=0,y=0,w=0,v=0;
		char temp[50],temp2[50];
		int g=0;		
		while(productions_rhs[g][0] != '\0')		
			{g++;}

		int nt=0;
		while(non_term[nt][0] != '\0')		
			{nt++;}		
		h=0;
		while(productions_rhs[h][0] != '\0')
			{
			strcpy(st,productions_lhs[h]);			
			if ( strcmp(tokenized[h][0],productions_lhs[h]) == 0 )
				{
				//cout<<productions_lhs[h]<<"hahah"<<endl;
				w=0;				
				while(productions_rhs[w][0] != '\0')
					{
					//cout<<w<<endl;
					//cout<<productions_lhs[w]<<"hahah"<<endl;
					//cout<<"ahah "<<w<<productions_lhs[w]<<st<<endl;
					//cout<<strcmp(st,productions_lhs[w])<<"haha"<<endl;
					if( strcmp(st,productions_lhs[w]) == 0 )
						{
						//cout<<h<<endl;
						//cout<<productions_lhs[w]<<"haha"<<endl;
						//cout<<"haha"<<w<<tokenized[w][0]<<productions_lhs[w]<<endl;
						//cout<<strcmp(tokenized[w][0],productions_lhs[w])<<endl;
						if ( strcmp(tokenized[w][0],productions_lhs[w]) != 0 )
							{
							strcpy(temp3,"");
							strcat(temp3,st);							
							strcat(temp3,"'");
							strcpy(temp2,"");
							strcat(temp2," ");							
							strcat(temp2,productions_lhs[w]);							
							strcat(temp2,"'");
							strcpy(temp,productions_rhs[w]);
							strcat(temp,temp2);
							strcpy(productions_rhs[w],temp);
							
							nt=0;
							while(non_term[nt][0] != '\0')		
								{nt++;}	
							v=0;							
							while(non_term[v][0] != '\0')
								{
								if( strcmp(non_term[v],temp3) == 0 )
									break;
								v++;
								}
							if(v==nt)
								{
								strcpy(non_term[nt],temp3);
								non_term[nt+1][0]='\0';
								}
							//cout<<temp<<endl;
							//cout<<productions_rhs[0]<<endl;
							}
						else if ( strcmp(tokenized[w][0],productions_lhs[w]) == 0 )
							{
							y=1;strcpy(temp,"");
							while( tokenized[h][y][0] != '\0' )							
								{
								strcat(temp,tokenized[h][y]);
								strcat(temp," ");
								y++;
								}
							//strcpy(temp2," ");							
							strcpy(temp2,productions_lhs[h]);							
							strcat(temp2,"'");							

							strcat(temp,temp2);							
							strcpy(productions_rhs[w],temp);
							strcpy(productions_lhs[w],temp2);
							strcpy(temp3,"");
							strcat(temp3,st);							
							strcat(temp3,"'");

							nt=0;
							while(non_term[nt][0] != '\0')		
								{nt++;}	

							v=0;							
							while(non_term[v][0] != '\0')
								{
								if( strcmp(non_term[v],temp3) == 0 )
									break;
								v++;
								}
							if(v==nt)
								{
								strcpy(non_term[nt],temp3);
								non_term[nt+1][0]='\0';
								}
							//cout<<productions_lhs[w];
							//cout<<productions_rhs[w];
							}
						}
					w++;
					}
				strcpy(temp3,"");
				strcat(temp3,st);							
				strcat(temp3,"'");
				g=0;				
				while(productions_rhs[g][0] != '\0')		
					{g++;}
				strcpy(productions_rhs[g],"eps");productions_rhs[g+1][0]='\0';
				strcpy(productions_lhs[g],temp3);productions_lhs[g+1][0]='\0';
				}
			h++;
			}
		//cout<<h<<endl;

	//char str[10];
	strcpy(str," ");
	tokenize(str);
	}


void check_ll1()
	{
	int h=0,w=0,l1=0,l2=0;
		for(h=0; h<10;h++)
			{
			for(w=0;w<10;w++)			
				{
				repeat:				
				if(error_table[h][w]== -1)
					{
					l1=0;
					while(tokenized[h][l1][0] != '\0')
						{
						l2=l1+1;
						while(tokenized[h][l2][0] != '\0')
							{
							if (strcmp(tokenized[h][l1],tokenized[h][l2]) == 0)		
								{w++;ambig_flag+=1;goto repeat;}
							l2++;
							}
						l1++;
						}
					flag+=1;			
					cout<<"REDUCE/REDUCE CONFLICT for ("<<non_term[h]<<","<<term[w]<<")"<<"\t\t";  
					cout<<"Reporting Error at Entry ("<<h<<","<<w<<") of LL1 table"<<endl;
					}
				}
			}

	if(ambig_flag>0)
		cout<<endl<<endl<<endl<<"---------------The Grammar has AMBIGUITY---------------"<<endl;

	if(flag==0)
		{
		cout<<                  "--------------The Grammar is LL1--------------"<<endl;
		cout<<endl<<endl<<endl<<"--------------Proceeding Further--------------"<<endl;
		cout<<endl<<endl<<"-------ERROR TABLE:---------"<<endl;
		h=0;
		while(non_term[h][0] != '\0')
			{
			w=0;
			while(term[w][0] != '\0')
				{cout<<error_table[h][w]<<"\t  ";w++;}
			cout<<endl;
			h++;
			}
		}
	else
		{
		cout<<endl<<endl<<endl<<"---------------The Grammar is NOT LL1---------------"<<endl;
		cout<<endl<<endl<<endl<<"---------------Not Proceeding Further---------------";
		cout<<endl<<endl<<endl<<"-------Printing the ERROR TABLE and LL1 TABLE for reference---------"<<endl;
		cout<<endl<<endl<<"------ERROR TABLE:--------"<<endl;
		h=0;
		while(non_term[h][0] != '\0')
			{
			w=0;
			while(term[w][0] != '\0')
				{cout<<error_table[h][w]<<"\t  ";w++;}
			cout<<endl;
			h++;
			}
		//exit(1);
		}
		//strcpy(tokenized[h][w],"");
	}

void tokenize_input(char* str,char* delim)
	{
	int l=0,h=0,b=0,n=0;
	char *u;
	n=0;
	while(str[n] != '\0')
		{
		u = strtok(str,delim );

		l=0;				
		while (u != NULL)
			{
			//cout<<u<<endl;
			//strcpy(tokens[l],u);
			strcpy(tokenized_input[l],u);
			//cout<<tokenized[list[n]][l]<<endl;
			u = strtok(NULL, delim);
			l++;
			}

		n++;
		}


	//strcpy(tokens[l],"");
	/*char *u = strtok(productions_rhs[list[n]], " ");
		
			int l=0,h=0,b=0;		
			while (u != NULL)
				{
				//cout<<u<<endl;
				strcpy(tokens[l],u);
				strcpy(tokenized[list[n]][l],u);
				//cout<<tokenized[list[n]][l]<<endl;
				u = strtok(NULL, " ");
				l++;
				}
			strcpy(tokens[l],"");*/
	}

void put_eps_in_all_or_not(int bit)
	{
	char str[10];
	int b=0;
	if(bit==0)	
		{
		cout<<endl<<"------------WIHOUT putting EPSILON in FIRST SET of all the Non-Terminals---------------"<<endl<<endl;
		cout<<endl<<"---------FIRST values:-----------"<<endl;
		b=0;
		while(non_term[b][0] != '\0')
			{
			strcpy(str,non_term[b]);			
			strcpy(first_table[b],str);
			strcat(first_table[b],":\t");			
			first(b,str);							//calling the function 'first'
			cout<<first_table[b]<<endl;
			b++;		
			}
		}

	else 
		{
		cout<<endl<<"------------PUTTING EPSILON in FIRST SET of all the Non-Terminals-------------"<<endl<<endl;
		cout<<endl<<"--------FIRST values:----------"<<endl;
		b=0;
		while(non_term[b][0] != '\0')
			{
			strcpy(str,non_term[b]);			
			strcpy(first_table[b],str);
			strcat(first_table[b],":\t");
			strcat(first_table[b],",eps");
			first(b,str);							//calling the function 'first'
			cout<<first_table[b]<<endl;
			b++;		
			}
		}
	}
	
void parsing(char *input)
	{

	cout<<endl<<endl<<endl<<"-----------PARSING-------------"<<endl<<endl<<endl;
	int i=0,g=0,q=0,l=0,l1=0,l2=0,xz=0;
	string str=" ",temp,dollar="$";
	char *str_ch,*temp_ch;
	str_ch	= &str[0];
	temp_ch = &temp[0];
	//strcpy(str," ");
	strcat(input," $");	
	tokenize_input(input,str_ch);
	/*int n=0;	
	while(tokenized_input[n][0] != '\0')
		{
		cout<<tokenized_input[n]<<"; ";
		n++;
		}*/

	stack<string> stck;
	stck.push(dollar);
	//cout<<stck.top()<<endl;	
	stck.push(start);
	
	//cout<<stck.top()<<endl;
	xz=0;l=0;	
	while( stck.top() != dollar)
		{
		if( stck.top() == tokenized_input[l] )
			{stck.pop();cout<<"Match "<<tokenized_input[l]<<endl;xz++;l++;}
		else 
			{
			//q=0;
			//while( term[q][0] != '\0' )
			for(q=0;q<10;q++)			
				{
				if ( term[q] == stck.top() )
					{cout<<endl<<endl<<endl<<"-----------------ERROR at STACK LEVEL "<<(xz+1)<<"--------------------"<<endl<<endl<<endl;
					cout<<endl<<endl<<endl<<"-----------------INPUT REJECTED--------------------"<<endl<<endl<<endl;
					exit(2);}
				}
			
			for(i=0;i<10;i++)
				{
				if( strcmp( term[i],tokenized_input[l]) == 0 )
					break;
				}

			for(g=0;g<10;g++)
				{
				if( non_term[g] == stck.top() )
					break;
				}
			//cout<<g<<" hahah "<<i<<endl;

			if ( ll1_table[g][i] < 0 )
				{cout<<endl<<endl<<endl<<"-----------------ERROR at STACK LEVEL "<<(xz+1)<<"--------------------"<<endl<<endl<<endl;
				 cout<<endl<<endl<<endl<<"-----------------INPUT REJECTED--------------------"<<endl<<endl<<endl;
				exit(3);}

			cout<<productions_lhs[ ll1_table[g][i] ]<<" -> ";
			l1=0;
			while( strcmp(tokenized[ ll1_table[g][i] ][l1],"") != 0)
						{cout<<tokenized[ ll1_table[g][i] ][l1]<<" ";l1++;}
			cout<<endl;			
			
			stck.pop();
			
			//cout<<l1;
			
			
			for(l2=l1-1 ; l2 > -1 ; (l2)--)
				{
				if( strcmp(tokenized[ ll1_table[g][i] ][l2],"eps") != 0 )				
					stck.push(tokenized[ ll1_table[g][i] ][l2]);
				}
			xz++;	
			}
		}

	cout<<endl<<endl<<endl<<"-----------------INPUT ACCEPTED--------------------"<<endl<<endl<<endl;
				
	//while()
	//cout<<stck.top();
	
	//stack(stck);
	}
	
		
			







