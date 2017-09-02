#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;
//string file_name;
int line_no = 0;
//vector<string> tokens;
vector<string> variables;
vector<string> keywords;
vector<string> datatypes;
vector<string> functions;
vector<string> brackets;
vector<string> operators;

stack<string> parenthesis;

//Functions USED

void abort(string message);
void createCPPfile();
void createLogFile();
void write(string data);
bool isvalid_number(string token);
string check_condition(vector<string> tokens);
void isvalid_brackets(vector<string> tokens);
void isvalid_if(vector<string> tokens);
void isvalid_while(vector<string> tokens);
void isvalid_elif(vector<string> tokens);
void isvalid_else(vector<string> tokens);
void isvalid_input(vector<string> s);
void isvalid_expression(vector<string> tokens);
void map_input(vector<string> s);
void map_print(vector<string> s);
void isvalid_print(vector<string> s);
void isvalid_declaration(vector<string> tokens);
void initialise();
bool isvalid_string(string s);
void isvalid_keyword(vector<string> tokens);
vector<string> tokenize(string data);
void isvalid_function(vector<string> vec);
void balanced(string s);
void push(string s);
bool isvalid_variable(string str);
bool isvalid_datatype(string str);
void log(string data);
void clrscreen(vector<string> vec);
void isvalid_return(vector<string> tokens);
void isvalid_function(vector<string> vec);
bool isvalid_operator(string s);
void isparenthesis_empty();
void is_init( vector<string> vec);
void isvalid_array_declaration(vector<string> tokens);
bool isvalid_functionpresent(vector<string> vec);
void func_call(vector<string> vec,int index);

int main(int argc,char const *argv[]){	
	cout<<"File : "<<argv[1]<<endl;
   initialise();
   ifstream infile;
   infile.open(argv[1]);
   if (!infile)
   {
       abort("Unable to open file");
   }

   while (!infile.eof())
   {
       char temp[500];
       infile.getline(temp, 1000);
       line_no++;
       string line(temp);
       vector<string> tokens;
       tokens = tokenize(line);
       /*for(int i=0;i<tokens.size();i++){
           cout<<tokens[i]<<endl;
        
        cout<<tokens.size()<<endl;*/
	if(line.find_first_not_of(' ') != std::string::npos)
{
 

       isvalid_keyword(tokens);
       //isvalid_datatype(tokens[0]);
       //isvalid_variable(tokens[0]);
       //isvalid_function(tokens);
      isvalid_brackets(tokens); 
   	}
	tokens.clear();
}
if(!parenthesis.empty())
	{
		abort("Parenthesis Unbalanced ");
	}

	cout<<"COMPILATION SUCCESSFUL!!!..."<<endl;
					
	cout<<"Calling g++ "<<endl;
	system("g++ tic.cpp");
	cout<<"g++ compilation successful "<<endl;
	cout<<"execution the game... "<<endl;
	system("a");

					

   infile.close();
   return 0;
}

void isparenthesis_empty()
{
   if (parenthesis.empty())
       abort("invalid global scope declaration");
}


void abort(string message)
{
   cout << "Error in line : " << line_no;
   cout << " ( " << message << " )" << endl;
   exit(0);
}

void createCPPfile(){
	ofstream outfile;
  	outfile.open("tic.cpp");
  	outfile <<"#include <iostream>"<<endl;
  	outfile <<"using namespace std;"<<endl; 
	outfile.close();
}
void createLogFile()
{
   ofstream outfile;
   outfile.open("log.txt");
   outfile << "\t\tFile : ["<<"tic.n"<<"]"<< endl;
   time_t rawtime;
   time (&rawtime);
   outfile << "\t\tTime : "<<ctime (&rawtime)<< endl;
   outfile.close();
}


void write(string data)
{
   ofstream outfile;
   outfile.open("tic.cpp", ios_base::app);
   outfile << data << endl;
   outfile.close();
}

bool isvalid_operator(string s)
{
   for (int i = 0; i < operators.size(); i++)
   {
       if (s.compare(operators[i]) == 0)
       {
        
           return true;
       }
   }
   return false;
}

