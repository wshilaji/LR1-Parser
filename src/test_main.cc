
#include <string.h>
#include <iostream>
#include "GrammarPool.hpp"
#include "ParseStack.hpp"
#include "cmdline.h"

int main(int argc, char *argv[])
{
	cmdline::parser cmdParser;
	cmdParser.add<string>("Grammar",'g',"Grammar YAML file path",true,"./Grammar.yml");
    cmdParser.add<string>("Tokens",'t',"Tokens TEXT file path for Syntax-Parse",false);
	cmdParser.add<string>("Built LR1-Table",'l',"Load previously built LR1-Table YAML file",false);
    cmdParser.add<string>("Output LR1-Table",'o',"LR1-Table YAML file path",false,"./LR1-Parse-Table.yml");
	cmdParser.add<string>("Show LR1-Table obviously",'s',"Show LR1-Table in a CSV file",false);
    cmdParser.add<string>("Show AST",'a',"TEXT file path of AST",false,"./ast.txt");
    cmdParser.add<string>("Easy mode",'e',"Exit when error occured",false);
    #ifndef _MSC_VER_
    cmdParser.add<string>("Debug mode",'d',"Parse Tokens with stacks-infos(not for windows)",false);
	#endif

    cmdParser.parse_check(argc,argv);


    return 0;
}
