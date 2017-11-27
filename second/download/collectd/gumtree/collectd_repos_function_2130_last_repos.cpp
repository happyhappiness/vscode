int udb_query_pick_from_list_by_name(const char *name, /* {{{ */
                                     udb_query_t **src_list,
                                     size_t src_list_len,
                                     udb_query_t ***dst_list,
                                     size_t *dst_list_len) {
  int num_added;

  if ((name == NULL) || (src_list == NULL) || (dst_list == NULL) ||
      (dst_list_len == NULL)) {
    ERROR("db query utils: udb_query_pick_from_list_by_name: "
          "Invalid argument.");
    return -EINVAL;
  }

  num_added = 0;
  for (size_t i = 0; i < src_list_len; i++) {
    udb_query_t **tmp_list;
    size_t tmp_list_len;

    if (strcasecmp(name, src_list[i]->name) != 0)
      continue;

    tmp_list_len = *dst_list_len;
    tmp_list = realloc(*dst_list, (tmp_list_len + 1) * sizeof(udb_query_t *));
    if (tmp_list == NULL) {
      ERROR("db query utils: realloc failed.");
      return -ENOMEM;
    }

    tmp_list[tmp_list_len] = src_list[i];
    tmp_list_len++;

    *dst_list = tmp_list;
    *dst_list_len = tmp_list_len;

    num_added++;
  } /* for (i = 0; i < src_list_len; i++) */

  if (num_added <= 0) {
    ERROR("db query utils: Cannot find query `%s'. Make sure the <Query> "
          "block is above the database definition!",
          name);
    return -ENOENT;
  } else {
    DEBUG("db query utils: Added %i versions of query `%s'.", num_added, name);
  }

  return 0;
}