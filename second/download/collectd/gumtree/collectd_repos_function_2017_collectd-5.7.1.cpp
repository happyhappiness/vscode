static int wl_config(oconfig_item_t *ci) /* {{{ */
{
  _Bool format_seen = 0;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Format", child->key) == 0) {
      char str[16];

      if (cf_util_get_string_buffer(child, str, sizeof(str)) != 0)
        continue;

      if (format_seen) {
        WARNING("write_log plugin: Redefining option `%s'.", child->key);
      }
      format_seen = 1;

      if (strcasecmp("Graphite", str) == 0)
        wl_format = WL_FORMAT_GRAPHITE;
      else if (strcasecmp("JSON", str) == 0)
        wl_format = WL_FORMAT_JSON;
      else {
        ERROR("write_log plugin: Unknown format `%s' for option `%s'.", str,
              child->key);
        return (-EINVAL);
      }
    } else {
      ERROR("write_log plugin: Invalid configuration option: `%s'.",
            child->key);
      return (-EINVAL);
    }
  }

  return (0);
}