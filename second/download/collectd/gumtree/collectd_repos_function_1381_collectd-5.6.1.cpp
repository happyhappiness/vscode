static int gmond_init (void) /* {{{ */
{
  create_sockets (&mc_send_sockets, &mc_send_sockets_num,
      (mc_receive_group != NULL) ? mc_receive_group : MC_RECEIVE_GROUP_DEFAULT,
      (mc_receive_port != NULL) ? mc_receive_port : MC_RECEIVE_PORT_DEFAULT,
      /* listen = */ 0);

  staging_tree = c_avl_create ((int (*) (const void *, const void *)) strcmp);
  if (staging_tree == NULL)
  {
    ERROR ("gmond plugin: c_avl_create failed.");
    return (-1);
  }

  mc_receive_thread_start ();

  return (0);
}