#include "par.h"

//constructor
Par::Par()
{}

//Print token and lexeme
void Par::print(std::ofstream& outfile) {

	outfile << "Token: " << std::left << std::setw(20) << this->token_ << "Lexeme: " << std::setw(20) << this->lexeme_ << std::endl;
}

//syntax rule functions
void Par::RAT23S(std::ifstream& infile, std::ofstream& outfile)
{
	//Get the first token in file.txt
	lexer(infile);
	print(outfile);

	outfile << "\t<RAT23S> -> <Opt Function Definitions> # <Opt Declaration List> # <Statement List>\n";

	OptFunctionDefinition(infile, outfile);
	if (lexeme_ == "#")
	{
		lexer(infile);
		print(outfile);
		OptDeclarationList(infile, outfile);
    if (lexeme_ == "#") 
    {
		  StatementList(infile, outfile);
		  if (lexeme_ != "EOF")
		  {
			  outfile << "\nThis is not EOF marker.\n"
				<< "Only <Opt Declaration List> and <Statement List> is allowed after #.\n\n";

		  } else {
		    outfile << "\nInvalid separator, '#' is expected after function definitions and before statement list.\n\n";
      }
	  }
	  else
	  {
		outfile << "\nInvalid separator, '#' is expected after function definitions and before declaration list.\n\n";

	  }
  }
}

void Par::OptFunctionDefinition(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "function")
	{
		outfile << "\t<Opt Function Definition> -> <Function Definition>\n";

		FunctionDefinition(infile, outfile);
	}
	else
	{
		outfile << "\t<Opt Function Definition> -> Epsilon" << std::endl;

		Empty(infile, outfile);
	}
}

void Par::FunctionDefinition(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Function Definition> -> <Function> <Function Definition Prime>\n";

	Function(infile, outfile);
	FunctionDefinitionPrime(infile, outfile);
}

void Par::FunctionDefinitionPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "function")
	{
		outfile << "\t<Function Definition Prime> -> <Function Definition>\n";

		FunctionDefinition(infile, outfile);
	}
	else
	{
		outfile << "\t<Function Definition Prime> -> Epsilon" << std::endl;

		Empty(infile, outfile);
	}
}

void Par::Function(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "function")
	{
		outfile << "\t<Function> -> function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>\n";
      
		lexer(infile);
		print(outfile);
		if (token_ == "identifier")
		{
			lexer(infile);
			print(outfile);
			if (lexeme_ == "(")
			{
				lexer(infile);
				print(outfile);
				OptParameterList(infile, outfile);
				if (lexeme_ == ")")
				{
					lexer(infile);
					print(outfile);
					OptDeclarationList(infile, outfile);
					Body(infile, outfile);
				}
				else
				{
					outfile << "\nFunction syntax error\n";
					outfile << "Invalid separator, ')' is expected after parameter list.\n\n";

				}
			}
			else
			{
				outfile << "\nFunction syntax error\n";
				outfile << "Invalid separator, '(' is expected after <identifier> and before parameter list.\n\n";
			}
		}
		else
		{
			outfile << "\nFunction syntax error\n";
			outfile << "Invalid token, <identifier> is expected after 'function'.\n\n";

		}
	}
	else
	{
		outfile << "\nFunction syntax error\n";
		outfile << "Invalid separator, 'function' is expected at the beginning of a function.\n\n";

	}

}

void Par::OptParameterList(std::ifstream& infile, std::ofstream& outfile)
{
	if (token_ == "identifier")
	{
		outfile << "\t<Opt Parameter List> -> <Parameter List>\n";

		ParameterList(infile, outfile);
	}
	else
	{
		outfile << "\t<Opt Parameter List> -> Epsilon" << std::endl;

		Empty(infile, outfile);
	}
}

void Par::ParameterList(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Parameter List> -> <Parameter> <Parameter List Prime>\n";

	Parameter(infile, outfile);
	ParameterListPrime(infile, outfile);
}

void Par::ParameterListPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == ",")
	{
		outfile << "\t<Parameter List Prime> -> , <Parameter>\n";

		lexer(infile);
		print(outfile);
		ParameterList(infile, outfile);
	}
	else
	{
		outfile << "\t<Parameter List Prime> -> Epsilon" << std::endl;

		Empty(infile, outfile);
	}
}

