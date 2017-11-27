int c_avl_size(c_avl_tree_t *t) {
  if (t == NULL)
    return (0);
  return (t->size);
}