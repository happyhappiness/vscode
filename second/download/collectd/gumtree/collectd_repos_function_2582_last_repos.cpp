int lcc_identifier_to_string(lcc_connection_t *c, /* {{{ */
                             char *string, size_t string_size,
                             const lcc_identifier_t *ident) {
  if ((string == NULL) || (string_size < 6) || (ident == NULL)) {
    lcc_set_errno(c, EINVAL);
    return -1;
  }

  if (ident->plugin_instance[0] == 0) {
    if (ident->type_instance[0] == 0)
      snprintf(string, string_size, "%s/%s/%s", ident->host, ident->plugin,
               ident->type);
    else
      snprintf(string, string_size, "%s/%s/%s-%s", ident->host, ident->plugin,
               ident->type, ident->type_instance);
  } else {
    if (ident->type_instance[0] == 0)
      snprintf(string, string_size, "%s/%s-%s/%s", ident->host, ident->plugin,
               ident->plugin_instance, ident->type);
    else
      snprintf(string, string_size, "%s/%s-%s/%s-%s", ident->host,
               ident->plugin, ident->plugin_instance, ident->type,
               ident->type_instance);
  }

  string[string_size - 1] = 0;
  return 0;
}