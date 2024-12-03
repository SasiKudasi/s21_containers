#ifdef NODE

template <typename Key, typename Value = void>
struct Node {
    Key key;
    Value value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    bool isRed = true;

    // Конструктор для set
    Node(const Key& key) : key(key), value(), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {}

    // Конструктор для map
    Node(const Key& key, const Value& value) : key(key), value(value), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {}
};

#endif// NODE