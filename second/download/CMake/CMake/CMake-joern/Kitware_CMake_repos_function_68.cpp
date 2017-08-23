static char *
create_hostcache_id(const char *name, int port)
{
  /* create and return the new allocated entry */
  char *id = aprintf("%s:%d", name, port);
  char *ptr = id;
  if(ptr) {
    /* lower case the name part */
    while(*ptr && (*ptr != ':')) {
      *ptr = (char)TOLOWER(*ptr);
      ptr++;
    }
  }
  return id;
}