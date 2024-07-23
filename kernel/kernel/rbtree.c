#include <kernel/rbtree.h>
#include <stdlib.h>

static void rb_rotate_left(rb_tree_t *tree, rb_node_t *node) {
    rb_node_t *right = node->right;
    node->right = right->left;
    if (right->left)
        right->left->parent = node;
    right->parent = node->parent;
    if (!node->parent)
        tree->root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

static void rb_rotate_right(rb_tree_t *tree, rb_node_t *node) {
    rb_node_t *left = node->left;
    node->left = left->right;
    if (left->right)
        left->right->parent = node;
    left->parent = node->parent;
    if (!node->parent)
        tree->root = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

static void rb_fix_insertion(rb_tree_t *tree, rb_node_t *node) {
    while (node != tree->root && node->parent->is_red) {
        if (node->parent == node->parent->parent->left) {
            rb_node_t *uncle = node->parent->parent->right;
            if (uncle && uncle->is_red) {
                node->parent->is_red = false;
                uncle->is_red = false;
                node->parent->parent->is_red = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rb_rotate_left(tree, node);
                }
                node->parent->is_red = false;
                node->parent->parent->is_red = true;
                rb_rotate_right(tree, node->parent->parent);
            }
        } else {
            rb_node_t *uncle = node->parent->parent->left;
            if (uncle && uncle->is_red) {
                node->parent->is_red = false;
                uncle->is_red = false;
                node->parent->parent->is_red = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rb_rotate_right(tree, node);
                }
                node->parent->is_red = false;
                node->parent->parent->is_red = true;
                rb_rotate_left(tree, node->parent->parent);
            }
        }
    }
    tree->root->is_red = false;
}

void rb_init(rb_tree_t *tree) {
    tree->root = NULL;
}

void rb_insert(rb_tree_t *tree, uint64_t key, void *value) {
    rb_node_t *node = malloc(sizeof(rb_node_t));
    node->key = key;
    node->value = value;
    node->left = node->right = NULL;
    node->is_red = true;

    rb_node_t *parent = NULL;
    rb_node_t *current = tree->root;
    while (current) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    node->parent = parent;
    if (!parent)
        tree->root = node;
    else if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;

    rb_fix_insertion(tree, node);
}

void *rb_find(rb_tree_t *tree, uint64_t key) {
    rb_node_t *node = tree->root;
    while (node) {
        if (key == node->key)
            return node->value;
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL;
}

rb_node_t *rb_first(rb_tree_t *tree) {
    rb_node_t *node = tree->root;
    if (!node)
        return NULL;
    while (node->left)
        node = node->left;
    return node;
}

rb_node_t *rb_next(rb_node_t *node) {
    if (node->right) {
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }
    rb_node_t *parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Note: will implement rb_delete later if needed