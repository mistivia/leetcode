#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// begin

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define VECTOR_DEF(T) \
    typedef struct { \
        T* buffer; \
        int size; \
        int cap; \
    } T##Vector; \
    \
    void T##Vector_init(T##Vector *self); \
    void T##Vector_push_back(T##Vector *self, T elem); \
    void T##Vector_insert_before(T##Vector *self, int n, T elem); \
    void T##Vector_pop(T##Vector *self); \
    bool T##Vector_empty(T##Vector *self); \
    void T##Vector_remove(T##Vector *self, size_t n); \
    size_t T##Vector_len(T##Vector *self); \
    T* T##Vector_begin(T##Vector *self); \
    T* T##Vector_last(T##Vector *self); \
    T* T##Vector_end(T##Vector *self); \
    T* T##Vector_ref(T##Vector *self, size_t n); \
    void T##Vector_swap(T##Vector *self, int i, int j); \
    T##Vector T##Vector_move(T##Vector *self); \
    void T##Vector_free(T##Vector *self);

#define VECTOR_IMPL(T) \
    void T##Vector_init(T##Vector *self) { \
        self->buffer = (T*)malloc(sizeof(T) * 16); \
        self->cap = 16; \
        self->size = 0; \
    } \
    \
    void T##Vector_push_back(T##Vector *self, T elem) { \
        if (self->size + 1 > self->cap) { \
            self->buffer = realloc(self->buffer, sizeof(T) * self->cap * 2); \
            self->cap *= 2; \
        } \
        self->buffer[self->size] = elem; \
        self->size += 1; \
    } \
    void T##Vector_insert_before(T##Vector *self, int n, T elem) { \
        if (n < 0 || n > self->size) { \
            return; \
        } \
        if (self->size + 1 > self->cap) { \
            self->buffer = malloc(sizeof(T) * self->cap * 2); \
            self->cap *= 2; \
        } \
        if (n != self->size) { \
            memmove(self->buffer + n + 1, \
                    self->buffer + n, \
                    sizeof(T) * (self->size - n)); \
            self->buffer[n] = elem; \
            self->size += 1; \
        } \
    } \
    void T##Vector_pop(T##Vector *self) { \
        self->size -= 1; \
    } \
    void T##Vector_remove(T##Vector *self, size_t n) { \
        if (n < 0 || n >= self->size) return; \
        memmove(self->buffer + n, \
                self->buffer + n + 1, \
                sizeof(T) * self->size - n - 1); \
        self->size -= 1; \
    } \
    T* T##Vector_begin(T##Vector *self) { return self->buffer; } \
    bool T##Vector_empty(T##Vector *self) { return self->size == 0; } \
    T* T##Vector_end(T##Vector *self) { return self->buffer + self->size; } \
    T* T##Vector_last(T##Vector *self) { return self->buffer + self->size - 1; } \
    T* T##Vector_ref(T##Vector *self, size_t n) { return self->buffer + n; } \
    void T##Vector_swap(T##Vector *self, int i, int j) { \
        T buf; \
        memcpy(&buf, self->buffer + i, sizeof(T)); \
        memcpy(self->buffer + i, self->buffer + j, sizeof(T)); \
        memcpy(self->buffer + j, &buf, sizeof(T)); \
    } \
    T##Vector T##Vector_move(T##Vector *self) { \
        T##Vector dup = *self; \
        self->buffer = NULL; \
        self->size = 0; \
        self->cap = 0; \
        return dup; \
    } \
    size_t T##Vector_len(T##Vector *self) { return self->size; } \
    void T##Vector_free(T##Vector *self) { free(self->buffer); }

typedef int Int;
VECTOR_DEF(Int);
VECTOR_IMPL(Int);

void inorderTraversalImpl(struct TreeNode* node, IntVector *vec) {
    if (node == NULL) return;
    inorderTraversalImpl(node->left, vec);
    IntVector_push_back(vec, node->val);
    inorderTraversalImpl(node->right, vec);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    IntVector vec;
    IntVector_init(&vec);
    inorderTraversalImpl(root, &vec);
    *returnSize = IntVector_len(&vec);
    return vec.buffer;
}

