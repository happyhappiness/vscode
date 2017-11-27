static int wl_write_json(const data_set_t *ds, const value_list_t *vl) {
  char buffer[WL_BUF_SIZE] = {0};
  size_t bfree = sizeof(buffer);
  size_t bfill = 0;

  if (0 != strcmp(ds->type, vl->type)) {
    ERROR("write_log plugin: DS type does not match value list type");
    return -1;
  }

  format_json_initialize(buffer, &bfill, &bfree);
  format_json_value_list(buffer, &bfill, &bfree, ds, vl,
                         /* store rates = */ 0);
  format_json_finalize(buffer, &bfill, &bfree);

  INFO("write_log values:\n%s", buffer);

  return (0);
}