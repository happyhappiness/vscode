static int ts_config_add_string (char **dest, /* {{{ */
    const oconfig_item_t *ci, int may_be_empty)
{
  char *tmp = NULL;
  int status;

  status = cf_util_get_string (ci, &tmp);
  if (status != 0)
    return (status);

  if (!may_be_empty && (strlen (tmp) == 0))
  {
    ERROR ("Target `set': The `%s' option does not accept empty strings.",
        ci->key);
    sfree (tmp);
    return (-1);
  }

  *dest = tmp;
  return (0);
}