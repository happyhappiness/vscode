static const char *olsrd_get_node (void) /* {{{ */
{
  if (config_node != NULL)
    return (config_node);
  return (OLSRD_DEFAULT_NODE);
}