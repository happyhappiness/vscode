static void cj_tree_free(c_avl_tree_t *tree) /* {{{ */
{
  char *name;
  cj_tree_entry_t *e;

  while (c_avl_pick(tree, (void *)&name, (void *)&e) == 0) {
    sfree(name);

    if (e->type == KEY)
      cj_key_free(e->key);
    else
      cj_tree_free(e->tree);
    sfree(e);
  }

  c_avl_destroy(tree);
}