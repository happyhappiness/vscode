static void cj_cb_inc_array_index(void *ctx, _Bool update_key) {
  cj_t *db = (cj_t *)ctx;

  if (!db->state[db->depth].in_array)
    return;

  db->state[db->depth].index++;

  if (update_key) {
    char name[DATA_MAX_NAME_LEN];

    ssnprintf(name, sizeof(name), "%d", db->state[db->depth].index - 1);

    cj_cb_map_key(ctx, (unsigned char *)name, (yajl_len_t)strlen(name));
  }
}