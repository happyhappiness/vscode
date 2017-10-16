  if(checkprefix("http://", url) || checkprefix("https://", url))
    return TRUE;   /* HTTP(S) upload */

  return FALSE; /* non-HTTP upload, probably no output should be expected */
}

static int
operate(struct Configurable *config, int argc, char *argv[])
{
  char errorbuffer[CURL_ERROR_SIZE];
  char useragent[128]; /* buah, we don't want a larger default user agent */
  struct ProgressData progressbar;
