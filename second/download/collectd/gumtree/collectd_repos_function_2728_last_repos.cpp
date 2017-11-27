static c_avl_node_t *c_avl_node_prev(c_avl_node_t *n) {
  c_avl_node_t *r; /* return node */

  if (n == NULL) {
    return NULL;
  }

  /* If we can't descent any further, we have to backtrack to the first
   * parent that's smaller than we, i. e. who's _right_ child we are. */
  if (n->left == NULL) {
    r = n->parent;
    while ((r != NULL) && (r->parent != NULL)) {
      if (r->right == n)
        break;
      n = r;
      r = n->parent;
    }

    /* n->left == NULL && r == NULL => t is root and has no next
     * r->right != n => r->left = n => r->parent == NULL */
    if ((r == NULL) || (r->right != n)) {
      assert((r == NULL) || (r->parent == NULL));
      return NULL;
    } else {
      assert(r->right == n);
      return r;
    }
  } else {
    r = n->left;
    while (r->right != NULL)
      r = r->right;
  }

  return r;
}