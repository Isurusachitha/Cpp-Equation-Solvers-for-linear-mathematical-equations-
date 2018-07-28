/***********************************************************************************************************************************************
Courese      :    CO2210 - Programming Quest
Academic Year:    2015/16
Name         :    HERATH HMMISB
Index No     :    16_ENG_029
Assigment    :    1
Date         :   28-07-2018

**********************************************************************************************************************************************************/

#include <iostream>
# include<iostream>
#include <math.h>
#include<fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <stack>
#include <iostream>
#include <iomanip>

using namespace std;

//Functions
vector<string>   ReadFile();
string EqualSignCheck(string str);
void OutFile(vector<string> VecReslt);

int getOpterPrecedence (char c);
double OperationExe(double val1, double val2, char opertr);
double Evaluate(string EqStirng);
bool isDigit(char c);
bool isOpter(char c);
bool isClosingBracket(char c);
bool isOpeningBracket(char c);
bool CompareBrackets(char Close,char Open);

// Main function

int main() {

  std::vector<string> Vec= ReadFile() ; // getting formulas
  std::vector<string> VecResult;

std::cout << "# Evaluvated Mathematical formulas  " << "\n \n";
   //Evaluating formulas
   for(int i=0;i<(Vec.size());i++){
      std::cout << Vec[i]<<" ";

      std::cout << std::fixed;
      std::cout << std::setprecision(2);

      double result =Evaluate(EqualSignCheck(Vec[i]));
      std::cout << result << "\n \n";

      string results = Vec[i]+ to_string(result);
      VecResult.push_back(results);

   }

    OutFile(VecResult);
   return 0;
}


/*
  -------------------------------------------------------------------------
*/

string EqualSignCheck(string str){

     if(str[str.length()-1]=='='){  // cheching for equal sign

       str=str.substr(0,str.length()-1);  // removeing equal sign

       str="("+str+")";
       return str;

     }else{
             std::cerr << "E :  >> missing end = sign " ;
             return "err";
     }


}


vector<string>  ReadFile() {

	string str;
  std::vector<string> TempVec;

	ifstream infile("formulas.txt");  // TXT

	while(infile>>str){
          TempVec.push_back(str);
	}

	infile.close();

  return TempVec;
}

 /*
   Output the evaluvated anwsers :
------------------------------------------------------------
  <!>------------- Warning------------------------------<!>
   errors such as missing equal symbol at t
   he end of the formula or  imbalance bracket use, or
   any other mathematical errors are not indicated in outputed "result.txt: file

 # all errors are printed in conslose alongside the formula with
 ‘E’ and type of occured error.
*/
void OutFile(vector<string> VecReslt){



	           ofstream outfiletxt("Result.txt"); // creating stream object and create Result.txt file

          outfiletxt << "                    Output the evaluvated anwsers :  "<<'\n';
          outfiletxt << "  ------------------------------------------------------------"<<'\n';
          outfiletxt << "            <!>------------- Warning------------------------------<!>"<<'\n';
          outfiletxt << "             errors such as missing equal symbol at "<<'\n';
          outfiletxt << "             the end of the formula or  imbalance bracket use, or"<<'\n';
          outfiletxt << "             any other mathematical errors are not indicated in outputed 'result.txt: file'  "<<'\n';

          outfiletxt << "             # all errors are printed in conslose alongside the formula with"<<'\n';
          outfiletxt << "             ‘E’ and type of occured error."<<'\n';

          outfiletxt << "  --------------------------------------------------------------------"<<'\n';
          outfiletxt << "  evaluvated anwsers   "<<'\n';
          outfiletxt << "  --------------------------------------------------------------------"<<'\n';
            for(int i=0;i<VecReslt.size();i++){

               outfiletxt <<VecReslt[i]<<'\n';

            }

	            // Writing data to genarated file

						 outfiletxt.close();


}

/***
   Setuping operator precedance with waeighted values
***/

int getOpterPrecedence (char c){
// Operator precedance BODMAS
    switch (c)
    {
        case '+':return 1;
        case '-': return 1;
        case '*':return 2;
        case '/': return 2;
        default: return -1;
    }
}

/**  Arithmetic Operations execution **/

