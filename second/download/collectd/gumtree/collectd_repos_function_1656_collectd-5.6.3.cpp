static int cc_handle_bool(struct oconfig_item_s *item, int *dest) {
  if (item->values_num != 1) {
    return -ENOTSUP;
  }

  if (item->values[0].type != OCONFIG_TYPE_BOOLEAN) {
    return -ENOTSUP;
  }

  *dest = (item->values[0].value.boolean) ? 1 : 0;
  return 0;
}