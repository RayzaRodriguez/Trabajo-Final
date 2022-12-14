#include<stdlib.h>
#include<stdio.h>
#include <array>
#include <vector>
#include "seq_avl.h"

typedef struct node node;
typedef int (*cmp_t)(const void*, const void*);

struct node {
    node* left, * right, * parent;
    int height;
    void* data;
};

struct avl_tree {
    node* head;
    cmp_t cmp;
};

// Function declarations

static int height(node*);
static node* insert_h(avl_tree*, node*, void*);
static int max(int, int);
static void free_nodes(node*);
static node* remove_h(avl_tree*, node*, void*);
static int balance_factor(node*);
static node* find_h(avl_tree*, node*, void*);
static node* single_rotate_with_left(node*);
static node* single_rotate_with_right(node*);
static node* double_rotate_with_left(node*);
static node* double_rotate_with_right(node*);
static void preorder(avl_tree* tree, node* n, void (*print_func)(const void* val));


// Library functions

avl_tree* avl_new_tree(cmp_t cmp) {
    avl_tree* tree = (avl_tree*)calloc(1, sizeof(avl_tree));
    tree->cmp = cmp;
    return tree;
}

void* avl_find(avl_tree* tree, void* val) {
    return find_h(tree, tree->head, val);
}

void avl_free_tree(avl_tree* tree) {
    free_nodes(tree->head);
    free(tree);
}

/*int main() {
    std::vector<std::array<double, 3>> r;
    for (auto i = 0u; i <= MAXRAY; ++i)
        r.push_back(std::array<double, 3>{ x, y, z });
}*/

void avl_insert(avl_tree* tree, void* val) {
    if (!tree->head) {
        tree->head = (node*)calloc(1, sizeof(node));
        tree->head->data = val;
        return;
    }
    tree->head = insert_h(tree, tree->head, val);
}

void avl_remove(avl_tree* tree, void* val) {
    tree->head = remove_h(tree, tree->head, val);
}

void avl_preorder(avl_tree* tree, void (*print_func)(const void* val)) {
    preorder(tree, tree->head, print_func);
}

// Library helper functions

static void preorder(avl_tree* tree, node* n, void (*print_func)(const void* val)) {
    if (n) {
        print_func(n->data);
        preorder(tree, n->left, print_func);
        preorder(tree, n->right, print_func);
    }
}

static void free_nodes(node* tree) {
    if (!tree)
        return;
    if (tree->left)
        free_nodes(tree->left);
    if (tree->right)
        free_nodes(tree->right);
    free(tree);
}

static node* find_h(avl_tree* tree, node* n, void* val) {
    if (n == NULL)
        return NULL;
    int cmp_val = tree->cmp(tree->head->data, val);
    if (cmp_val > 0)
        return find_h(tree, n->right, val);
    if (cmp_val < 0)
        return find_h(tree, n->left, val);
    return n;
}

static node* insert_h(avl_tree* tree, node* n, void* val) {
    if (n == NULL) {
        n = (node*)calloc(1, sizeof(node));
        n->data = val;
    }
    else {
        int cmp_val = tree->cmp(tree->head->data, val);
        // cmp_val > 0 <=> val > tree->head->data
        if (cmp_val > 0) {
            n->right = insert_h(tree, n->right, val);
            if (balance_factor(n) == -2) {
                if (tree->cmp(n->right->data, val) > 0) {
                    // val > n->right->data
                    n = single_rotate_with_right(n);
                }
                else {
                    n = double_rotate_with_right(n);
                }
            }
        }
        else if (cmp_val < 0) {
            n->left = insert_h(tree, n->left, val);
            if (balance_factor(n) == 2) {
                if (tree->cmp(n->left->data, val) < 0) {
                    // val < n->left->data
                    n = single_rotate_with_left(n);
                }
                else {
                    n = double_rotate_with_left(n);
                }
            }
        }
    }
    n->height = height(n);
    return n;
}

static node* remove_h(avl_tree* tree, node* n, void* val) {
    if (n == NULL)
        return NULL;
    node* p;
    int cmp_val = tree->cmp(n->data, val);
    if (cmp_val > 0) {
        n->right = remove_h(tree, n->right, val);
        if (balance_factor(n) == 2) {
            if (balance_factor(n->left) >= 0) {
                n = single_rotate_with_left(n);
            }
            else {
                n = double_rotate_with_left(n);
            }
        }
    }
    else if (cmp_val < 0) {
        n->left = remove_h(tree, n->left, val);
        if (balance_factor(n) == -2) {
            if (balance_factor(n->right) <= 0) {
                n = single_rotate_with_right(n);
            }
            else {
                n = double_rotate_with_right(n);
            }
        }
    }
    else {
        // Data to be deleted is found
        if (n->right != NULL) {
            p = n->right;
            while (p->left != NULL) p = p->left;
            n->data = p->data;
            n->right = remove_h(tree, n->right, p->data);
            if (balance_factor(n) == 2) {
                if (balance_factor(n->left) >= 0) {
                    n = single_rotate_with_left(n);
                }
                else {
                    n = double_rotate_with_left(n);
                }
            }
        }
        else {
            return n->left;
        }
    }
    n->height = height(n);
    return n;
}
// Helper functions

static int height(node* n) {
    int rh, lh;
    if (n == NULL)
        return 0;
    lh = n->left == NULL ? 0 : 1 + n->left->height;
    rh = n->right == NULL ? 0 : 1 + n->right->height;
    return max(lh, rh);
}

static int balance_factor(node* n) {
    int rh, lh;
    if (n == NULL)
        return 0;
    lh = n->left == NULL ? 0 : 1 + n->left->height;
    rh = n->right == NULL ? 0 : 1 + n->right->height;
    return lh - rh;
}

static node* single_rotate_with_left(node* k2)
{
    node* k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k1->height = height(k1);
    k2->height = height(k2);
    return k1; /* new root */
}

static node* single_rotate_with_right(node* k1)
{
    node* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = height(k1);
    k2->height = height(k2);
    return k2;  /* New root */
}

static node* double_rotate_with_left(node* k3)
{
    k3->left = single_rotate_with_right(k3->left);
    return single_rotate_with_left(k3);
}

static node* double_rotate_with_right(node* k1)
{
    k1->right = single_rotate_with_left(k1->right);
    return single_rotate_with_right(k1);
}

static int max(int a, int b) {
    return a > b ? a : b;
}

static void* xalloc(size_t size) {
    void* mem = calloc(1, size);
    if (mem)
        return mem;
    exit(1);
}

// Example comparator function
static int int_cmp(int* o1, int* o2) {
    return *o2 - *o1;
}