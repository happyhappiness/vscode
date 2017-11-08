static void my_unlock(CURL *handle, curl_lock_data data, void *useptr)
{
  const char *what;
  struct userdata *user = (struct userdata *)useptr;
  (void)handle;
  switch(data) {
    case CURL_LOCK_DATA_SHARE:
      what = "share";
      break;
    case CURL_LOCK_DATA_DNS:
      what = "dns";
      break;
    case CURL_LOCK_DATA_COOKIE:
      what = "cookie";
      break;
    case CURL_LOCK_DATA_SSL_SESSION:
      what = "ssl_session";
      break;
    default:
      fprintf(stderr, "unlock: no such data: %d\n", (int)data);
      return;
  }
  printf("unlock: %-6s [%s]: %d\n", what, user->text, user->counter);
  user->counter++;
}