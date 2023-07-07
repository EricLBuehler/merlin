#include <functional>

namespace parser {
enum NodeType {
    INTEGER,
    BINARY,
};

class Node {
   private:
    NodeType type;
    void* data;
    std::function<void(void*)> deleter;

   public:
    // void* data must be allocated with new
    Node(NodeType type, void* data, std::function<void(void*)> deleter) {
        this->type = type;
        this->data = data;
        this->deleter = deleter;
    }
    ~Node() { this->deleter(this->data); }

    std::tuple<NodeType, void*> get_data() { return {this->type, this->data}; }
};

enum BinaryType {
    ADD,
};

struct BinaryNode {
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    BinaryType type;
};

}  // namespace parser