int c_avl_pick(c_avl_tree_t *t, void **key, void **value) {
  c_avl_node_t *n;
  c_avl_node_t *p;

  if ((key == NULL) || (value == NULL))
    return (-1);
  if (t->root == NULL)
    return (-1);

  n = t->root;
  while ((n->left != NULL) || (n->right != NULL)) {
    if (n->left == NULL) {
      n = n->right;
      continue;
    } else if (n->right == NULL) {
      n = n->left;
      continue;
    }

    if (n->left->height > n->right->height)
      n = n->left;
    else
      n = n->right;
  }

  p = n->parent;
  if (p == NULL)
    t->root = NULL;
  else if (p->left == n)
    p->left = NULL;
  else
    p->right = NULL;

  *key = n->key;
  *value = n->value;

  free_node(n);
  --t->size;
  rebalance(t, p);

  return (0);
}