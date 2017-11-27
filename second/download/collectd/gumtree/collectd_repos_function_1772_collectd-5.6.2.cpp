static int olsrd_shutdown(void) /* {{{ */
{
  sfree(config_node);
  sfree(config_service);

  return (0);
}