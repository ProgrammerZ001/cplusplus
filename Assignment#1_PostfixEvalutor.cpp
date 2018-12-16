#include<iostream>
#include<string>
#include<sstream>
#include <map>
using namespace std;

struct valuenode{
	double value;
	valuenode *next;
};

class Resultstack
{
     
	public:
    valuenode *Val_TOP;
    Resultstack() // constructor
    {
        Val_TOP=NULL;
    }
    void push(double a); // to insert an element
    double pop();  // to delete an element
};
// PUSH Operation
void Resultstack::push(double a)
{
	valuenode *ptr;
    ptr=new valuenode;
    ptr->next=Val_TOP;
    Val_TOP=ptr;
	Val_TOP->value=a;
}

// POP Operation
double Resultstack::pop()
{
    struct valuenode *temp;
    if(Val_TOP==NULL)
    {
        cout<<"\nThe stack is empty!!!";
    }
    temp=Val_TOP;
    double b=Val_TOP->value;
    Val_TOP=Val_TOP->next;
    
    delete temp;
    return b;
}

//   Creating a NODE Structure
struct node
{
    char data;
    struct node *next;
};
// Creating a class STACK
class stack
{
     
	public:
    struct node *top;
    stack() // constructor
    {
        top=NULL;
    }
    char push(char a); // to insert an element
    char pop();  // to delete an element
    void show(); // to show the stack
};
// PUSH Operation
char stack::push(char a)
{
	node *ptr;
    ptr=new node;
    ptr->next=top;
    top=ptr;
	top->data=a;
}

// POP Operation
char stack::pop()
{
    struct node *temp;
    if(top==NULL)
    {
        cout<<"\nThe stack is empty!!!";
    }
    temp=top;
    char b=top->data;
    top=top->next;
    
    delete temp;
    return b;
}

// Show stack
void stack::show()
{
    struct node *ptr1=top;
    do
    {
        cout<<ptr1->data;
        ptr1=ptr1->next;
    }while(ptr1!=NULL);
    cout<<endl;
}

bool precedence(char a, char b)
    {
    	if((a=='-'||a=='+'||a=='*'||a=='/')&&(b=='('||b=='{'||b=='['))
    		return true;
		else if((a=='/'||a=='*')&&(b=='/'||b=='*'))
			return false;
    	else if((a=='-'||a=='+')&&(b=='+'||b=='-'||b=='/'||b=='*'))
    		return false;
    	return true;
	};

int main(){
	map<char, double> variable_map;
	double var_input, var1, var2, result;
	char var_char; 
	int bracesup=0,bracesdown=0,optr=0,opnd=0;
	stack postequ;
	Resultstack RSTAK;
	string equation, output;
	char a='l';
	int strchck;
	cout<<"Enter your equation ";
	getline(cin,equation);
	for(int i=0; equation[i]!='\0'; i++){
		
		if(equation[i]=='('||equation[i]=='{'||equation[i]=='['||equation[i]=='/'||equation[i]=='*'||equation[i]=='+'||equation[i]=='-'||equation[i]=='^')
		{	
			if(equation[i]=='['||equation[i]=='{'||equation[i]=='('){
				bracesup++;
				postequ.push(equation[i]);
			}
			else if(equation[i]=='/'||equation[i]=='*'||equation[i]=='+'||equation[i]=='-'||equation[i]=='^'){
				optr++;
				if(postequ.top==NULL){
					postequ.push(equation[i]);
				}
				else{
					bool check=precedence(equation[i],postequ.top->data);
					while(check!=true){
						char y=postequ.pop();
						output+=y;
						if(postequ.top==NULL)
							break;
						check=precedence(equation[i],postequ.top->data);
					}
					postequ.push(equation[i]);
				}
			}
		}
		else if(equation[i]==')'||equation[i]=='}'||equation[i]==']'){
			bracesdown++;
			do{
				if(postequ.top==NULL){
					cout<<"!!!...Check the validity of your equation."<<endl;
					exit(0);
				}
				a=postequ.pop();
				if(a=='l'||a=='['||a=='{'||a=='('){
					break;
				}
				else{
					output+=a;
				}
			}while(a!='['||'{'||'(');
			
			if(!((a=='('&&equation[i]==')')||(a=='{'&&equation[i]=='}')||(a=='['&&equation[i]==']')))
			{
				cout<<".!!!...Check the validity of your equation."<<endl;
				exit(0);
			}
		}
		strchck=(int)equation[i];
		if(strchck>47&&strchck<58||strchck>64&&strchck<91||strchck>96&&strchck<123){
			opnd++;
			output+=equation[i];
		}
		a='l';
	}
	if(postequ.top!=NULL){
		while(postequ.top!=NULL){
			a=postequ.pop();
			output+=a;
		}
	}
	if((bracesup==bracesdown)&&(optr==(opnd-1))){
		cout<<"\nYour equation is balanced."<<endl;
		for(int i=0; output[i]!='\0'; i++){
		strchck=(int)output[i];
		if(strchck>96&&strchck<123){
			if(variable_map.count(output[i])>0)
				{
				}
			else{
				cout<<"Enter the value of "<<output[i]<<" : ";
				cin>>var_input;
				variable_map[output[i]]=var_input;
			}
		}else if(strchck>64&&strchck<91)
		{
			cout<<"You enterred the capital variables "<<output[i]<<" but don't worry\n variables names aren't case sensitive'"<<endl;
			var_char=(char)(strchck+32);
			output[i]=var_char;
			if(variable_map.count(var_char)>0)
				{
				}
			else{
				cout<<"the value of "<<var_char<<" : ";
				cin>>var_input;
				variable_map[var_char]=var_input;
			}
		}}
		cout<<endl<<"Postfix of your equation is : "<<output<<endl;
		
	}
	else{
		cout<<"..!!!...Check the validity of your equation."<<endl;
		exit(0);
		
	}
	for(int i=0; output[i]!='\0'; i++){
		strchck=(int)output[i];
		if(strchck>96&&strchck<123){
			RSTAK.push(variable_map[output[i]]);
		}
		else if(strchck>48&&strchck<58){
			double constant=strchck-48;
			RSTAK.push(constant);
		}
		else if(output[i]=='/'||output[i]=='*'||output[i]=='+'||output[i]=='-'){
			double pop1=RSTAK.pop();
			var2=(double)pop1;
			double pop2=RSTAK.pop();
			var1=(double)pop2;
			cout<<var1<<output[i]<<var2<<" = ";
			switch(output[i]){
				case '/':
					result=var1/var2;
					RSTAK.push(result);
					break;
				case '*':
					result=var1*var2;
					RSTAK.push(result);
					break;
				case '+':
					result=var1+var2;
					RSTAK.push(result);
					break;
				case '-':
					result=var1-var2;
					RSTAK.push(result);
					break;
			}
			cout<<result<<endl;
		}
	}
	cout<<output<<" = "<<result;
}

