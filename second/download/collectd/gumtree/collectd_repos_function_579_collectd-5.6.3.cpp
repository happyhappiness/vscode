static char *build_json_str_list(const char *tag,
                                 struct str_list const *list) /* {{{ */
{
  int res;
  char *ret_str = NULL;
  char *temp_str;
  if (list->nb_strs == 0) {
    ret_str = malloc(sizeof(char));
    if (ret_str == NULL) {
      ERROR("write_sensu plugin: Unable to alloc memory");
      return NULL;
    }
    ret_str[0] = '\0';
  }

  res = my_asprintf(&temp_str, "\"%s\": [\"%s\"", tag, list->strs[0]);
  if (res == -1) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    free(ret_str);
    return NULL;
  }
  for (int i = 1; i < list->nb_strs; i++) {
    res = my_asprintf(&ret_str, "%s, \"%s\"", temp_str, list->strs[i]);
    free(temp_str);
    if (res == -1) {
      ERROR("write_sensu plugin: Unable to alloc memory");
      return NULL;
    }
    temp_str = ret_str;
  }
  res = my_asprintf(&ret_str, "%s]", temp_str);
  free(temp_str);
  if (res == -1) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    return NULL;
  }

  return ret_str;
}