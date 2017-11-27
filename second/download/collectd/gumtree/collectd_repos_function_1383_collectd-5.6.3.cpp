static int gmond_shutdown(void) /* {{{ */
{
  mc_receive_thread_stop();

  pthread_mutex_lock(&mc_send_sockets_lock);
  for (size_t i = 0; i < mc_send_sockets_num; i++) {
    close(mc_send_sockets[i].fd);
    mc_send_sockets[i].fd = -1;
  }
  sfree(mc_send_sockets);
  mc_send_sockets_num = 0;
  pthread_mutex_unlock(&mc_send_sockets_lock);

  return (0);
}