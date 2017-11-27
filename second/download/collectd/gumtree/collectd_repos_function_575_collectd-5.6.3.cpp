static int add_str_to_list(struct str_list *strs,
                           const char *str_to_add) /* {{{ */
{
  char **old_strs_ptr = strs->strs;
  char *newstr = strdup(str_to_add);
  if (newstr == NULL) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    return -1;
  }
  strs->strs = realloc(strs->strs, sizeof(char *) * (strs->nb_strs + 1));
  if (strs->strs == NULL) {
    strs->strs = old_strs_ptr;
    free(newstr);
    ERROR("write_sensu plugin: Unable to alloc memory");
    return -1;
  }
  strs->strs[strs->nb_strs] = newstr;
  strs->nb_strs++;
  return 0;
}