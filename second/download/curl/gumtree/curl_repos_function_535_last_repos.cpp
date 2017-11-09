static int please_continue(void *userp,
                           curl_off_t dltotal,
                           curl_off_t dlnow,
                           curl_off_t ultotal,
                           curl_off_t ulnow)
{
  struct transfer_status *st = (struct transfer_status *)userp;
  (void)dltotal;
  (void)dlnow;
  (void)ultotal;
  (void)ulnow;
  if(st->halted) {
    st->please++;
    if(st->please == 2) {
      /* waited enough, unpause! */
      curl_easy_pause(st->easy, CURLPAUSE_CONT);
    }
  }
  fprintf(stderr, "xferinfo: paused %d\n", st->halted);
  return 0; /* go on */
}