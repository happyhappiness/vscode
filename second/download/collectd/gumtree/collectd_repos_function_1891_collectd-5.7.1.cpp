void cmd_destroy_flush(cmd_flush_t *flush) {
  if (flush == NULL)
    return;

  strarray_free(flush->plugins, flush->plugins_num);
  flush->plugins = NULL;
  flush->plugins_num = 0;

  sfree(flush->identifiers);
  flush->identifiers_num = 0;
}