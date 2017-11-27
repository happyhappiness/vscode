static int cj_cb_map_key(void *ctx, unsigned char const *in_name,
                         yajl_len_t in_name_len) {
  cj_t *db = (cj_t *)ctx;
  c_avl_tree_t *tree;

  tree = db->state[db->depth - 1].tree;

  if (tree != NULL) {
    cj_key_t *value = NULL;
    char *name;
    size_t name_len;

    /* Create a null-terminated version of the name. */
    name = db->state[db->depth].name;
    name_len =
        COUCH_MIN((size_t)in_name_len, sizeof(db->state[db->depth].name) - 1);
    memcpy(name, in_name, name_len);
    name[name_len] = 0;

    if (c_avl_get(tree, name, (void *)&value) == 0) {
      if (CJ_IS_KEY((cj_key_t *)value)) {
        db->state[db->depth].key = value;
      } else {
        db->state[db->depth].tree = (c_avl_tree_t *)value;
      }
    } else if (c_avl_get(tree, CJ_ANY, (void *)&value) == 0)
      if (CJ_IS_KEY((cj_key_t *)value)) {
        db->state[db->depth].key = value;
      } else {
        db->state[db->depth].tree = (c_avl_tree_t *)value;
      }
    else
      db->state[db->depth].key = NULL;
  }

  return (CJ_CB_CONTINUE);
}