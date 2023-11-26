
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *left;
    int data;
    int height;
    struct node *right;
};

struct AVL {
    struct node *root;
};

int calheight(struct node *p);
int bf(struct node *n);
struct node *llrotation(struct node *n);
struct node *rrrotation(struct node *n);
struct node *rlrotation(struct node *n);
struct node *lrrotation(struct node *n);
struct node *insert(struct node *r, int data);
void levelorder_newline(struct AVL *avl);
void levelorder_newline_util(struct node *v);
struct node *deleteNode(struct node *p, int data);
struct node *inpre(struct node *p);
struct node *insuc(struct node *p);

int main() {
    struct AVL b;
    int c, x;

    b.root = NULL;

    do {
        printf("\n1. Display levelorder on newline");
        printf("\n2. Insert");
        printf("\n3. Delete\n");
        printf("\n0. Exit\n");
        printf("\nChoice: ");

        scanf("%d", &c);

        switch (c) {
        case 1:
            levelorder_newline(&b);
            break;

        case 2:
            printf("\nEnter no. ");
            scanf("%d", &x);
            b.root = insert(b.root, x);
            break;

        case 3:
            printf("\nWhat to delete? ");
            scanf("%d", &x);
            b.root = deleteNode(b.root, x);
            break;

        case 0:
            break;
        }

    } while (c != 0);

    return 0;
}

int calheight(struct node *p) {
    if (p == NULL) {
        return 0;
    }

    if (p->left && p->right) {
        return (p->left->height < p->right->height) ? p->right->height + 1 : p->left->height + 1;
    } else if (p->left && p->right == NULL) {
        return p->left->height + 1;
    } else if (p->left == NULL && p->right) {
        return p->right->height + 1;
    }

    return 0;
}

int bf(struct node *n) {
    if (n == NULL) {
        return 0;
    }

    if (n->left && n->right) {
        return n->left->height - n->right->height;
    } else if (n->left && n->right == NULL) {
        return n->left->height;
    } else if (n->left == NULL && n->right) {
        return -n->right->height;
    }

    return 0;
}

struct node *llrotation(struct node *n) {
    struct node *p;
    struct node *tp;
    p = n;
    tp = p->left;

    p->left = tp->right;
    tp->right = p;

    return tp;
}

struct node *rrrotation(struct node *n) {
    struct node *p;
    struct node *tp;
    p = n;
    tp = p->right;

    p->right = tp->left;
    tp->left = p;

    return tp;
}

struct node *rlrotation(struct node *n) {
    struct node *p;
    struct node *tp;
    struct node *tp2;
    p = n;
    tp = p->right;
    tp2 = p->right->left;

    p->right = tp2->left;
    tp->left = tp2->right;
    tp2->left = p;
    tp2->right = tp;

    return tp2;
}

struct node *lrrotation(struct node *n) {
    struct node *p;
    struct node *tp;
    struct node *tp2;
    p = n;
    tp = p->left;
    tp2 = p->left->right;

    p->left = tp2->right;
    tp->right = tp2->left;
    tp2->right = p;
    tp2->left = tp;

    return tp2;
}

struct node *insert(struct node *r, int data) {
    if (r == NULL) {
        struct node *n;
        n = (struct node *)malloc(sizeof(struct node));
        n->data = data;
        r = n;
        r->left = r->right = NULL;
        r->height = 1;
        return r;
    } else {
        if (data < r->data)
            r->left = insert(r->left, data);
        else
            r->right = insert(r->right, data);
    }

    r->height = calheight(r);

    if (bf(r) == 2 && bf(r->left) == 1) {
        r = llrotation(r);
    } else if (bf(r) == -2 && bf(r->right) == -1) {
        r = rrrotation(r);
    } else if (bf(r) == -2 && bf(r->right) == 1) {
        r = rlrotation(r);
    } else if (bf(r) == 2

 && bf(r->left) == -1) {
        r = lrrotation(r);
    }

    return r;
}

void levelorder_newline(struct AVL *avl) {
    if (avl->root == NULL) {
        printf("\nEmpty tree\n");
        return;
    }
    levelorder_newline_util(avl->root);
}

void levelorder_newline_util(struct node *v) {
    if (v == NULL) {
        return;
    }

    struct node *cur;
    struct node *q[v->height];
    int front = -1, rear = -1;

    q[++rear] = v;
    q[++rear] = NULL;

    while (front != rear) {
        cur = q[++front];
        if (cur == NULL && rear != front) {
            printf("\n");
            q[++rear] = NULL;
            continue;
        }
        if (cur != NULL) {
            printf(" %d", cur->data);

            if (cur->left != NULL) {
                q[++rear] = cur->left;
            }
            if (cur->right != NULL) {
                q[++rear] = cur->right;
            }
        }
    }
}

struct node *deleteNode(struct node *p, int data) {
    if (p == NULL) {
        return NULL;
    }

    if (p->left == NULL && p->right == NULL) {
        free(p);
        return NULL;
    }

    struct node *t;
    struct node *q;
    if (p->data < data) {
        p->right = deleteNode(p->right, data);
    } else if (p->data > data) {
        p->left = deleteNode(p->left, data);
    } else {
        if (p->left != NULL) {
            q = inpre(p->left);
            p->data = q->data;
            p->left = deleteNode(p->left, q->data);
        } else {
            q = insuc(p->right);
            p->data = q->data;
            p->right = deleteNode(p->right, q->data);
        }
    }

    if (bf(p) == 2 && bf(p->left) == 1) {
        p = llrotation(p);
    } else if (bf(p) == 2 && bf(p->left) == -1) {
        p = lrrotation(p);
    } else if (bf(p) == 2 && bf(p->left) == 0) {
        p = llrotation(p);
    } else if (bf(p) == -2 && bf(p->right) == -1) {
        p = rrrotation(p);
    } else if (bf(p) == -2 && bf(p->right) == 1) {
        p = rlrotation(p);
    } else if (bf(p) == -2 && bf(p->right) == 0) {
        p = llrotation(p);
    }

    return p;
}

struct node *inpre(struct node *p) {
    while (p->right != NULL)
        p = p->right;
    return p;
}

struct node *insuc(struct node *p) {
    while (p->left != NULL)
        p = p->left;

    return p;
}