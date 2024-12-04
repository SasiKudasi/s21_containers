
#include <iostream>
class BynaryTree
{
private:
   int key;
   int value;
   BynaryTree* left = nullptr;
   BynaryTree* right = nullptr;
public:
    BynaryTree(int key, int value){
        this->key = key;
        this->value = value;
    };
   // ~BynaryTree();

    void add(int key, int value){
        if(key < this->key){
            if(this->left == nullptr){
                this->left = new BynaryTree(key, value);
            }else{
                this->left->add(key, value);
            }
        }else{
            if(this->right == nullptr){
                this->right = new BynaryTree(key, value);
            }else{
                this->right->add(key, value);
            }
    
        }
    }

    BynaryTree* search(int key){
        if(this->key == key){
            return this;
        }else if(key < this->key){
            if(this->left == nullptr){
                return nullptr;
            }else{
                return this->left->search(key);
            }
        }else{
            if(this->right == nullptr){
                return nullptr;
            }else{
                return this->right->search(key);
            }
        }
    }

    void print(BynaryTree *node){
        if(node != nullptr){
            std::cout << node->key << " " << node->value << std::endl;
            print(node->left);
            print(node->right);
        }
    }

    void print(){
        std::cout << this->key << " " << this->value << std::endl;
    }

};

int main(){
    BynaryTree tree(1, 1);
    tree.add(2, 2);
    tree.add(3, 3);
    tree.add(4, 400);
    tree.add(5, 5);
    tree.add(6, 6);
    tree.add(7, 7);
    tree.add(8, 8);
    tree.add(9, 9);
    auto node = tree.search(4);
    node->print();
    //tree.print(&tree);
    return 0;
}