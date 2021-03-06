/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}
 void parser_the_token(){

}

Statement *parsestatement(bool ifhaslinenum,string index){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();//enter the pattern of being able to read num
    //cout<<scanner.scanNumbersFlag<<endl;
    scanner.setInput(index);
    string token;
    if (ifhaslinenum) {
         token = scanner.nextToken();
    }
    token = scanner.nextToken();
    if (token=="INPUT"){
        Expression *temp= nullptr;
        temp=parseExp(scanner);
        if (temp->getType()!=IDENTIFIER) {error("SYNTAX ERROR");}
        return new INPUT(temp);
//       if (!scanner.hasMoreTokens()){error("SYNTAX ERROR");}
//        token = scanner.nextToken();
//       if (scanner.getTokenType(token)!=WORD) {error("SYNTAX ERROR");}
//    if (scanner.hasMoreTokens()) {error("SYNTAX ERROR");}
//        return new INPUT(token);
    } else if (token=="PRINT"){ Expression *exp = parseExp(scanner);
        return new PRINT(exp);
        }
    else if (token=="LET"){
       // cout<<"fuuuuuuuuck"<<endl;
        Expression *exp = parseExp(scanner);
        return new LET(exp);
    }
    else if (token=="END"){
        return new END();}
    else if (token=="IF"){
        Expression *exp = parseExp(scanner);
        Expression*temp1=readT(scanner);
        if (temp1->getType()!=IDENTIFIER) {error("SYNTAX ERROR");}
        Expression* temp2=readT(scanner);
        if (temp2->toString()!="="&&temp2->toString()!="<"&&temp2->toString()!=">") {error("SYNTAX ERROR");}
        Expression* temp3=readT(scanner);
        if (temp3->getType()!=IDENTIFIER) {error("SYNTAX ERROR");}

        Expression* temp4=parseExp(scanner);
        if (temp4->toString()!="THEN") {error("SYNTAX ERROR");}

        Expression*temp5=parseExp(scanner);
        if (temp5->getType()!=CONSTANT){error("SYNTAX ERROR");}

        return new IF(temp1,temp2,temp3,temp4,temp5);
    }
    else if (token=="GOTO"){
        Expression *exp = parseExp(scanner);
        return new GOTO(exp);
    }
    else if (token=="REM"){//do nothing
        Expression *exp = parseExp(scanner);
        return new REM(exp);
       }
    else {error("SYNTAX ERROR");}
}
INPUT::INPUT(Expression *temp) {  ptr=temp;}
INPUT::~INPUT() noexcept {};
void INPUT:: execute(EvalState & state) {
    int value;

    while (1){
        try {string temp;
            //char *temp= nullptr;
            cout<<" ";
            cout<<'?';
            cout<<" ";
            //cout<<"((((("<<endl;
            cin>>temp;
            //cout<<temp<<"******"<<endl;
            value=stringToInteger(temp);
        } catch (...) {
            cout<<"INVALID NUMBER"<<endl;
            continue;
        }
        break;
    }
    state.setValue(((IdentifierExp *) ptr)->getName(),value);
}