bool isvalid_number(string token)
{
   for (int i = 0; i < token.size(); i++)
   {
       if (isdigit(token[i]))
           continue;
       else
       	return false; 
           //abort("invalid assignment");
   }
   return true;
}

string check_condition(vector<string> tokens)
{
   int flag, i = 0, index = 1;
   string str;
   if (tokens[index].compare("(") == 0)
       str += tokens[index];
   else
       abort("( expected");
   index++;
   while (tokens[index].compare(")") != 0)
   {
//   		cout<<tokens[index];
//		write(tokens[index]);
   		if(tokens[index][0] == '[')
   		{
//   			cout<<tokens[index];
//write(tokens[index]);
   			str = str + tokens[index] + " ";
   			index++;
   			continue;
		}
       flag = 0;
       if (i % 2 == 0)
       {
           if (isvalid_variable(tokens[index]) || isvalid_number(tokens[index]))
               flag = 1;
       }
       else
       {
           if (isvalid_operator(tokens[index]))
               flag = 2;
       }
       if (flag == 0)
           abort("error in check condition");
       str = str + " " + tokens[index];
       i++;
       index++;
   }
   if (flag != 1)
       abort("error in check condition");
   str += tokens[index];
   return str;
}


void isvalid_while(vector<string> tokens)
{
   if (tokens[tokens.size() - 1].compare("{") != 0)
       abort("missing {");
   string str = "while ";
   str = str + check_condition(tokens) + "{";
   write(str);
}

void isvalid_if(vector<string> tokens)
{
   if (tokens[tokens.size() - 1].compare("{") != 0)
       abort("missing {");
   string str = tokens[0];
   str = str + check_condition(tokens) + "{";
   write(str);
}

void isvalid_elif(vector<string> tokens)
{
   if (tokens[tokens.size() - 1].compare("{") != 0)
       abort("missing {");
   string str = "else if";
   str = str + check_condition(tokens) + "{";
   write(str);
}

void isvalid_else(vector<string> tokens)
{
   string s = "else";
   if (tokens[1].compare("{") == 0)
       s.append("{");
   else
       abort("parenthesis missing");
   write(s);
}

/******** Harsh ka code chalu ********/

// input statement validity check function starts
void isvalid_input(vector<string> s)
{
   int flag = 0;
   for (int i = 0; i < variables.size(); i++)
   {
       if (variables[i] == s[1])
       {
           flag++;
       }
   }
   if (flag != 0 && s.size() == 2)
   {
       map_input(s);
       return;
   }
   else
   {
       abort("Error in input statement");
       return;
   }
}
// input statement validity check function ends

// mapping function for input starts
void map_input(vector<string> s)
{
   string str = "";
   s[0]="cin";
   str = s[0] + " >> " + s[1] + " ;";
   write(str);
   return;
}
// mapping function for input ends

// mapping function for print output starts
void map_print(vector<string> s)
{
   string str = "";
   for (int i = 0; i < s.size(); i++)
   {
       if (s[i] == "+")
       {
           s[i] = "<<";
       }
       if (s[i] == "print")
       {
           s[i] = "cout <<";
       }
   }
   s.push_back(";");
   for (int i = 0; i < s.size(); i++)
   {
       if (s[i] == "(" || s[i] == ")")
       {
           continue;
       }
       str = str + s[i] + " ";
   }

   write(str);
   return;
}
// mapping function for print output ends

// print output statement validity check function starts
void isvalid_print(vector<string> s)
{
   int t = 0;
   int inverted = 0;
   int bracket = 0;

   for (int i = 0; i < s.size(); i++)
   {
       if (s[i] == "(")
       {
           bracket++;
       }
       else if (s[i] == ")")
       {
           bracket--;
       }
       if (s[i] == "\"" && t == 0)
       {
           inverted++;
           t = -1;
       }
       else if (s[i] == "\"" && t == -1)
       {
           inverted--;
           t = 0;
       }
   }

   if ( bracket == 0 && s[1] == "(" && s[s.size() - 1] == ")")
   {
       map_print(s);
   }
   else
   {
       abort("Error in print statement");
   }
}
// print output statement validity check function ends

