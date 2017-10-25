void lock(CURL *handle, curl_lock_data data, curl_lock_access access,
          void *useptr )
{
  const char *what;
  struct userdata *user = (struct userdata *)useptr;

  (void)handle;
  (void)access;

  switch ( data ) {
    case CURL_LOCK_DATA_SHARE:
      what = "share";  
      break;
    case CURL_LOCK_DATA_DNS:
      what = "dns";  
      break;
    case CURL_LOCK_DATA_COOKIE:
      what = "cookie";  
      break;
    default:
      fprintf(stderr, "lock: no such data: %d\n", (int)data);
      return;
  }
  printf("lock:   %-6s <%s>: %d\n", what, user->text, user->counter);
  user->counter++;
}