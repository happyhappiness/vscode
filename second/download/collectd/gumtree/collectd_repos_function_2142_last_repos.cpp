static int wl_write_graphite(const data_set_t *ds, const value_list_t *vl) {
  char buffer[WL_BUF_SIZE] = {0};
  int status;

  if (0 != strcmp(ds->type, vl->type)) {
    ERROR("write_log plugin: DS type does not match value list type");
    return -1;
  }

  status = format_graphite(buffer, sizeof(buffer), ds, vl, NULL, NULL, '_', 0);
  if (status != 0) /* error message has been printed already. */
    return status;

  INFO("write_log values:\n%s", buffer);

  return 0;
}