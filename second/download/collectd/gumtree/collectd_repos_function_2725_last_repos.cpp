static c_avl_node_t *rotate_right_left(c_avl_tree_t *t, c_avl_node_t *x) {
  rotate_right(t, x->right);
  return rotate_left(t, x);
}