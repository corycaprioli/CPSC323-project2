#include "lexer.h"

  Lexer::Lexer() {}

  Lexer::~Lexer() {}

  //DFSM for integers and reals
  int Lexer::FSM_int_real(std::string str) {
    int state = 1; //starting state
    int column;
    //create table for real/int DFSM
    int table[6][3] = {0,'d','.', 
                       1, 2, 5, 
                       2, 2, 3, 
                       3, 4, 5,
                       4, 4, 5, 
                       5, 5, 5};

    int accept[2] = {2, 4}; //accepting states

    int size = str.size();
    for(int i = 0; i < size; i++) {
       column = int_real_column(str[i]); //change column based on str[i] type
       if(column == 3) {
        state = 5;
        return 0;
       }
       state = table[state][column]; //change state based on table location
    }

    if(state == 5) {
      return 0; //invalid
    }

    if(state == accept[0]) {
      return 1; //integer
    } else if(state == accept[1]) {
       return 2; //real
    } else {
      return 0; //invalid
    }
  }
    

  int Lexer::FSM_id(std::string lexeme) {
    int state = 1; //starting state
    int column;
    // create DFSM table for identifiers
    int table[7][4] = {0,'l','d','_',
                       1, 2, 6, 6,
                       2, 5, 4, 3,
                       3, 5, 4, 3,
                       4, 5, 4, 3,
                       5, 5, 4, 3,
                       6, 6, 6, 6};

    int accept[4] = {2, 3, 4, 5}; //accepting states

    int size = lexeme.size();
    for(int i = 0; i < size; i++) {
      column = id_column(lexeme[i]); //update column based on str[i] type
      if(column == 4) {
        state = 6;
        return 0;
      }
      state = table[state][column];
      //update state based on table location
    }

    if(state == 6) {
      return 0; //fail state
    }

    if(state == accept[0] || state == accept[1] || state == accept[2] || state == accept[3]) {
      return 1; //identifer
    } else {
      return 0; //invalid
    }
  }

  int Lexer::int_real_column(char input) const {
     if(isdigit(input)) {
      return 1; //digit column
     } else if(input == '.') {
      return 2; // '.' column
     } else {
      return 3; //invalid
     }
  }

  int Lexer::id_column(char input) const {
    if(isalpha(input)) {
      return 1; //letter column
    } else if(isdigit(input)) {
      return 2; //digit column
    } else if(input == '_') {
      return 3; // '_' column
    } else {
      return 4; //invalid
    }
  }
  //check if char is a seperator
  bool Lexer::is_separator(char ch) const {
    std::vector<char> seperators = {'(', ')', '{', '}', '[', ';', ':', ',', '"', '#'};

    for(int i = 0; i < seperators.size(); i++) {
      if(seperators[i] == ch) {
        return 1; //separator
      }
    }
    return 0; //not separator
  }
  //check if identifier is a keyword
  bool Lexer::is_keyword(std::string id)const {
    std::vector<std::string> keywords = {"if", "for", "while", "do", "int", "double", "float", "bool", "endif", "endwhile", "put", "else", "return", "true", "false", "std", "cout", "class", "throw", "continue", "break", "endl"};

    for(int i = 0; i < keywords.size(); i++) {
      if(keywords[i] == id) {
        return 1; //keyword
      }
    }
    return 0; //identifier

  }
  // check if char is an operator
  bool Lexer::is_operator(char ch) const {
    std::vector<char> operators = {'+', '-', '*', '/', '%', '=', '>', '<', '!', '&', '|', '^', '~'};

    for(int i = 0; i < operators.size(); i++) {
      if(operators[i] == ch) {
        return 1; //operator
      }
    }
    return 0; //not operator

  }

  int Lexer::type(std::string s) {
    int length = s.length();
    //check if input string has an operator
    for(int i = 0; i < length; i++) {
      if(is_operator(s[i])) {
        return 1; //operator
      }
    }
    //check if input string has a separator
    for (int i = 0; i < length; i++) {
		if (is_separator(s[i]))
			return 2; //separator
	  }

	  //first character of the input string
	  char first_ch = s[0];

	  if (isalpha(first_ch)) {
      //if first char is a letter return 3 for identifier
		  return 3; 
  
	  } else if (isdigit(first_ch)) {
		  //if first char is a digit return 4 for int or real
		  return 4;
	  } else { 
		  return 5; //invalid input
    }

	  return 6; //none of the above
  }

	void Lexer::lexer(std::ifstream& file) {
	  std::string lexeme;
	  int end_state = 0;
	  bool found = false;
	  char ch;

	  while (!found) {
		  ch = file.get();
      
      // end loop if ch is sep, op, space, or EOF
		  if (this->is_separator(ch) || this->is_operator(ch) || isspace(ch) || ch == EOF) {
			  found = true;
		  }

		  if (!lexeme.empty() && (this->is_separator(ch) ||   this->is_separator(ch))) {
			  file.unget();
      } else if (!isspace(ch) && !(ch == EOF)) {
			  lexeme += ch;
      }

		  if (lexeme.empty() && !(ch == EOF)) {
			  found = false;
      }
	}

	if (lexeme.empty() && ch == EOF) {
		this->setLexeme("EOF");
		this->setToken("EOF");
		return;
	}

	int lexeme_type = type(lexeme); //get lexeme type

	//check for identfier
	if (lexeme_type == 3) {
		end_state = FSM_id(lexeme);
    this->setLexeme(lexeme);
        
    if (end_state == 1) {
			if (is_keyword(lexeme)) {
				this->setToken("keyword");
      } else {
				this->setToken("identifier");
      }
		} else {
			this->setToken("invalid identifier");
		}
	}

	//check for operator
	else if (lexeme_type == 1) {
		lexeme = ch;
		ch = file.peek();

    //find 2 char operators
		if ((lexeme[0] == '-' && ch == '-') ||
        (lexeme[0] == '+' && ch == '+') ||
        (lexeme[0] == '+' && ch == '=') ||
        (lexeme[0] == '-' && ch == '=') ||
        (lexeme[0] == '*' && ch == '=') ||
        (lexeme[0] == '/' && ch == '=') ||
        (lexeme[0] == '%' && ch == '=') ||
        (lexeme[0] == '=' && ch == '=') ||
        (lexeme[0] == '!' && ch == '=') ||
        (lexeme[0] == '>' && ch == '=') ||
        (lexeme[0] == '<' && ch == '=') ||
        (lexeme[0] == '&' && ch == '&') ||
        (lexeme[0] == '|' && ch == '|') ||
        (lexeme[0] == '<' && ch == '<') ||
        (lexeme[0] == '>' && ch == '>') ||
        (lexeme[0] == ':' && ch == ':'))
		{
			lexeme += ch;
			file.get();
		}

		//check if single and double char operators are valid or not
		if (lexeme == "--" ||
        lexeme == "++" ||
        lexeme == "+=" ||
        lexeme == "-=" ||
        lexeme == "*=" ||
        lexeme == "/=" ||
        lexeme == "%=" ||
        lexeme == "==" ||
        lexeme == "!=" ||
        lexeme == ">=" ||
        lexeme == "<=" ||
        lexeme == "&&" ||
        lexeme == "||" ||
        lexeme == "<<" ||
        lexeme == ">>" ||
        lexeme == "::" ||
        is_operator(lexeme[0])) {
			this->setToken("operator");
			this->setLexeme(lexeme);
		} else {
			this->setToken("invalid operator");
			this->setLexeme(lexeme);
		}
	}
	//check for separator
	else if (lexeme_type == 2) {
    if(is_separator(lexeme[0])) {
      this->setLexeme(lexeme);
		  this->setToken("separator");
    } else {
      this->setLexeme(lexeme);
			this->setToken("invalid separator");
    }
	}
    //put number into the int/real DFSM to find if it is an int, a real, or an invalid number
    else if (lexeme_type == 4)
	  {
		  end_state = FSM_int_real(lexeme);
		  this->setLexeme(lexeme);

		  if (end_state == 1) {
			  this->setToken("integer");
		  } else if(end_state == 2) {
        this->setToken("real");
      } else {
			  this->setToken("invalid number");
      }
	  } else {
	  	this->setLexeme(lexeme);
	  	this->setToken("invalid input"); //invalid input if none of the above
	  }
  }

	void Lexer::setToken(const std::string new_token) {
    token_ = new_token; //token = input
  }
	void Lexer::setLexeme(const std::string new_lexeme) {
    lexeme_ = new_lexeme; //lexeme = input
  }

	std::string Lexer::getToken() const {
    return token_; //return the current token
  }
	std::string Lexer::getLexeme() const {
    return lexeme_; //return current lexeme
  }
