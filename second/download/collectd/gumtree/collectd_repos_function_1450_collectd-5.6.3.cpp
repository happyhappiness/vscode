static int tbl_config_set_s(char *name, char **var, oconfig_item_t *ci) {
  if ((1 != ci->values_num) || (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("\"%s\" expects a single string argument.", name);
    return 1;
  }

  sfree(*var);
  *var = sstrdup(ci->values[0].value.string);
  return 0;
}