void Par::Parameter(std::ifstream& infile, std::ofstream& outfile)
{
	if (token_ == "identifier")
	{
		outfile << "\t<Parameter> -> <IDs> <Qualifier>\n";

		IDs(infile, outfile);
		Qualifier(infile, outfile);
	}
	else
	{
		outfile << "\nParameter syntax error\n";
		outfile << "Invalid token, <identifier> is expected.\n\n";

	}
}

void Par::Qualifier(std::ifstream& infile, std::ofstream& outfile)
{
	if (token_ == "keyword" && lexeme_ == "int")
	{
		outfile << "\t<Qualifier> -> int\n";

		lexer(infile);
		print(outfile);
	}
	else if (token_ == "keyword" && lexeme_ == "bool")
	{
		outfile << "\t<Qualifier> -> bool\n";

		lexer(infile);
		print(outfile);
	}
	else if (token_ == "keyword" && lexeme_ == "real")
	{
		outfile << "\t<Qualifier> -> real\n";

		lexer(infile);
		print(outfile);
	}
	else
	{
		outfile << "\nQualifier syntax error. Invalid keyword\n";
		outfile << "'int', 'bool' or 'real' keyword is expected\n\n";

	}
}

void Par::Body(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "{")
	{
		outfile << "\t<Body> -> { <Statement List> }\n";

		lexer(infile);
		print(outfile);
		StatementList(infile, outfile);
		if (lexeme_ == "}")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			outfile << "\nFunction Body syntax error\n";
			outfile << "Invalid separator, '}' is expected after statements.\n\n";

		}
	}
	else
	{
		outfile << "\nFunction Body syntax error";
		outfile << "Invalid separator, '{' is expected before any statements.\n\n";

	}
}

void Par::OptDeclarationList(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "int" || lexeme_ == "bool" || lexeme_ == "real")
	{
		outfile << "\t<Opt Declaration List> -> <Declaration List>\n";

		DeclarationList(infile, outfile);
	}
	else
	{
		outfile << "\t<Opt Declaration List> -> Epsilon\n";

		Empty(infile, outfile);
	}
}

void Par::DeclarationList(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Declaration List> -> <Declaration> ; <Declaration List Prime>\n";

	Declaration(infile, outfile);
	if (lexeme_ == ";")
	{
		lexer(infile);
		print(outfile);
		DeclarationListPrime(infile, outfile);
	}
	else
	{
		outfile << "\nDeclaration List syntax error\n";
		outfile << "Invalid separator, ';' is expected at the end of declaration.\n\n";

	}
}

void Par::DeclarationListPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "int" || lexeme_ == "bool" || lexeme_ == "real")
	{
		outfile << "\t<Declaration List Prime> -> "
			<< "<Declaration List>\n";

		DeclarationList(infile, outfile);
	}
	else
	{
		outfile << "\t<Declaration List Prime> -> Epsilon\n";

		Empty(infile, outfile);
	}
}

void Par::Declaration(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Declaration> -> <Qualifier> <IDs>\n";

	Qualifier(infile, outfile);
	IDs(infile, outfile);
}

void Par::IDs(std::ifstream& infile, std::ofstream& outfile)
{
	if (token_ == "identifier")
	{
		outfile << "\t<IDs> -> <identifier> <IDs Prime>\n";

		lexer(infile);
		print(outfile);
		IDsPrime(infile, outfile);
	}
	else
	{
		outfile << "\nIDs syntax error\n";
		outfile << "Invalid token, <identifier> is expected\n\n";

	}
}

void Par::IDsPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == ",")
	{
		outfile << "\t<IDsPrime> -> , <IDs>\n";

		lexer(infile);
		print(outfile);
		IDs(infile, outfile);
	}
	else
	{
		outfile << "\t<IDs Prime> -> Epsilon\n";

		Empty(infile, outfile);
	}
}

void Par::StatementList(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Statement List> -> <Statement> <Statement List Prime>\n";

	Statement(infile, outfile);
	StatementListPrime(infile, outfile);
}

void Par::StatementListPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "{" || token_ == "identifier" || lexeme_ == "if" || lexeme_ == "return" || lexeme_ == "print" || lexeme_ == "scan" || lexeme_ == "while")
	{
		outfile << "\t<Statement List Prime> -> <Statement List>\n";

		StatementList(infile, outfile);
	}
	else
	{
		if (lexeme_ != "EOF")
		{
			outfile << "\t<Statement List Prime> -> Epsilon\n";
		}
		Empty(infile, outfile);
	}
}