double OperationExe(double val1, double val2, char opertr){

     if(opertr=='+'){
       return (val1 +val2);
     }else if(opertr=='-'){
       return (val1 - val2);
     }else if(opertr=='*'){
       return (val1 * val2);
     }else if(opertr=='/'){

                if(val2>0){
                     return (val1 / val2 );
                   }else{
                     std::cerr << "E - division by Zero " ;
                     return 0;
                   }

     }else{
       std::cerr << "E- invalid Operator" ;
       return 0;
     }

}


//check if char is a digit.

bool isDigit(char c){

    if (c == '0' || c == '1'|| c == '2'|| c == '3'|| c == '4'|| c == '5'|| c == '6'|| c == '7'|| c == '8'|| c == '9')
    return true;
    else
    return false;
}

//check if char is an operator.
bool isOpter(char c){
     if(c == '+' || c == '-' || c == '*' || c == '/' )
     return true;
     else
     return false;
}
/*
  checking for Opening and closing brackets
*/
bool isClosingBracket(char c){
  if(c == ')' || c == ']' || c == '}'  )
  return true;
  else
  return false;
}
bool isOpeningBracket(char c){
  if(c == '(' || c == '[' || c == '{'  )
  return true;
  else
  return false;
}

/** Compare Opening and Cloase brackets

**/
bool CompareBrackets(char Close,char Open){

  if(Close==')' && Open=='('){
    return true;
  }else if(Close=='}' && Open=='{'){
      return true;
  }else if(Close==']' && Open=='['){
      return true;
  }else{
    return false;
  }

}
/** Equation Evaluator**/

double Evaluate(string EqStirng){

  if(!("err"==EqStirng)){  // Error Massage Handling



    int CharPostion=0;


    stack <double> values; // stack to store integer values.
    stack <char> optrs;  // stack to store operators.

  for (CharPostion = 0; CharPostion < EqStirng.length(); CharPostion++) {

          char Strchar=EqStirng[CharPostion];

          if(isOpeningBracket(Strchar)){ // indentifying opening unbracketed

              optrs.push(Strchar);

          }
          else if(isDigit(Strchar)){
            // varifying  the current valueeis a digit and push into values stack

                  double val = 0;

             if(isDigit(EqStirng[CharPostion]+1)){
               // getting multi digit numbers
                   while(CharPostion < EqStirng.length() && isDigit(EqStirng[CharPostion])){

                     val = (val*10.0) + (double)(EqStirng[CharPostion]-'0');
                     CharPostion++;

                     }

                 CharPostion--;
             }else{
                 val =  (double)(EqStirng[CharPostion]-'0');
             }

               values.push(val);

         }
         else if(isOpter(Strchar)){  // indentifying operators

             // Operator precedance BODMAS

              if(!(optrs.empty())){


                 if( getOpterPrecedence(Strchar) < getOpterPrecedence(optrs.top())){


                            double val1=values.top();
                            values.pop();
                            double val2=values.top();
                            values.pop();

                            char opter=optrs.top();
                            optrs.pop();

                            values.push(OperationExe(val1,val2,opter));


                            optrs.push(Strchar);

                 }else{

                     optrs.push(Strchar);
                 }

              }else{

                  optrs.push(Strchar);

              }

         }
         else if(isClosingBracket(Strchar)){ // indentifying closing brackets


          if(!optrs.empty()){

                          char bracketChr=  Strchar;

               while(!isOpeningBracket((optrs.top()))){

                   double val2=values.top();
                   values.pop();

                   double val1=values.top();
                   values.pop();

                   char opter=optrs.top();

                   if(isOpter(opter)){

                       values.push(OperationExe(val1,val2,opter));
                       optrs.pop();

                   }


               }
                           // optrs.push(EqStirng[CharPostion]);

                if(isOpeningBracket(optrs.top()) && CompareBrackets(Strchar,optrs.top())){  // remove opening bracket;
                           optrs.pop();
                   }else{
                        std::cerr << "E - Imbalance bracket " ;
                        return 0;
                  }


         }else{ // checking Imbalances- Opening brackets
              std::cerr << "E - Imbalance bracket " ;
              return 0;
         }


     }


  }


        if(!optrs.empty()){ // checking Imbalances- Opening brackets

             std::cerr << "E - Imbalance bracket " ;
             return 0;

        }else{
                 return values.top(); // returning evaluvated values of formula
       }

    }else{
             return 0;
         }

  }
