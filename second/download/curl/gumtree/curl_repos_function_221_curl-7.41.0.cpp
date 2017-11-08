int main(int argc, char **argv)
{
  GlobalInfo g;
  CURLMcode rc;

  (void)argc;
  (void)argv;

  memset(&g, 0, sizeof(GlobalInfo));
  g.multi = curl_multi_init();

  curl_multi_setopt(g.multi, CURLMOPT_SOCKETFUNCTION, sock_cb);
  curl_multi_setopt(g.multi, CURLMOPT_SOCKETDATA, &g);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
  curl_multi_setopt(g.multi, CURLMOPT_TIMERDATA, &g);

  new_conn((char *)"www.google.com", &g);  /* add a URL */

  /* enter io_service run loop */
  io_service.run();

  curl_multi_cleanup(g.multi);

  fprintf(MSG_OUT, "\ndone.\n");

  return 0;
}