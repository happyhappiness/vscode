static int cj_read(user_data_t *ud) /* {{{ */
{
  cj_t *db;

  if ((ud == NULL) || (ud->data == NULL)) {
    ERROR("curl_json plugin: cj_read: Invalid user data.");
    return -1;
  }

  db = (cj_t *)ud->data;

  db->depth = 0;
  memset(&db->state, 0, sizeof(db->state));

  /* This is not a compound literal because EPEL6's GCC is not cool enough to
   * handle anonymous unions within compound literals. */
  cj_tree_entry_t root = {0};
  root.type = TREE;
  root.tree = db->tree;
  db->state[0].entry = &root;

  int status = cj_perform(db);

  db->state[0].entry = NULL;

  return status;
}