static void free_node(c_avl_node_t *n) {
  if (n == NULL)
    return;

  if (n->left != NULL)
    free_node(n->left);
  if (n->right != NULL)
    free_node(n->right);

  free(n);
}