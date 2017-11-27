static int cj_load_key(cj_t *db, char const *key) {
  if (db == NULL || key == NULL || db->depth <= 0)
    return EINVAL;

  sstrncpy(db->state[db->depth].name, key, sizeof(db->state[db->depth].name));

  c_avl_tree_t *tree = db->state[db->depth - 1].tree;
  if (tree == NULL) {
    return 0;
  }

  /* the parent has a key, so the tree pointer is invalid. */
  if (CJ_IS_KEY(db->state[db->depth - 1].key)) {
    return 0;
  }

  void *value = NULL;
  if (c_avl_get(tree, key, (void *)&value) == 0) {
    if (CJ_IS_KEY((cj_key_t *)value)) {
      db->state[db->depth].key = value;
    } else {
      db->state[db->depth].tree = value;
    }
  } else if (c_avl_get(tree, CJ_ANY, (void *)&value) == 0) {
    if (CJ_IS_KEY((cj_key_t *)value)) {
      db->state[db->depth].key = value;
    } else {
      db->state[db->depth].tree = value;
    }
  } else {
    db->state[db->depth].key = NULL;
  }

  return 0;
}