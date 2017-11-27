static void fbh_free_tree (c_avl_tree_t *tree) /* {{{ */
{
  int status;

  if (tree == NULL)
    return;

  while (42)
  {
    char *key = NULL;
    char *value = NULL;

    status = c_avl_pick (tree, (void *) &key, (void *) &value);
    if (status != 0)
      break;

    free (key);
    free (value);
  }

  c_avl_destroy (tree);
}