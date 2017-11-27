int c_avl_iterator_next(c_avl_iterator_t *iter, void **key, void **value) {
  c_avl_node_t *n;

  if ((iter == NULL) || (key == NULL) || (value == NULL))
    return (-1);

  if (iter->node == NULL) {
    for (n = iter->tree->root; n != NULL; n = n->left)
      if (n->left == NULL)
        break;
    iter->node = n;
  } else {
    n = c_avl_node_next(iter->node);
  }

  if (n == NULL)
    return (-1);

  iter->node = n;
  *key = n->key;
  *value = n->value;

  return (0);
}