static int calc_height(c_avl_node_t *n) {
  int height_left;
  int height_right;

  if (n == NULL)
    return 0;

  height_left = (n->left == NULL) ? 0 : n->left->height;
  height_right = (n->right == NULL) ? 0 : n->right->height;

  return ((height_left > height_right) ? height_left : height_right) + 1;
}