static int plugin_read(void) /* {{{ */
{
  unsigned int i = 0;
  pinba_statnode_t data;

  while ((i = service_statnode_collect(&data, i)) != 0) {
    plugin_submit(&data);
  }

  return 0;
}