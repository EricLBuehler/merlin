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
                return this->expr(Precedence::LOWEST);
            }
        }
    }

    std::optional<std::unique_ptr<Node>> atomic() {
        switch (this->current.type) {
            case (lexer::TokenType::INTEGER): {
                auto data = (void*)new std::string(this->current.data);
                return std::optional(std::unique_ptr<Node>{
                    new Node(NodeType::INTEGER, data,
                             [](void* d) { delete (std::string*)d; })});
            }
            default: {
                return std::nullopt;
            }
        }
    }

    std::unique_ptr<Node> expr(Precedence precedence) {
        auto atomic = this->atomic();
        if (!atomic.has_value()) {
            UNIMPLEMENTED;
        }

        auto left = *std::move(atomic);

        this->advance();

        while (!this->is_current_eof() && precedence < get_precedence()) {
            switch (this->current.type) {
                case (lexer::TokenType::PLUS): {
                    left = binary_expr(get_precedence(), std::move(left), this->current.type);
                }
                default: {
                    return left;
                }
            }
        }

        return left;
    }

    //Expressions
    std::unique_ptr<Node> binary_expr(Precedence precedence, std::unique_ptr<Node> left, lexer::TokenType type) {
        this->advance();

        auto right = expr(precedence);
        BinaryType binary_type;
        switch (type) {
            case (lexer::TokenType::PLUS): {
                binary_type = BinaryType::ADD;
                break;
            }
            default: {
                UNREACHABLE;
            }
        }
        auto binary = (void*)new BinaryNode {
            std::move(left),
            std::move(right),
            binary_type,
        };
        
        return std::unique_ptr<Node>{
            new Node(NodeType::BINARY, binary,
                        [](void* d) { delete (BinaryNode*)d; })};
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