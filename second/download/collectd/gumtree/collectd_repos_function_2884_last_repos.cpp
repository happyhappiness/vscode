static char *plugin_flush_callback_name(const char *name) {
  const char *flush_prefix = "flush/";
  size_t prefix_size;
  char *flush_name;
  size_t name_size;

  prefix_size = strlen(flush_prefix);
  name_size = strlen(name);

  flush_name = malloc(name_size + prefix_size + 1);
  if (flush_name == NULL) {
    ERROR("plugin_flush_callback_name: malloc failed.");
    return NULL;
  }

  sstrncpy(flush_name, flush_prefix, prefix_size + 1);
  sstrncpy(flush_name + prefix_size, name, name_size + 1);

  return flush_name;
}