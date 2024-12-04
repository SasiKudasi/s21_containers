
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

   BynaryTree* GetMin(BynaryTree* node){
    if (node == nullptr){
        return nullptr;
    }
    if(node->left == nullptr){
        return node;
    }
    return GetMin(node->left);
   }

   BynaryTree* deleteNode(BynaryTree* node, int key){
       if(node == nullptr){
           return nullptr;
       }
       if(key < node->key){
           node->left = deleteNode(node->left, key);
       }else if(key > node->key){
           node->right = deleteNode(node->right, key);
       }else{
         if(node->left == nullptr || node->right == nullptr){
            node = (node->left == nullptr) ? node->right : node->left;
         }else{
            BynaryTree* minNode = GetMin(node->right);
            node->key = minNode->key;
            node->value = minNode->value;
            node->right = deleteNode(node->right, minNode->key);
         }
       }
       return node;

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
    tree.deleteNode(&tree,4);
   
    tree.print(&tree);
    return 0;
}