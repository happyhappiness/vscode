static int tbl_config_append_array_i(char *name, size_t **var, size_t *len,
                                     oconfig_item_t *ci) {
  size_t *tmp;
  size_t num;

  if (1 > ci->values_num) {
    log_err("\"%s\" expects at least one argument.", name);
    return 1;
  }

  num = (size_t)ci->values_num;
  for (size_t i = 0; i < num; ++i) {
    if (OCONFIG_TYPE_NUMBER != ci->values[i].type) {
      log_err("\"%s\" expects numerical arguments only.", name);
      return 1;
    }
  }

  tmp = realloc(*var, ((*len) + num) * sizeof(**var));
  if (NULL == tmp) {
    char errbuf[1024];
    log_err("realloc failed: %s.", sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }
  *var = tmp;

  for (size_t i = 0; i < num; ++i) {
    (*var)[*len] = (size_t)ci->values[i].value.number;
    (*len)++;
  }

  return 0;
}