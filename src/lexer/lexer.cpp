lexer::Lexer::Lexer(std::string data) {
    this->data=data;
    if (data.size() != 0) {
        this->chr=data[0];
    }
    else {
        this->chr='\0';
    }
}

lexer::Lexer::~Lexer() { }

void lexer::Lexer::advance(){
    this->pos.advance(this->chr);
    if (this->pos.index > this->data.length()){
        this->chr='\0';
        return;
    }
    this->chr=this->data[this->pos.index];
}

std::vector<lexer::Token> lexer::Lexer::generate_tokens() {
    std::vector<lexer::Token> tokens;
    while (this->chr!='\0') {
        if (isdigit(this->chr)) {
            Position start = this->pos;
            std::string data(1, this->chr);
            this->advance();
            tokens.push_back(lexer::Token(data, lexer::TokenType::INTEGER, start, this->pos));
        }
        else if (this->chr == '+') {
            Position start = this->pos;
            std::string data(1, this->chr);
            this->advance();
            tokens.push_back(lexer::Token(data, lexer::TokenType::PLUS, start, this->pos));
        }
        else {
            Position start = this->pos;
            std::string data(1, this->chr);
            this->advance();
            tokens.push_back(lexer::Token(data, lexer::TokenType::UNKNOWN, start, this->pos));
        }
    }

    Position start = this->pos;
    std::string data("\\0");
    this->advance();
    tokens.push_back(lexer::Token(data, lexer::TokenType::EOF_TOK, start, this->pos));
    return tokens;
}