/******** Harsh ka code khatam ********/

void isvalid_declaration(vector<string> tokens)
{
   if (tokens.size() > 4 || tokens.size() == 3 )
       abort("invalid variable declaration");
   string s = tokens[0];
   int flag = 0;
   if((tokens[1][0] >='A' && tokens[1][0] <='Z') || (tokens[1][0] >= 'a' && tokens[1][0] <= 'z')){
       for (int i = 0; i < variables.size(); i++)
       {
           if (tokens[1].compare(variables[i]) == 0)
               abort("variable already declared");
       }
       variables.push_back(tokens[1]);
   }
   s = s + " " + tokens[1];
   if(tokens.size() == 2)
   {
       s += " ;";
       write(s);
       return;
   }
   if(tokens[2].compare("=") != 0)
       abort("invalid assignment 2");
   else{
       if (tokens[1].compare("char") == 0)
       {
           if (tokens[3][0] != '\'' || tokens[3][tokens[3].size() - 1] != '\'')
               abort("invalid assignment for type char");
       }
       else if (tokens[1].compare("int") == 0)
           isvalid_number(tokens[3]);
   }
   s = s + " " + tokens[2] + " " + tokens[3] + " ;";
   write(s);
}

void isvalid_array_declaration(vector<string> tokens)
{
   int flag = 0, i = 0, index = 1;
   string str;
   if (tokens.size() > 6)
       abort("invalid array declaration");
   if (isvalid_datatype(tokens[1]))
       str += tokens[1];
   else
       abort("invalid name of datatype");
   index++;
   while (index < tokens.size())
   {
       if (index % 2 == 0)
       {
           if (tokens[index].compare(",") != 0)
               abort("invalid array declaration ',' expected");
       }
       if (index == 3)
       {
           if ((tokens[3][0] >= 'A' && tokens[3][0] <= 'Z') || (tokens[3][0] >= 'a' && tokens[3][0] <= 'z'))
           {
               for (int i = 0; i < variables.size(); i++)
               {
                   if (tokens[3].compare(variables[i]) == 0)
                       abort("variable already declared");
               }
               variables.push_back(tokens[3]);
               str = str + " " + tokens[index];
               flag = 1;
           }
           else
               abort("invalid array variable name");
       }
       if (index == 5)
       {
           if (isvalid_number(tokens[index]))
               str = str + "[" + tokens[index] + "]";
           else
               abort("invalid array size declaration");
       }
       index++;
   }
   if (flag != 1)
       abort("invalid array declaration");
   str = str + ";";
   write(str);
}


/*
void isvalid_expression(vector<string> tokens)
{
int flag, i = 0, index = 0, temp=0;
       string str = tokens[0];
    if(tokens[1][0] == '[')
    {
        str = str + tokens[1]; 
        temp = 1;
        index = 2;
    }

    while (index < tokens.size())
    {
        flag = 0;
        if (i % 2 == 0)
        {
            if (isvalid_variable(tokens[index]) || isvalid_number(tokens[index]))
                flag = 1;
        }
        else
        {
            if (isvalid_operator(tokens[index]))
                flag = 2;
        }
        if (flag == 0)
            abort("error in expression");
        str = str + " " + tokens[index];
        i++;
        index++;
    }
    str = str + ";";
    write(str);
}*/


