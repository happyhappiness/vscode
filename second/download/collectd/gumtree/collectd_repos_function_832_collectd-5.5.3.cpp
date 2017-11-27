static int ethstat_add_interface (const oconfig_item_t *ci) /* {{{ */
{
  char **tmp;
  int status;

  tmp = realloc (interfaces,
      sizeof (*interfaces) * (interfaces_num + 1));
  if (tmp == NULL)
    return (-1);
  interfaces = tmp;
  interfaces[interfaces_num] = NULL;

  status = cf_util_get_string (ci, interfaces + interfaces_num);
  if (status != 0)
    return (status);

  interfaces_num++;
  INFO("ethstat plugin: Registered interface %s",
      interfaces[interfaces_num - 1]);

  return (0);
}