void Par::Statement(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "{")
	{
		outfile << "\t<Statement> -> <Compound>\n";

		Compound(infile, outfile);
	}
	else if (token_ == "identifier")
	{
		outfile << "\t<Statement> -> <Assign>\n";

		Assign(infile, outfile);
	}
	else if (lexeme_ == "if")
	{
		outfile << "\t<Statement> -> <If>\n";

		If(infile, outfile);
	}
	else if (lexeme_ == "return")
	{
		outfile << "\t<Statement> -> <Return>\n";

		Return(infile, outfile);
	}
	else if (lexeme_ == "print")
	{
		outfile << "\t<Statement> -> <Print>\n";

		Print(infile, outfile);
	}
	else if (lexeme_ == "scan")
	{
		outfile << "\t<Statement> -> <Scan>\n";

		Scan(infile, outfile);
	}
	else if (lexeme_ == "while")
	{
		outfile << "\t<Statement> -> <While>\n";

		While(infile, outfile);
	}
	else
	{
		outfile << "\nStatement syntax error\n";
		outfile << "Invalid token or keyword or separator\n";
		outfile << "<identifier>,'if', 'return', 'write', 'read','while' 'keyword' or '{'is expected at the beginning of a statement.\n\n";

	}
}

void Par::Compound(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "{")
	{
		outfile << "\t<Compound> -> { <StatementList> }\n";

		lexer(infile);
		print(outfile);
		StatementList(infile, outfile);
		if (lexeme_ == "}")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			outfile << "\nCompound syntax error\n";
			outfile << "Invalid separator, '}' is expected at the end of statement list.\n\n";

		}
	}
	else
	{
		outfile << "\nCompound syntax error\n";
		outfile << "Invalid separator, '{' is expected at the beginning of statement list.\n\n";

	}
}

void Par::Assign(std::ifstream& infile, std::ofstream& outfile)
{
	if (token_ == "identifier")
	{
		outfile << "\t<Assign> -> <Identifier> := <Expression>;\n";

		lexer(infile);
		print(outfile);
		if (lexeme_ == "=")
		{
			lexer(infile);
			print(outfile);
			Expression(infile, outfile);
			if (lexeme_ == ";")
			{
				lexer(infile);
				print(outfile);
			}
			else
			{
				outfile << "\nAssign syntax error\n";
				outfile << "Invalid separator, ';' is expected at the end of assign statement.\n\n";

			}
		}
		else
		{
			outfile << "\nAssign syntax error\n";
			outfile << "Invalid operator, '=' is expected after <identifier> and before <expression>.\n\n";

		}
	}
	else
	{
		outfile << "\nAssign syntax error\n";
		outfile << "Invalid token, <identifier> is expected at the beginning of assign statement.\n\n";

	}
}

void Par::If(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "if")
	{
		outfile << "\t<If> -> if (<Condition>) <Statement> <If Prime>\n";

		lexer(infile);
		print(outfile);
		if (lexeme_ == "(")
		{
			lexer(infile);
			print(outfile);
			Condition(infile, outfile);
			if (lexeme_ == ")")
			{
				lexer(infile);
				print(outfile);
				Statement(infile, outfile);
				IfPrime(infile, outfile);
			}
			else
			{
				outfile << "\nIf statement syntax error\n";
				outfile << "Invalid separator, ')' is expected after condition.\n\n";

			}
		}
		else
		{
			outfile << "\nIf statement syntax error\n";
			outfile << "Invalid separator, '(' is expected before condition.\n\n";

		}
	}
	else
	{
		outfile << "\nIf statement syntax error\n";
		outfile << "Invalid keyword, 'if' keyword is expected at the beginning of If statement.\n\n";

	}
}

void Par::IfPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "fi")
	{
		outfile << "\t<If Prime> -> fi\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "else")
	{
		outfile << "\t<If Prime> -> else <Statement> fi\n";

		lexer(infile);
		print(outfile);
		Statement(infile, outfile);
		if (lexeme_ == "fi")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			outfile << "\nIf statement syntax error\n";
			outfile << "Invalid keyword, 'fi' is expected at the end of If statement.\n\n";

		}
	}
	else
	{
		outfile << "\nIf statement syntax error\n";
		outfile << "Invalid keyword, 'fi' is expected at the end of If Statement or 'else' is expected if there is an If-else statement.\n\n";

	}
}

