/* comments dictionary:
|                                  |
|(f) --> The function of this line |
|__________________________________|
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXSIZE 256
//stack and basic functions
struct cStack
{
	char* arr;
	int sp;
	int size;
	//Constructor (from C++)
	cStack()
	{
		arr = NULL;
		sp = -1;
		size = 0;
	}
};
struct fStack
{
	float* arr;
	int sp;
	int size;
	//Constructor (from C++)
	fStack()
	{
		arr = NULL;
		sp = -1;
		size = 0;
	}
};
bool cinitializeStack(cStack *c, int sz)
{
	if (c->arr != NULL) //In case previous malloc is called
		free(c->arr);
	c->arr = (char*)malloc(sizeof(char) * sz);
	if (c->arr == NULL)
		return false;
	c->size = sz;
	c->sp = -1;
	return true;
} 
int cisempty(cStack *c)
{
	if(c->sp!=-1) return -1;//Stack NOT empty
	if(c->arr==NULL) return -2;//Stack not initialized !
	return 1;//Stack is empty
}
int cpush(cStack *c, char citem)
{
	if (c->arr == NULL)
		return -1;	//Stack not initialized !
	if (c->sp + 1 == c->size)
		return -2;	//Stack overflow !
	c->sp = c->sp + 1;	//or c->sp++;
	c->arr[c->sp] = citem;
	return 1;
}
int cpop(cStack* c, char* citem)
{
	if (c->arr == NULL)
		return -1;	//Stack not initialized !
	if (cisempty(c))
		return -2;	//Stack underflow !

	*citem = c->arr[c->sp];
	c->sp = c->sp - 1;	//c->sp--;
	return 1;
}
int ctop(cStack*c,char *ctemp)
{
	if(cisempty(c))return -1;// stack is empty
	if(c->arr==NULL)return -2; // stack not initialized
	*ctemp=c->arr[c->sp];
	return 1;
}
bool finitializeStack(fStack *f ,int sz)
{
	if (f->arr != NULL) //In case previous malloc is called
		free(f->arr);
	f->arr = (float*)malloc(sizeof(float) * sz);
	if (f->arr == NULL)
		return false;
	f->size = sz;
	f->sp = -1;
	return true;
} 
int fisempty(fStack *f)
{
	if(f->sp!=-1) return -1;//Stack NOT empty
	if(f->arr==NULL) return -2;//Stack not initialized !
	return 1;//Stack is empty
}
int fpush(fStack *f, float fitem)
{
	if (f->arr == NULL)
		return -1;	//Stack not initialized !
	if (f->sp + 1 == f->size)
		return -2;	//Stack overflow !
	f->sp = f->sp + 1;	//or f->sp++;
	f->arr[f->sp] = fitem;
	return 1;
}
int fpop(fStack* f, float* fitem)
{
	if (f->arr == NULL)
		return -1;	//Stack not initialized !
	if (f->sp == -1)
		return -2;	//Stack underflow !

	*fitem = f->arr[f->sp];
	f->sp = f->sp - 1;	//f->sp--;
	return 1;
}
int ftop(fStack*f,float *ftemp)
{
	if(f->sp==-1)return -1;// stack is empty
	if(f->arr==NULL)return -2; // stack not initialized
	*ftemp=f->arr[f->sp];
	return 1;
}
//From infix to postfix functions
int checkinftostack(char item)
{
	if(isdigit(item)) return 2;//if the item isdigit 
	else if(item=='*'||item=='/'||item=='+'||item=='-'||item=='^') return 3;//if the item is operator
    else if(item=='(') return 1;
    else if(item==')') return 4;
	return 0;	
}
int priority(char infex,char top)
{
	int copy=0, inf=0;
	if(infex=='^') inf=3;
	else if(infex=='*'|| infex=='/')inf=2;    // check  the stack priority of the operators
	else if(infex=='+' || infex=='-') inf=1;
    if(top=='^') copy=3;
	else if(top=='*'||top=='/')copy=2;
	else if(top=='+' || top=='-')copy=1;
	if(copy>=inf) return 0;
    return 1;
}
int inftopost(cStack c,char infex[],char post[],int sizeinf)
{
	char copy,delet='0';
	int i,per,counterpost=0,z;
	bool ans=cinitializeStack(&c,sizeinf);
		if(ans==true) // checking if the stack got intialized or no
		{
		   for(i=0;i<sizeinf;i++)
			{
				per=checkinftostack(infex[i]); // check which kind of character is going to enter the stack  <<<Except the alphapet characters are banned >>>>
				if(per==2) // The character is digit --> put in postfix string
					post[counterpost++]=infex[i];
				else if(per==3) // The character kind is operator
				{
					if(cisempty(&c)==-1) // the stack is not empty so check the priority
					{
						ctop(&c,&copy); // check the top operator in the stack for the priority
						z=priority(infex[i],copy);
						if(z==1) cpush(&c,infex[i]);  //The element's priority in the stack is lower than in the infex string
						else 
						{   
							cpop(&c,&delet);
							post[counterpost++]=delet;  // The element's priority in the stack is greater than in the infex string --> pop the element in the stack then push  the element in the stack from the infex
							cpush(&c,infex[i]);
						}
				
					}
					else cpush(&c,infex[i]); // if the stack is already empty--> push the element
				}
				else if(per==1) cpush(&c,infex[i]); // The element is <<< ( >>>  so push in the stack
				else if(per==4) // The element is <<< ) >>> 
				{
					if(cisempty(&c)==1){ printf("unbalanced brackets\n"); return 0;} // if the stack is empty while the element is <<< ) >>> so the brackets is not balanced
					while(ctop(&c,&copy)==1)  //(f)The loop will go over and over until there is no element in the stack --- (f2) check the top element
					{
						if(copy!='(')
						{
							cpop(&c,&delet);   // pop until the top element is <<< ( >>>
						   post[counterpost++]=delet;
						}
						else {cpop(&c,&delet); break;} // If the top element is <<< ( >>>  so pop it and exit the loop
					} 
					if(delet!='(') {printf("unbalanced brackets\n"); return 0;} // If last element poped not equal to <<< ( >>> so this means that there is no <<< ( >>> 
					if(per==4 && infex[i+1]=='(') cpush(&c,'*'); //If there is closed bracket then open bracket --> put between it <<< * >>>
				}
					else { printf("Invaled input!!!\n"); return 0;} // This means Alphabet character
			}
			while(ctop(&c,&copy)==1) // After the the whole infex loop is finished pop all the characters that still in the stack
			{
				if(copy=='(') {printf("bracket unbalanced \n"); return 0;} // (f) If there is <<< ( >>> in the stack after the loop of the ifex finished this this means that there was no <<< ) >>>
				else 
				{
					cpop(&c,&delet);
				    post[counterpost++]=delet;
				}
			}
		}
		else printf("Memory Error!!!\n"); // Stack is not intialized 
		post[counterpost]='\0';
		return 1;
}
//From postfix to evaluation
float eval(fStack *f,char *op){float A=0,B=0,y=0;int error=0;
	if(*op=='^'){
		if(fpop(f,&B)!=1) {printf("Error B");return -1;}
		 if(fpop(f,&A)!=1) {printf("Error A");return -2;}
		 y=pow(float(A),float(B));
		 if(fpush(f,y)!=1) printf("push error!!!");
		 //fpop(f-,&y2);printf("%f\n",y2);
	  }
	  else if(*op=='*'){
		  if(fpop(f,&B)!=1) {printf("Error B");return -1;}
		  if(fpop(f,&A)!=1) {printf("Error A");}
		  y=(float)A*B; if(fpush(f,y)!=1) printf("push error!!!");
		  //fpop(f,&y2);printf("%f\n",y2);
	  }
	  else if(*op=='/'){
		  if(fpop(f,&B)!=1) {printf("Error B");return -1;};
		  if(fpop(f,&A)!=1) {printf("Error A");return -2;}
		  y=(float)A/B; if(fpush(f,y)!=1) printf("push error!!!");
		  //fpop(f,&y2);printf("%f\n",y2);
	  }
	  else if(*op=='+'){
		  if(fpop(f,&B)!=1) {printf("Error B");return -1;}
		  if(fpop(f,&A)!=1) {printf("Error A");return -2;}
		  y=(float)A+B; if(fpush(f,y)!=1) printf("push error!!!");
		  printf("\n\nthis is +\n\n");
		  //fpop(f,&y);printf("%f\n",y);
	  }
	  else if(*op=='-'){
		  if(fpop(f,&B)!=1) {printf("Error B");return -1;}
	      if(fpop(f,&A)!=1) {printf("Error A");return -2;}
		  y=(float)A-B; if(fpush(f,y)!=1) printf("push error!!!");
		  //fpop(f,&y);printf("%f\n",y);
	  }
	  else {printf("\noperants error!!!\n");error=1;return 0;}
       //for(int k=0;k<sz;k++) printf("\n op:%c\t\n",op[k]);
	  //if(error==0){ans(f);return 1;}
}
float checkposttoans(fStack *f,char *item,int sz){
	int fdig=0,i=0,opnum=0; float out=0,y2=0; char x,*op=&x;
	bool ans=finitializeStack(f,sz);
	if (ans==true){
    for( i=0;i<sz;i++){
		if(isdigit(item[i])) //if the item isdigit
		{   
			fdig=item[i]-'0';
			fpush(f,fdig);
		}		
		else if(item[i]=='*'||item[i]=='/'||item[i]=='+'||item[i]=='-'||item[i]=='^')
		{*op=item[i];opnum++;eval(f,op);}
	  }//if if the item is operator
	printf("\nopnum=%d\n",opnum);
	printf("%c",*op);
	if(fpop(f,&y2)!=1) {printf("\npop error!!!!\n");return 0;}
	if(fisempty(f))return y2;
	else {printf("\nstack is not empty!!!!!\n");return 0;}
	}
	return 0;
  }

int main(void){
	cStack c; fStack f;
	char infex[500],post[MAXSIZE];
	int sizeinf,mn; float X=0;
	printf("Type your infex expression\t");
	gets(infex);
	sizeinf=strlen(infex);
	if(sizeinf>MAXSIZE){printf("\n\nInfiex is more than max size!!!!\n\n"); return 0;}
	mn=inftopost(c,infex,post,sizeinf);
	if(mn==1) {puts(post);X=checkposttoans(&f,post,strlen(post));}
	if(X!=0){printf("\n\nthe R=  %.2f\n\n",X);}
   return 0;
}