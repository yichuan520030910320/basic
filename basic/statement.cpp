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
    else if (token=="LET"){Expression *exp = parseExp(scanner);
        return new LET(exp);}
    else if (token=="END"){}
    else if (token=="IF"){}
    else if (token=="GOTO"){}
    else if (token=="REM"){//do nothing
         }
    else {error("SYNTAX ERROR");}
}
INPUT::INPUT(Expression *temp) {  ptr=temp;}
INPUT::~INPUT() noexcept {};
void INPUT:: execute(EvalState & state) {
    int value;
    while (1){
        try {char *temp;
            cout<<'?';
            cin>>temp;
            value=stringToInteger(temp);
        } catch (...) {
            cout<<"INVALID NUMBER"<<endl;
            continue;

        }
        break;
    }
    state.setValue(((IdentifierExp *) ptr)->getName(),value);
}
REM::REM() {};
REM::~REM() noexcept {};
void REM:: execute(EvalState & state){};