void Par::Return(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "return")
	{
		outfile << "\t<Return> -> return <Return Prime>\n";

		lexer(infile);
		print(outfile);
		ReturnPrime(infile, outfile);
	}
	else
	{
		outfile << "\nReturn statement syntax error\n";
		outfile << "Invalid keyword, 'return' is expected at the beginning of Return statement.\n\n";

	}
}

void Par::ReturnPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == ";")
	{
		outfile << "\t<Return Prime> -> ;\n";
      
		lexer(infile);
		print(outfile);
	}
	else
	{
		outfile << "\t<Return Prime> -> <Expression>;\n";

		Expression(infile, outfile);
		if (lexeme_ == ";")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			outfile << "\nReturn statement syntax error\n";
			outfile << "Invalid separator, ';' is expected at the end of Return statement.\n\n";

		}
	}
}

void Par::Print(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "put")
	{
		outfile << "\t<Print> -> put (<Expression>);\n";

		lexer(infile);
		print(outfile);
		if (lexeme_ == "(")
		{
			lexer(infile);
			print(outfile);
			Expression(infile, outfile);
			if (lexeme_ == ")")
			{
				lexer(infile);
				print(outfile);
				if (lexeme_ == ";")
				{
					lexer(infile);
					print(outfile);
				}
				else
				{
					outfile << "\nPrint statement syntax error\n";
					outfile << "Invalid separator, ';' is expected at the end of Print statement.\n\n";

				}
			}
			else
			{
				outfile << "\nPrint statement syntax error\n";
				outfile << "Invalid separator, ')' is expected before ';' and after <Expression>.\n\n";

			}
		}
		else
		{
			outfile << "\nPrint statement syntax error\n";
			outfile << "Invalid separator, '(' is expected after 'put' keyword and before <Expression>.\n\n";

		}
	}
	else
	{
		outfile << "\nPrint statement syntax error\n";
		outfile << "Invalid keyword, 'put' is expected at the beginning of Print statement.\n\n";

	}
}

void Par::Scan(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "get")
	{
		outfile << "\t<Scan> -> read (<IDs>);\n";

		lexer(infile);
		print(outfile);
		if (lexeme_ == "(")
		{
			lexer(infile);
			print(outfile);
			IDs(infile, outfile);
			if (lexeme_ == ")")
			{
				lexer(infile);
				print(outfile);
				if (lexeme_ == ";")
				{
					lexer(infile);
					print(outfile);
				}
				else
				{
					outfile << "\nScan statement syntax error\n";
					outfile << "Invalid separator, ';' is expected at the end of Scan statement.\n\n";

				}
			}
			else
			{
				outfile << "\nScan statement syntax error\n";
				outfile << "Invalid separator, ')' is expected after <IDs> and before ';'.\n\n";

			}
		}
		else
		{
			outfile << "\nScan statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " after 'get' keyword and before <IDs>.\n\n";

		}
	}
	else
	{
		outfile << "\nScan statement syntax error\n";
		outfile << "Invalid keyword, 'get' is expected at the beginning of Scan statement.\n\n";

	}
}

void Par::While(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "while")
	{
		outfile << "\t<While> -> <while (<Condition>) <Statement> endwhile\n";

		lexer(infile);
		print(outfile);
		if (lexeme_ == "(")
		{
			lexer(infile);
			print(outfile);
			Condition(infile, outfile);
			if (lexeme_ == ")")
			{
				lexer(infile);
				print(outfile);
				Statement(infile, outfile);
			}
			else
			{
				outfile << "\nWhile statement syntax error\n";
				outfile << "Invalid separator, ')' is expected after condition and before any statements.\n\n";

			}
		}
		else
		{
			outfile << "\nWhile statement syntax error\n";
			outfile << "Invalid separator, '(' is expected before condition and after 'while' keyword.\n\n";

		}
	}
	else
	{
		outfile << "\nWhile-loop syntax error\n";
		outfile << "Invalid keyword, 'while' is expected at the beginning of While-loop.\n\n";

	}
}

void Par::Condition(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Condition> -> <Expression> <Relop> <Expression>\n";

	Expression(infile, outfile);
	Relop(infile, outfile);
	Expression(infile, outfile);
}

