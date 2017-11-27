static void cj_advance_array(cj_t *db) {
  if (!db->state[db->depth].in_array)
    return;

  db->state[db->depth].index++;

  char name[DATA_MAX_NAME_LEN];
  snprintf(name, sizeof(name), "%d", db->state[db->depth].index);
  cj_load_key(db, name);
}