static c_avl_tree_t *cj_avl_create(void) {
  return c_avl_create((int (*)(const void *, const void *))strcmp);
}