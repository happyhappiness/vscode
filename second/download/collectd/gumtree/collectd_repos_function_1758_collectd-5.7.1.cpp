static int cc_handle_str(struct oconfig_item_s *item, char *dest,
                         int dest_len) {
  const char *val;
  if (item->values_num != 1) {
    return -ENOTSUP;
  }
  if (item->values[0].type != OCONFIG_TYPE_STRING) {
    return -ENOTSUP;
  }
  val = item->values[0].value.string;
  if (snprintf(dest, dest_len, "%s", val) > (dest_len - 1)) {
    ERROR("ceph plugin: configuration parameter '%s' is too long.\n",
          item->key);
    return -ENAMETOOLONG;
  }
  return 0;
}