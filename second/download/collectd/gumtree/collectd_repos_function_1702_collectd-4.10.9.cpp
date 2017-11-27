static int cj_cb_map_key (void *ctx, const unsigned char *val,
    yajl_len_t len)
{
  cj_t *db = (cj_t *)ctx;
  c_avl_tree_t *tree;

  tree = db->state[db->depth-1].tree;

  if (tree != NULL)
  {
    cj_key_t *value;
    char *name;

    name = db->state[db->depth].name;
    len = COUCH_MIN(len, sizeof (db->state[db->depth].name)-1);
    sstrncpy (name, (char *)val, len+1);

    if (c_avl_get (tree, name, (void *) &value) == 0)
      db->state[db->depth].key = value;
    else if (c_avl_get (tree, CJ_ANY, (void *) &value) == 0)
      db->state[db->depth].key = value;
    else
      db->state[db->depth].key = NULL;
  }

  return (CJ_CB_CONTINUE);
}