void isvalid_keyword(vector<string> tokens)
{
   if (tokens[0].compare("if") == 0)
   {
       isparenthesis_empty();
       isvalid_if(tokens);
   }
   else if (tokens[0].compare("elif") == 0)
   {
       isparenthesis_empty();
       isvalid_elif(tokens);
   }
   else if (tokens[0].compare("while") == 0)
   {
       isparenthesis_empty();
       isvalid_while(tokens);
   }
   else if (tokens[0].compare("char") == 0)
       isvalid_declaration(tokens);
   else if (tokens[0].compare("int") == 0)
       isvalid_declaration(tokens);
   else if (tokens[0].compare("array") == 0)
       isvalid_array_declaration(tokens);
   else if (tokens[0].compare("def") == 0)
       isvalid_function(tokens);
   else if (tokens[0].compare("clear") == 0)
   {
       isparenthesis_empty();
       clrscreen(tokens);
   }
   else if (tokens[0].compare("return") == 0)
   {
       isparenthesis_empty();
       isvalid_return(tokens);
   }
   else if (tokens[0].compare("else") == 0)
   {
       isparenthesis_empty();
       isvalid_else(tokens);
   }
   else if (tokens[0].compare("print") == 0)
   {
       isparenthesis_empty();
       isvalid_print(tokens);
   }
   else if (tokens[0].compare("input") == 0)
   {
       isparenthesis_empty();
       isvalid_input(tokens);
   }
   else if (tokens[0].compare("_init_") == 0)
       is_init(tokens);
   else if (tokens[0].compare("}") == 0)
       return;
   else
   {
       isparenthesis_empty();
       isvalid_expression(tokens);
   }
}

void initialise()
{
   //file_name=”tic.n”;
   createLogFile();
   createCPPfile();
   keywords.push_back("_init_(");
   keywords.push_back("while");
   keywords.push_back("if");
   keywords.push_back("elif");
   keywords.push_back("print");
   keywords.push_back("else");
   keywords.push_back("input");
   keywords.push_back("clear");
   keywords.push_back("return");

   datatypes.push_back("char");
   datatypes.push_back("int");

   operators.push_back("==");
   operators.push_back("!=");
   operators.push_back("&&");
   operators.push_back("=");
   operators.push_back("+");
   operators.push_back("-");
   operators.push_back("*");
   operators.push_back("/");
   operators.push_back("%");
   operators.push_back(">");
   operators.push_back("<");
   operators.push_back(">=");
   operators.push_back("<=");
   operators.push_back("/");
   operators.push_back("%");
}

bool isvalid_string(string s)
{
   int c = 0;
   for (int i = 0; i < s.length(); i++)
   {
       if (s[i] == '"')
       {
           c++;
       }
   }
   if (c % 2 == 0)
       return true;
   else
       return false;
}

vector<string> tokenize(string data)
{
   if (!isvalid_string(data))
   {
       abort("Invalid string");
   }
   vector<string> tokens;
   stringstream ss(data); // Insert the string into a stream
   string buf;            // Have a buffer string
   while (ss >> buf)

       if (buf[0] == '"')
       {
           string temp = buf;
           while (buf[buf.length() - 1] != '"')
           {
               ss >> buf;
               temp = temp + " " + buf;
           }
           tokens.push_back(temp);
          
       }
       else
       {
           tokens.push_back(buf);
           //cout<<buf<<endl;
       }
   return tokens;
}



void isvalid_function(vector<string> vec)
{
   if (vec[0] != "def")
   {
       return;
   }
   if (!isvalid_datatype(vec[1]))
   {
       abort("Invalid Return Type");
   }

   string name = vec[2];
   int size = name.size() - name.find_first_of("(");
   name = name.substr(0, size);

   for (int i = 0; i < keywords.size(); i++)
   {
       if (keywords[i].compare(name) == 0)
       {
           abort("Function name cannot be a Keyword");
       }
   }

   for (int i = 0; i < functions.size(); i++)
   {
       if (functions[i] == vec[2])
       {
           abort("Function Name Repeated");
       }
   }

   functions.push_back(vec[2]);
   if (vec[3] != "{")
   {
       abort("{ expected ");
   }
   string str = vec[1] + " " + vec[2] + " " + vec[3];
   write(str);
}

