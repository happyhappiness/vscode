static void my_unlock(CURL *handle, curl_lock_data data, void *useptr )
{
  const char *what;
  struct userdata *user = (struct userdata *)useptr;
  int locknum;
  (void)handle;
  switch ( data ) {
    case CURL_LOCK_DATA_SHARE:
      what = "share";
      locknum = 0;
      break;
    case CURL_LOCK_DATA_DNS:
      what = "dns";
      locknum = 1;
      break;
    case CURL_LOCK_DATA_COOKIE:
      what = "cookie";
      locknum = 2;
      break;
    default:
      fprintf(stderr, "unlock: no such data: %d\n", (int)data);
      return;
  }

  /* detect unlocking of unlocked locks */
  if(!lock[locknum]) {
    printf("unlock: double unlocked %s\n", what);
    return;
  }
  lock[locknum]--;

  printf("unlock: %-6s [%s]: %d\n", what, user->text, user->counter);
  user->counter++;
}