static int compare_read_func_group(llentry_t *e, void *ud) /* {{{ */
{
  read_func_t *rf = e->value;
  char *group = ud;

  return strcmp(rf->rf_group, (const char *)group);
}