void balanced(string s)
{
   if (parenthesis.empty())
   {
       abort("No Opening Bracket found, but closing bracket encounter");
   }
   char x = s[0];
   string par;
   switch (x)
   {
   case '}':
       par = parenthesis.top();
       if (par[0] != '{')
       {
           abort("Unbalanced Bracket,  '}' encountered");
       }
       parenthesis.pop();
 write("}");
       break;
   case ')':
       par = parenthesis.top();
       if (par[0] != '(')
       {
           abort("Unbalanced Bracket,  ')' encountered");
       }
       parenthesis.pop();
       break;
   case ']':
       par = parenthesis.top();
       if (par[0] != '[')
       {
           abort("Unbalanced Bracket,  ']' encountered");
       }
       parenthesis.pop();
       break;
   default:
       if (parenthesis.empty())
       {
           abort("No Opening Bracket found, but closing bracket encounter");
       }
       break;
   }
}

void push(string s)
{
   parenthesis.push(s);
}

void isvalid_brackets(vector<string> vec)
{
   for (int i = 0; i < vec.size(); i++)
   {
       if (vec[i].compare("{") == 0 || vec[i].compare("(") == 0 || vec[i].compare("[") == 0)
       {
           push(vec[i]);
       }
       if (vec[i].compare("}") == 0 || vec[i].compare(")") == 0 || vec[i].compare("]") == 0)
       {
           balanced(vec[i]);
       }
   }
}

bool isvalid_variable(string str)
{
   for (int i = 0; i < variables.size(); i++)
   {
       if (str.compare(variables[i]) == 0)
       {
           return true;
       }
   }
   return false;
}

bool isvalid_datatype(string str)
{
   for (int i = 0; i < datatypes.size(); i++)
   {
       if (str.compare(datatypes[i]) == 0)
       {
           return true;
       }
   }
   return false;
}


void log(string data)
{
   ofstream outfile;
   outfile.open("log.txt", ios_base::app);
   outfile << data << endl;
   outfile.close();
}

void clrscreen(vector<string> vec)
{
   if (vec[0].compare("clear") == 0 && vec.size() == 1)
   {
       string clr = "system(\"CLS\");";
       write(clr);
   }
   else
   {
       abort("Invalid Clear Command");
   }
}

void isvalid_return(vector<string> tokens)
{
   if (isvalid_number(tokens[1]))
   {
       string str = tokens[0] + " " + tokens[1] + " ;";
       write(str);
   }
   else
   {
       abort("Invalid return");
   }
}

void is_init(vector<string> vec)
{
	if(vec.size()>2)
	{
		abort("Invalid  _init_ Statement ");
	}
	if(vec[0].compare("_init_")==0 && vec[1].compare("{")==0)
	{
		string str = "int main() {";
		write(str);
	}
	else
	{
		abort("Invalid  _init_ Statement ");
	}
}





bool isvalid_functionpresent(vector<string> vec)
{
//	write("stu");
	for(int index=0;index<vec.size();index++)
	{
		for(int i=0;i<functions.size();i++)
		{
			if(functions[i].compare(vec[index])==0)
			{
//				write("here mf");
				func_call(vec,index);
//				write("done");
				return true;
			}
		}
	}
	return false;
}

void func_call(vector<string> vec,int index)
{
	if(index==0)
	{
		string str = vec[0] + " ;";
		write(str);
	}
	else if(index == 2)
	{
		string str = vec[0] + " " + vec[1] + " " + vec[2] + " ;";
		write(str); 
	}
	else
	{
		abort("Invalid Function Call");
	}
}




void isvalid_expression(vector<string> tokens)
{
    int flag, i = 0, index = 0, temp=0;
       string str;
    
    if(!isvalid_functionpresent(tokens))
    {
    if(tokens[1][0] == '[')
    {
        str = str + tokens[0] + tokens[1]; 
        temp = 1;
        index = 2;
    }
		while (index < tokens.size())
	    {
	        flag = 0;
	        if (i % 2 == temp)
	        {
	            if (isvalid_variable(tokens[index]) || isvalid_number(tokens[index] ))
	                flag = 1;
	        }
	        else
	        {
	            if (isvalid_operator(tokens[index]))
	                flag = 2;
	        }
	        if (flag == 0)
	            abort("error in expression");
	        str = str + " " + tokens[index];
	        i++;
	        index++;
	    }
	    str = str + ";";
	    write(str);
	}
}





