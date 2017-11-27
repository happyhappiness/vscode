static int cj_read(user_data_t *ud) /* {{{ */
{
  cj_t *db;

  if ((ud == NULL) || (ud->data == NULL)) {
    ERROR("curl_json plugin: cj_read: Invalid user data.");
    return (-1);
  }

  db = (cj_t *)ud->data;

  db->depth = 0;
  memset(&db->state, 0, sizeof(db->state));
  db->state[db->depth].tree = db->tree;
  db->key = NULL;

  return cj_perform(db);
}