int udb_query_pick_from_list(oconfig_item_t *ci, /* {{{ */
                             udb_query_t **src_list, size_t src_list_len,
                             udb_query_t ***dst_list, size_t *dst_list_len) {
  const char *name;

  if ((ci == NULL) || (src_list == NULL) || (dst_list == NULL) ||
      (dst_list_len == NULL)) {
    ERROR("db query utils: udb_query_pick_from_list: "
          "Invalid argument.");
    return (-EINVAL);
  }

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    ERROR("db query utils: The `%s' config option "
          "needs exactly one string argument.",
          ci->key);
    return (-1);
  }
  name = ci->values[0].value.string;

  return (udb_query_pick_from_list_by_name(name, src_list, src_list_len,
                                           dst_list, dst_list_len));
}