#include <vector>

namespace lexer {
    enum TokenType {
        INTEGER,
        PLUS,
        UNKNOWN,
        EOF_TOK,
    };

    std::string token_type_to_str(TokenType type) {
        switch (type) {
            case TokenType::INTEGER:
                return "integer";
            case TokenType::PLUS:
                return "plus";
            case TokenType::UNKNOWN:
                return "???";
            case TokenType::EOF_TOK:
                return "EOF";

            default:
                return "Unknown token!";
        }
    }

    class Position{
        public:
            size_t col;
            size_t line;
            size_t index;

            Position(){
                this->index=0;
                this->col=0;
                this->line=0;
            }

            Position(int index_, int col_, int line_){
                this->index=index_;
                this->col=col_;
                this->line=line_;
            }

            void advance(char chr){
                this->index++;

                if (chr=='\n'){
                    this->line++;
                    this->col=0;
                } else{
                    this->col++;
                }
            }

            void advance(){
                this->index++;
                this->col++;
            }

            Position copy(){
                return Position(this->index,this->col,this->line);
            }
            
    };

    class Token{
        friend std::ostream& operator<<(std::ostream &s, const Token &tok);

        public:
            std::string data="";
            TokenType type;
            Position start;
            Position end;

            Token(){}
            Token(std::string data, TokenType type, Position start, Position end){
                this->data=data;
                this->type=type;
                this->start=start;
                this->end=end;
            }
        
    };

    std::ostream& operator<<(std::ostream &s, const Token &tok) {
        if (tok.data.length()==0){
            return s << token_type_to_str(tok.type);
        }
        return s << token_type_to_str(tok.type) << ":" << tok.data << "  start: (l=" << tok.start.line << ", i=" << tok.start.index << ", c="  << tok.start.col << ")" << " end: (l=" << tok.end.line << ", i=" << tok.end.index << ", c="  << tok.end.col << ")";
    }


    class Lexer {
    private:
        std::string data;
        char chr;
        Position pos;
        
    public:
        Lexer(std::string data);
        ~Lexer();
        std::vector<Token> generate_tokens();
        void advance();
    };
};

#include "lexer.cpp"
