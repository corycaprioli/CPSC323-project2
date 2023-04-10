#ifndef PAR_H
#define PAR_H

#include "lexer.h"

class Par : public Lexer {

public:
	//constructor
	Par();

	//<Rat23S> -> <Opt Function Definitions> # <Opt Declaration List> # <Statement List>
	void RAT23S(std::ifstream& infile, std::ofstream& outfile);

	//<Opt Function Definitions> -> <Function Definitions> | <Empty>
	void OptFunctionDefinition(std::ifstream& infile, std::ofstream& outfile);

	//<Function Definitions> -> <Function> <Function Definitions Prime>
	void FunctionDefinition(std::ifstream& infile, std::ofstream& outfile);

	//<Function Definitions Prime>  -> <Function Definitions> | <Empty>  
	void FunctionDefinitionPrime(std::ifstream& infile, std::ofstream& outfile);

	/* <Function> ->  function <Identifier>  (<Opt Parameter List>) <Opt Declaration List>  <Body> */
	void Function(std::ifstream& infile, std::ofstream& outfile);

	//<Opt Parameter List> ->  <Parameter List>   |  <Empty>
	void OptParameterList(std::ifstream& infile, std::ofstream& outfile);

	//<Parameter List>  ->  <Parameter> <Parameter List Prime>
	void ParameterList(std::ifstream& infile, std::ofstream& outfile);

	//<Parameter List Prime>  -> , <Parameter List> | <Empty>
	void ParameterListPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Parameter> ->  <IDs > <Qualifier> 
	void Parameter(std::ifstream& infile, std::ofstream& outfile);

	//<Qualifier> -> int   |  bool  |  real
	void Qualifier(std::ifstream& infile, std::ofstream& outfile);

	//<Body>  ->  {  < Statement List>  }
	void Body(std::ifstream& infile, std::ofstream& outfile);

	//<Opt Declaration List> -> <Declaration List>   | <Empty>
	void OptDeclarationList(std::ifstream& infile, std::ofstream& outfile);

	//<Declaration List>  -> <Declaration> ;  <Declaration List Prime>
	void DeclarationList(std::ifstream& infile, std::ofstream& outfile);

	//<Declaration List Prime>  -> <Declaration List> | <Empty>
	void DeclarationListPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Declaration> ->  <Qualifier > <IDs>
	void Declaration(std::ifstream& infile, std::ofstream& outfile);

	//<IDs> ->  <Identifier> <IDs Prime>
	void IDs(std::ifstream& infile, std::ofstream& outfile);

	//<IDs Prime> ->  , <IDs> | <Empty>
	void IDsPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Statement List> ->  <Statement> | <Statement> <Statement List Prime>
	void StatementList(std::ifstream& infile, std::ofstream& outfile);

	//<Statement List Prime> ->  <Statement List> | <Empty>
	void StatementListPrime(std::ifstream& infile, std::ofstream& outfile);

	/* <Statement> ->  <Compound> | <Assign> | <If> |  <Return> | <Print> | <Scan> | <While> */
	void Statement(std::ifstream& infile, std::ofstream& outfile);

	//<Compound> -> {  <Statement List>  }
	void Compound(std::ifstream& infile, std::ofstream& outfile);

	//<Assign> -> <Identifier> = <Expression>;
	void Assign(std::ifstream& infile, std::ofstream& outfile);

	//<If> -> if  ( <Condition>  ) <Statement> <If Prime>
	void If(std::ifstream& infile, std::ofstream& outfile);

	//<If Prime> ->  fi | else <Statement> fi
	void IfPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Return> ->  return <Return Prime>
	void Return(std::ifstream& infile, std::ofstream& outfile);

	//<Return Prime> ->  ; |  <Expression> ;
	void ReturnPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Print> ->   put ( <Expression>);
	void Print(std::ifstream& infile, std::ofstream& outfile);

	//<Scan> -> get ( <IDs> );
	void Scan(std::ifstream& infile, std::ofstream& outfile);

	//<While> -> while ( <Condition>  )  <Statement> endwhile
	void While(std::ifstream& infile, std::ofstream& outfile);

	//<Condition> -> <Expression>  <Relop>   <Expression>
	void Condition(std::ifstream& infile, std::ofstream& outfile);

	//<Relop> ->   == |  !=  |   >   | <   |  =>   | <=
	void Relop(std::ifstream& infile, std::ofstream& outfile);

	//<Expression>  -> <Term> <Expression Prime>
	void Expression(std::ifstream& infile, std::ofstream& outfile);

	/* <Expression Prime>  -> + <Term> <Expression Prime>  |
	- <Term> <Expression Prime> | <Empty> */
	void ExpressionPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Term>    ->  <Factor> <Term Prime>
	void Term(std::ifstream& infile, std::ofstream& outfile);

	/* <Term Prime> ->  * <Factor> <Term Prime> |  / <Factor> <Term Prime> | <Empty> */
	void TermPrime(std::ifstream& infile, std::ofstream& outfile);

	//<Factor> -> - <Primary> | <Primary>
	void Factor(std::ifstream& infile, std::ofstream& outfile);

	/* <Primary> -> <Identifier> | <Integer> | <Identifier> (<IDs>) | (<Expression>) | <Real> | true | false */
	void Primary(std::ifstream& infile, std::ofstream& outfile);

	//<Empty> -> epsilon
	void Empty(std::ifstream& infile, std::ofstream& outfile);

	//Helper functions
	void print(std::ofstream& outfile);

	//Destructor
	~Par();

private:
	
};

#endif
