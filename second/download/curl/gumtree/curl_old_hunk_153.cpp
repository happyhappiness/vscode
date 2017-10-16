  _lseeki64(fd, curr, SEEK_SET);
  return rc;
}
#define ftruncate(fd,where) ftruncate64(fd,where)
#endif

/*
 * This is the main global constructor for the app. Call this before
 * _any_ libcurl usage. If this fails, *NO* libcurl functions may be
 * used, or havoc may be the result.
 */
static CURLcode main_init(void)
