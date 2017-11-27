int c_avl_remove(c_avl_tree_t *t, const void *key, void **rkey, void **rvalue) {
  c_avl_node_t *n;
  int status;

  assert(t != NULL);

  n = search(t, key);
  if (n == NULL)
    return -1;

  if (rkey != NULL)
    *rkey = n->key;
  if (rvalue != NULL)
    *rvalue = n->value;

  status = _remove(t, n);
  verify_tree(t->root);
  --t->size;
  return status;
}