static int cj_append_key(cj_t *db, cj_key_t *key) { /* {{{ */
  if (db->tree == NULL)
    db->tree = cj_avl_create();

  c_avl_tree_t *tree = db->tree;

  char const *start = key->path;
  if (*start == '/')
    ++start;

  char const *end;
  while ((end = strchr(start, '/')) != NULL) {
    char name[PATH_MAX];

    size_t len = end - start;
    if (len == 0)
      break;

    len = COUCH_MIN(len, sizeof(name) - 1);
    sstrncpy(name, start, len + 1);

    cj_tree_entry_t *e;
    if (c_avl_get(tree, name, (void *)&e) != 0) {
      e = calloc(1, sizeof(*e));
      if (e == NULL)
        return ENOMEM;
      e->type = TREE;
      e->tree = cj_avl_create();

      c_avl_insert(tree, strdup(name), e);
    }

    if (e->type != TREE)
      return EINVAL;

    tree = e->tree;
    start = end + 1;
  }

  if (strlen(start) == 0) {
    ERROR("curl_json plugin: invalid key: %s", key->path);
    return -1;
  }

  cj_tree_entry_t *e = calloc(1, sizeof(*e));
  if (e == NULL)
    return ENOMEM;
  e->type = KEY;
  e->key = key;

  c_avl_insert(tree, strdup(start), e);
  return 0;
}