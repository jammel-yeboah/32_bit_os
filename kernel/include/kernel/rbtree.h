#ifndef _KERNEL_RBTREE_H
#define _KERNEL_RBTREE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct rb_node {
    struct rb_node *parent;
    struct rb_node *left;
    struct rb_node *right;
    uint64_t key;
    void *value;
    bool is_red;
} rb_node_t;

typedef struct {
    rb_node_t *root;
} rb_tree_t;

void rb_init(rb_tree_t *tree);
void rb_insert(rb_tree_t *tree, uint64_t key, void *value);
void *rb_find(rb_tree_t *tree, uint64_t key);
void rb_delete(rb_tree_t *tree, uint64_t key);
rb_node_t *rb_first(rb_tree_t *tree);
rb_node_t *rb_next(rb_node_t *node);

#endif