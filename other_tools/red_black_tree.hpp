#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP
# include <iostream>

namespace ft
{
    template <class value_type>
    struct Node
    {
        Node(const value_type &p = value_type())
         : begin(NULL), left(NULL), right(NULL), parent(0), NIL(0), color(0), pair(new value_type(p)) {};

        ~Node()
        {
            delete pair;
        }

        struct Node *begin;
        struct Node *left;
        struct Node *right;
        struct Node *parent;
        bool color;
        bool NIL;
        value_type *pair;
    };

    template <class value_type>
    class Tree
    {
    public:
        Node<value_type> sentinel;
        Node<value_type> *root;
        size_t amount_node;
        Tree() : amount_node(0)
        {
            sentinel.begin = &sentinel;
            sentinel.left = &sentinel;
            sentinel.right = &sentinel;
            sentinel.parent = 0;
            sentinel.color = 0;
            sentinel.NIL = true;
            root = &sentinel;
        }

        Tree(Tree<value_type> &other) : amount_node(0)
        {
            sentinel.begin = &sentinel;
            sentinel.left = &sentinel;
            sentinel.right = &sentinel;
            sentinel.parent = 0;
            sentinel.color = 0;
            sentinel.NIL = true;
            root = &sentinel;
        }

        Tree& operator=(const Tree<value_type> &other)
        {
            if(this != &other)
            {
                root = other.root;
                sentinel = other.sentinel;
                amount_node = other.amount_node;
            }
            return *this;
        }

        void rotateLeft(Node<value_type> *x)
        {
            Node<value_type> *y = x->right;

            x->right = y->left;
            if (y->left != 0)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent)
            {
                if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
            }
            else
                root = y;
            y->left = x;
            x->parent = y;
        }
        void rotateRight(Node<value_type> *x)
        {
            Node<value_type> *y = x->left;

            x->left = y->right;
            if (!y->right->NIL)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent) {
                if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
            } else {
                root = y;
            }
            y->right = x;
            x->parent = y;
        }

        void balance_insert(Node<value_type> *x)
        {
            while (x != root && x->parent->color == 1)
            {
                if (x->parent == x->parent->parent->left)
                {
                    Node<value_type> *y = x->parent->parent->right;
                    if (y->color == 1)
                    {
                        x->parent->color = 0;
                        y->color = 0;
                        x->parent->parent->color = 1;
                        x = x->parent->parent;
                    }
                    else
                    {
                        if(x == x->parent->right)
                        {
                            x = x->parent;
                            rotateLeft(x);
                        }
                        x->parent->color = 0;
                        x->parent->parent->color = 1;
                        rotateRight(x->parent->parent);
                    }
                }
                else
                {
                    Node<value_type> *y = x->parent->parent->left;
                    if (y->color == 1)
                    {
                        x->parent->color =0;
                        y->color = 0;
                        x->parent->parent->color = 1;
                        x = x->parent->parent;
                    }
                    else
                    {
                        if (x == x->parent->left)
                        {
                            x = x->parent;
                            rotateRight(x);
                        }
                        x->parent->color = 0;
                        x->parent->parent->color = 1;
                        rotateLeft(x->parent->parent);
                    }
                }
            }
            root->color = 0;
        }

        void balance_delete(Node<value_type> *x)
        {
            while (x != root && x->color == 0)
            {
                if (x == x->parent->left)
                {
                    Node<value_type> *brother = x->parent->right;
                    if (brother->color == 1)
                    {
                        brother->color = 0;
                        x->parent->color = 1;
                        rotateLeft(brother->parent);
                        brother = x->parent->right;
                    }
                    if (brother->left->color == 0 && brother->right->color == 0)
                    {
                        brother->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (brother->right->color == 0)
                        {
                            brother->left->color = 0;
                            brother->color = 1;
                            rotateRight(brother);
                            brother = x->parent->right;
                        }
                        brother->color = x->parent->color;
                        x->parent->color = 0;
                        brother->right->color = 0;
                        rotateLeft(brother->parent);
                        x = root;
                    }
                }
                else
                {
                    Node<value_type> *brother = x->parent->left;
                    if (brother->color == 1)
                    {
                        brother->color = 0;
                        x->parent->color = 1;
                        rotateRight(x->parent);
                        brother = x->parent;
                    }
                    if (brother->right->color == 0 && brother->left->color == 0)
                    {
                        brother->color = 1;
                        x = x->parent;
                    }
                    else
                    {
                        if (brother->left->color == 0)
                        {
                            brother->rihgt->color = 0;
                            brother->color = 1;
                            rotateLeft(brother);
                            brother = x->parent->left;
                        }
                        brother->color = x->parent->color;
                        x->parent->color = 0;
                        brother->left->color = 0;
                        x = root;
                    }
                }
            }
            x->color = 0;
        }

        int deleteNode(Node<value_type> *del)
        {
            Node<value_type> *x, *y;

            if (!del || del->NIL)
                return 0;
            if (del->left->NIL || del->right->NIL)
                y = del;
            else
            {
                y = del->right;
                while (!y->left->NIL)
                    y = y->left;
            }
            if (!y->left->NIL)
                x = y->left;
            else
                x = y->right;
            x->parent = y->parent;
            if (y->parent)
            {
                if (y == y->parent->left)
                    y->parent->left = x;
                else
                    y->parent->rihgt = x;
            }
            else
                root = x;
            if (y != del)
            {
                delete del->pair;
                value_type *n = new value_type(*y->pair);
                del->pair = n;
            }
            if (y->color == 0)
                balance_delete(x);
            amount_node--;
            delete y;
            return 1;
        }

        Node<value_type> *min_node()
        {
            Node<value_type> *tmp = root;
            while (!tmp->left->NIL)
                tmp = tmp->left;
            return tmp;
        }
        Node<value_type> *max_node()
        {
            Node<value_type> *tmp = root;
            while (!tmp->right->NIL)
                tmp = tmp->right;
            return tmp;
        }
        Node<value_type> *getEnd()
        {
            Node<value_type> *tmp = root;
            while (!tmp->right->NIL)
                tmp = tmp->right;
            return tmp->right;
        }
    };
}

#endif