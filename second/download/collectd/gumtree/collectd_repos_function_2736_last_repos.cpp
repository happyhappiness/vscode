c_avl_iterator_t *c_avl_get_iterator(c_avl_tree_t *t) {
  c_avl_iterator_t *iter;

  if (t == NULL)
    return NULL;

  iter = calloc(1, sizeof(*iter));
  if (iter == NULL)
    return NULL;
  iter->tree = t;

  return iter;
}