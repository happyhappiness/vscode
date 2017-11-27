static void cj_tree_free (c_avl_tree_t *tree) /* {{{ */
{
  char *name;
  void *value;

  while (c_avl_pick (tree, (void *) &name, (void *) &value) == 0)
  {
    cj_key_t *key = (cj_key_t *)value;

    if (CJ_IS_KEY(key))
      cj_key_free (key);
    else
      cj_tree_free ((c_avl_tree_t *)value);

    sfree (name);
  }

  c_avl_destroy (tree);
}