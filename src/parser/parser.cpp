#include <memory>
#include <optional>
#include <tuple>
#include <vector>

#include "nodes.cpp"

namespace parser {
enum Precedence {
    LOWEST = 1,
    ASSIGN,
    LOGICAL_OR,
    LOGICAL_AND,
    LOGICAL_NOT,
    EQUALS,
    LESSGREATER,
    BITWISE_OR_PREC,
    BITWISE_XOR_PREC,
    BITWISE_AND_PREC,
    BITWISE_SHIFT_PREC,
    SUM,
    PRODUCT,
    BITWISE_NOT_PREC,
    EXP,
    CALL,
    INDEX,
    UNARY,
    TERNARY,
};

class Parser {
   private:
    lexer::Token current;
    std::vector<lexer::Token> tokens;
    size_t idx;

    Precedence get_precedence() {
        switch (this->current.type) {
            case lexer::TokenType::PLUS:
                return Precedence::SUM;
            default:
                return Precedence::LOWEST;
        }
    }

    bool is_current_eof() {
        return this->current.type == lexer::TokenType::EOF_TOK;
    }

    lexer::Token advance() {
        const auto idx = ++this->idx;
        if (idx == this->tokens.size()) {
            this->current = this->tokens.at(this->tokens.size() - 1);
        } else {
            this->current = this->tokens.at(idx);
        }
        return this->current;
    }

    std::unique_ptr<Node> parse_statement() {
        switch (this->current.type) {
            default: {
                return this->expr();
            }
        }
    }

    std::optional<std::unique_ptr<Node>> atomic() { return std::nullopt; }

    std::unique_ptr<Node> expr() {
        auto atomic = this->atomic();
        if (!atomic.has_value()) {
            TODO;
        }
        auto left = *std::move(atomic);
        while (!this->is_current_eof()) {
            auto next = this->advance();
            std::cout << next << std::endl;
        }
        return left;
    }

   public:
    Parser(std::vector<lexer::Token> tokens) {
        this->tokens = tokens;
        this->idx = 0;
        this->current = this->tokens.at(0);
    }

    ~Parser() {}

    std::vector<std::unique_ptr<Node>> block() {
        std::vector<std::unique_ptr<Node>> nodes;

        while (!is_current_eof()) {
            nodes.push_back(parse_statement());
        }

        return nodes;
    }
};
}  // namespace parser