
{
  CURLcode result;
  va_list arg;
  struct SessionHandle * data;
  char * s;
  unsigned int ccsid;
  static char testwarn = 1;

  /* Warns if this procedure has not been updated when the dupstring enum
     changes.
     We (try to) do it only once: there is no need to issue several times
     the same message; but since threadsafeness is not handled here,
     this may occur (and we don't care!). */

  if (testwarn) {
    testwarn = 0;

    if ((int) STRING_LAST != (int) STRING_USERPWD + 1)
      curl_mfprintf(stderr,
       "*** WARNING: curl_easy_setopt_ccsid() should be reworked ***\n");
    }

  data = (struct SessionHandle *) curl;
  va_start(arg, tag);