void Par::Relop(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "==")
	{
		outfile << "\t<Relop> -> ==\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "!=")
	{
		outfile << "\t<Relop> -> !=\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == ">")
	{
		outfile << "\t<Relop> -> >\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "<")
	{
		outfile << "\t<Relop> -> <\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "=>")
	{
		outfile << "\t<Relop> -> =>\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "<=")
	{
		outfile << "\t<Relop> -> <=\n";

		lexer(infile);
		print(outfile);
	}
	else
	{
		outfile << "\nRelop syntax error\n";
		outfile << "Invalid operator. '==', '!=', '>', '<', '=>' or '<=' is expected between 2 <Expression>.\n\n";

	}
}

void Par::Expression(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Expression> -> <Term> <Expression Prime>\n";

	Term(infile, outfile);
	ExpressionPrime(infile, outfile);
}

void Par::ExpressionPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "+")
	{
		outfile << "\t<Expression Prime> -> + <Term> <Expression Prime>\n";

		lexer(infile);
		print(outfile);
		Term(infile, outfile);
		ExpressionPrime(infile, outfile);
	}
	else if (lexeme_ == "-")
	{
		outfile << "\t<Expression Prime> -> - <Term> <Expression Prime>\n";

		lexer(infile);
		print(outfile);
		Term(infile, outfile);
		ExpressionPrime(infile, outfile);
	}
	else
	{
		outfile << "\t<Expression Prime> -> Epsilon\n";

		Empty(infile, outfile);
	}
}

void Par::Term(std::ifstream& infile, std::ofstream& outfile)
{
	outfile << "\t<Term> -> <Factor> <Term Prime>\n";

	Factor(infile, outfile);
	TermPrime(infile, outfile);
}

void Par::TermPrime(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "*")
	{
		outfile << "\t<Term Prime> -> * <Factor> <Term Prime>\n";

		lexer(infile);
		print(outfile);
		Factor(infile, outfile);
		TermPrime(infile, outfile);
	}
	else if (lexeme_ == "/")
	{
		outfile << "\t<Term Prime> -> / <Factor> <Term Prime>\n";

		lexer(infile);
		print(outfile);
		Factor(infile, outfile);
		TermPrime(infile, outfile);
	}
	else
	{
		outfile << "\t<Term Prime> -> Epsilon\n";

		Empty(infile, outfile);
	}
}

void Par::Factor(std::ifstream& infile, std::ofstream& outfile)
{
	if (lexeme_ == "-")
	{
		outfile << "\t<Factor> -> - <Primary>\n";

		lexer(infile);
		print(outfile);
		Primary(infile, outfile);
	}
	else
	{
		outfile << "\t<Factor> -> <Primary>\n";

		Primary(infile, outfile);
	}
}

void Par::Primary(std::ifstream& infile, std::ofstream& outfile)
{
	if (token_ == "identifier")
	{
		outfile << "\t<Primary> -> <identifier>\n";

		lexer(infile);
		print(outfile);
    if (lexeme_ == "(")
		{
			lexer(infile);
			print(outfile);
			IDs(infile, outfile);
			if (lexeme_ == ")")
			{
				lexer(infile);
				print(outfile);
				Statement(infile, outfile);
			}
			else
			{
				outfile << "\nIf statement syntax error\n";
				outfile << "Invalid separator, ')' is expected after IDs.\n\n";

			}
		}
		else
		{
			outfile << "\nIf statement syntax error\n";
			outfile << "Invalid separator, '(' is expected before IDs.\n\n";

		}
	}
	else if (token_ == "int")
	{
		outfile << "\t<Primary> -> <int>\n";

		lexer(infile);
		print(outfile);
	}
	else if (token_ == "real")
	{
		outfile << "\t<Primary> -> <real>\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "(")
	{
		outfile << "\t<Primary> -> (<Expression>)\n";

		lexer(infile);
		print(outfile);
		Expression(infile, outfile);
		if (lexeme_ == ")")
		{
			lexer(infile);
			print(outfile);
		}
		else
		{
			outfile << "\nInvalid separator, ')' is expected.\n\n";

		}
	}
	else if (lexeme_ == "true")
	{
		outfile << "\t<Primary> -> true\n";

		lexer(infile);
		print(outfile);
	}
	else if (lexeme_ == "false")
	{
		outfile << "\t<Primary> -> false\n";

		lexer(infile);
		print(outfile);
	}
	else
	{
		outfile << "\nPrimary syntax error\n";
		outfile << "Invalid token, separator, or boolean value. <identifier>, <integer>, <floating>, '(', 'true' or 'false' is expected after '-', '*' or '/'.\n\n";

	}
}

void Par::Empty(std::ifstream& infile, std::ofstream& outfile)
{
	
}

//Destructor
Par::~Par() {}
