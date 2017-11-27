static int conn_init (void)
{
  if (port_list_head == NULL)
    port_collect_listening = 1;

  return (0);
}