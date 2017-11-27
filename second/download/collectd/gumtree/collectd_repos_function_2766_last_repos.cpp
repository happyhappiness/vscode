static int dispatch_value_plugin(const char *plugin, oconfig_item_t *ci) {
  char buffer[4096];
  char *buffer_ptr;
  int buffer_free;

  buffer_ptr = buffer;
  buffer_free = sizeof(buffer);

  for (int i = 0; i < ci->values_num; i++) {
    int status = -1;

    if (ci->values[i].type == OCONFIG_TYPE_STRING)
      status =
          snprintf(buffer_ptr, buffer_free, " %s", ci->values[i].value.string);
    else if (ci->values[i].type == OCONFIG_TYPE_NUMBER)
      status =
          snprintf(buffer_ptr, buffer_free, " %lf", ci->values[i].value.number);
    else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN)
      status = snprintf(buffer_ptr, buffer_free, " %s",
                        ci->values[i].value.boolean ? "true" : "false");

    if ((status < 0) || (status >= buffer_free))
      return -1;
    buffer_free -= status;
    buffer_ptr += status;
  }
  /* skip the initial space */
  buffer_ptr = buffer + 1;

  return cf_dispatch(plugin, ci->key, buffer_ptr);
}