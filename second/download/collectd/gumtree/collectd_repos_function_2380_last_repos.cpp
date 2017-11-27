static int cj_load_key(cj_t *db, char const *key) {
  if (db == NULL || key == NULL || db->depth <= 0)
    return EINVAL;

  sstrncpy(db->state[db->depth].name, key, sizeof(db->state[db->depth].name));

  if (db->state[db->depth - 1].entry == NULL ||
      db->state[db->depth - 1].entry->type != TREE) {
    return 0;
  }

  c_avl_tree_t *tree = db->state[db->depth - 1].entry->tree;
  cj_tree_entry_t *e = NULL;

  if (c_avl_get(tree, key, (void *)&e) == 0) {
    db->state[db->depth].entry = e;
  } else if (c_avl_get(tree, CJ_ANY, (void *)&e) == 0) {
    db->state[db->depth].entry = e;
  } else {
    db->state[db->depth].entry = NULL;
  }

  return 0;
}