static void olsrd_set_node(const char *node) /* {{{ */
{
  char *tmp;
  if (node == NULL)
    return;
  tmp = strdup(node);
  if (tmp == NULL)
    return;
  config_node = tmp;
}