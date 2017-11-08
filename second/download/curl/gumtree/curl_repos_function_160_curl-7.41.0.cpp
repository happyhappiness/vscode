int main(int argc, char **argv)
{
  GlobalInfo *g;
  CURLMcode rc;
  GMainLoop*gmain;
  int fd;
  GIOChannel* ch;
  g=g_malloc0(sizeof(GlobalInfo));

  fd=init_fifo();
  ch=g_io_channel_unix_new(fd);
  g_io_add_watch(ch,G_IO_IN,fifo_cb,g);
  gmain=g_main_loop_new(NULL,FALSE);
  g->multi = curl_multi_init();
  curl_multi_setopt(g->multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g->multi, CURLMOPT_SOCKETDATA, g);
  curl_multi_setopt(g->multi, CURLMOPT_TIMERFUNCTION, update_timeout_cb);
  curl_multi_setopt(g->multi, CURLMOPT_TIMERDATA, g);

  /* we don't call any curl_multi_socket*() function yet as we have no handles
     added! */

  g_main_loop_run(gmain);
  curl_multi_cleanup(g->multi);
  return 0;
}