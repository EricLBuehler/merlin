namespace parser {
enum NodeType {
    INTEGER,
    BINARY,
};

class Node {
   private:
    NodeType type;
    void* data;

   public:
    // void* data must be allocated with free
    Node(NodeType type, void* data) {
        this->type = type;
        this->data = data;
    }
    ~Node() { free(this->data); }

    std::tuple<NodeType, void*> get_data() { return {this->type, this->data}; }
};
}  // namespace parser