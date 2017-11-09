static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct transfer_status *st = (struct transfer_status *)userp;
  size_t len = size * nmemb;
  st->counter++;
  if(st->counter > 1) {
    /* the first call puts us on pause, so subsequent calls are after
       unpause */
    fwrite(ptr, size, nmemb, stdout);
    return len;
  }
  printf("Got %d bytes but pausing!\n", (int)len);
  st->halted = 1;
  return CURL_WRITEFUNC_PAUSE;
}