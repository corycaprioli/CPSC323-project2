#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Lexer {
  private:

  char input;
	std::string lexeme_;
	std::string token_;

  public:
  
  Lexer();

  ~Lexer();

  int FSM_int_real(std::string);

  int FSM_id(std::string);

  int int_real_column(const char) const;

  int id_column(const char) const;

  bool is_separator(char) const;
  bool is_keyword(std::string)const;
  bool is_operator(char) const;

  int type(std::string);

	void lexer(std::ifstream&);

	void setToken(const std::string);
	void setLexeme(const std::string);

	std::string getToken() const;
	std::string getLexeme() const;

};

#endif