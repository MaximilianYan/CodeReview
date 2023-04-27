#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

#define nullptr 0

struct Node {
    int16_t height;
    int key;
    void* value;
    struct Node* left;
    struct Node* right;
};

void NodeCtor(struct Node* ptr, int key, void* value) {
    ptr->key = key;
    ptr->value = value;
    ptr->height = 1;
    ptr->left = nullptr;
    ptr->right = nullptr;
}

struct AVLTree {
    struct Node* root_;
    size_t size_;
};

void AVLTreeCtor(struct AVLTree* ptr);
void Insert(struct AVLTree* ptr, int key, void* value);
void Erase(struct AVLTree* ptr, int key);
bool Contains(struct AVLTree* ptr, int key);
void** Get(struct AVLTree* ptr, int key);
void Clear(struct AVLTree* ptr);
void AVLTreeDtor(struct AVLTree* ptr);
size_t Size(struct AVLTree* ptr);
void Clear2(struct AVLTree* ptr, struct Node* node);
struct Node* Insert2(struct AVLTree* ptr, struct Node* node, int key, void* value);
struct Node* Erase2(struct AVLTree* ptr, struct Node* node, int key);
struct Node* Balance(struct AVLTree* ptr, struct Node* node);
struct Node* RotateLeft(struct AVLTree* ptr, struct Node* node);
struct Node* RotateRight(struct AVLTree* ptr, struct Node* node);
struct Node* FindMin(struct AVLTree* ptr, struct Node* node);
struct Node* DetachMin(struct AVLTree* ptr, struct Node* node);
int16_t BalanceFactor(struct AVLTree* ptr, struct Node* node);
void ActualizeHeight(struct AVLTree* ptr, struct Node* node);
int16_t Height(struct AVLTree* ptr, struct Node* node);

void AVLTreeCtor(struct AVLTree* ptr) {
    ptr->root_ = nullptr;
    ptr->size_;
}

void Insert(struct AVLTree* ptr, int key, void* value) {
    ptr->root_ = Insert2(ptr, ptr->root_, key, value);
}

void Erase(struct AVLTree* ptr, int key) {
    ptr->root_ = Erase2(ptr, ptr->root_, key);
}

bool Contains(struct AVLTree* ptr, int key) {
    return Get(ptr, key) != nullptr;
}

void** Get(struct AVLTree* ptr, int key) {
    struct Node* current = ptr->root_;
    while (current != nullptr) {
        if (current->key == key) {
            return &current->value;
        }
        current = key < current->key ? current->left : current->right;
    }
    return nullptr;
}

struct Node* GetFIRSTLESSTHANKey(struct AVLTree* ptr, int key) {
    struct Node* current = ptr->root_;
    struct Node* prev = nullptr;
    while (current != nullptr) {
        prev = current;
        current = current->key > key ? current->left : current->right;
    }
    return nullptr;
}

void Clear(struct AVLTree* ptr) {
    Clear2(ptr, ptr->root_);
    ptr->size_ = 0;
    ptr->root_ = nullptr;
}

void AVLTreeDtor(struct AVLTree* ptr) {
    Clear2(ptr, ptr->root_);
}

size_t Size(struct AVLTree* ptr) {
    return ptr->size_;
}

void Clear2(struct AVLTree* ptr, struct Node* node) {
    if (node == nullptr) {
        return;
    }
    Clear2(ptr, node->left);
    Clear2(ptr, node->right);
    free(node);
}

struct Node* Insert2(struct AVLTree* ptr, struct Node* node, int key, void* value) {
    if (node == nullptr) {
        ++ptr->size_;
        struct Node* r = calloc(sizeof(struct Node), 1);
        NodeCtor(r, key, value);
        return r;
    }
    if (key == node->key) {
        node->value = value;
        return node;
    }
    if (key < node->key) {
        node->left = Insert2(ptr, node->left, key, value);
    } else {
        node->right = Insert2(ptr, node->right, key, value);
    }
    return Balance(ptr, node);
}

struct Node* Erase2(struct AVLTree* ptr, struct Node* node, int key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = Erase2(ptr, node->left, key);
        return Balance(ptr, node);
    }
    if (node->key < key) {
        node->right = Erase2(ptr, node->right, key);
        return Balance(ptr, node);
    }

    --ptr->size_;
    if (node->right == nullptr) {
        struct Node* left_child = node->left;
        free(node);
        return left_child;
    }

    struct Node* right_min = FindMin(ptr, node->right);
    node->right = DetachMin(ptr, node->right);
    int tempK = right_min->key;
    right_min->key = node->key;
    node->key = tempK;
    void* tempV = right_min->value;
    right_min->value = node->value;
    node->value = tempV;
    free(right_min);
    return Balance(ptr, node);
}

struct Node* Balance(struct AVLTree* ptr, struct Node* node) {
    ActualizeHeight(ptr, node);// при insert/Detach всегда!
    int16_t bf = BalanceFactor(ptr, node);
    if (bf == -2) {
        if (BalanceFactor(ptr, node->left) == 1) {
            node->left = RotateLeft(ptr, node->left);
        }
        return RotateRight(ptr, node);
    } else if (bf == 2) {
        if (BalanceFactor(ptr, node->right) == -1) {
            node->right = RotateRight(ptr, node->right);
        }
        return RotateLeft(ptr, node);
    }
    return node;
}

struct Node* RotateLeft(struct AVLTree* ptr, struct Node* node) {
    struct Node* new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    ActualizeHeight(ptr, node);
    ActualizeHeight(ptr, new_parent);
    return new_parent;
}

struct Node* RotateRight(struct AVLTree* ptr, struct Node* node) {
    struct Node* new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    ActualizeHeight(ptr, node);
    ActualizeHeight(ptr, new_parent);
    return new_parent;
}

struct Node* FindMin(struct AVLTree* ptr, struct Node* node) {
    struct Node* curr = node;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

struct Node* DetachMin(struct AVLTree* ptr, struct Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = DetachMin(ptr, node->left);
    return Balance(ptr, node);
}

int16_t BalanceFactor(struct AVLTree* ptr, struct Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return (int16_t)Height(ptr, node->right) - (int16_t)Height(ptr, node->left);
}

int16_t max(int16_t a, int16_t a2) {
    if (a < a2) return a2;
    return a == a2 ? a2 : a;
}

void ActualizeHeight(struct AVLTree* ptr, struct Node* node) {
    if (node == nullptr) {
        return;
    }
    node->height = 1 + max(Height(ptr, node->left), Height(ptr, node->right));
}

int16_t Height(struct AVLTree* ptr, struct Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}


int main() {
    struct AVLTree tree;
    AVLTreeCtor(&tree);

    // for (int i = 0; i < 1000000; ++i) {
    //     Insert(&tree, i, (void*)(size_t)i);
    // }
    // for (int i = 200000; i < 600000; ++i) {
    //     Erase(&tree, i);
    // }

    int n = 0;
    scanf("%d", &n);
    char prec = '+';
    int prei = 0;
    while (n--) {
        char c;
        scanf("%c", &c);
        int i;
        scanf("%d", &i);

        if (c == '+') {
            if (prec == '?') {
                Insert(&tree, (i + prei) % 1e9, (void*)(size_t)((i + prei) % 1e9));
            } else { // prec == '+'
                Insert(&tree, i, (void*)(size_t)i);
            }
        } else { // c == '?'
            struct Node* ans = GetFIRSTLESSTHANKey(&tree, i);
            printf("%d", ans == nullptr ? -1 : ans->key);
        }

        prec = c;
        prei = i;
    }


    printf("%d", Size(&tree));

    return 0;
}
