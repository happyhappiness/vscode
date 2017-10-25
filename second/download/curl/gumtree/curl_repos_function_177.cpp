static int my_fread(void *buffer, size_t sz, size_t nmemb, void *userp)
{
  int rc;
  struct InStruct *in=(struct InStruct *)userp;
  struct Configurable *config = in->config;
  curl_off_t size = (curl_off_t)(sz * nmemb);  /* typecast to prevent warnings
                                                  when converting from
                                                  unsigned to signed */

  if(config->sendpersecond) {
    /*
     * We know when we sent data the previous time. We know how much data
     * we sent. Make sure that this was not faster than we are told to run.
     * If we're faster, sleep a while *before* doing the fread() here.
     * Also, make no larger fread() than should be sent this second!
     */

    struct timeval now;
    long timediff;
    long sleep_time;

    static curl_off_t addit = 0;

    now = curlx_tvnow();
    timediff = curlx_tvdiff(now, config->lastsendtime); /* milliseconds */

    if((config->sendpersecond > CURL_MAX_WRITE_SIZE) &&
       (timediff < 100)) {
      /*
       * We allow very fast transfers, then allow at least 100 ms between
       * each sleeping mile-stone to create more accurate long-term rates.
       */
      addit += size;
    }
    else {
      /* If 'addit' is non-zero, it contains the total amount of bytes
         uploaded during the last 'timediff' milliseconds. If it is zero,
         we use the stored previous size. */
      curl_off_t xfered = addit?addit:(curl_off_t)config->lastsendsize;
      addit = 0; /* clear it for the next round */

      if( xfered*1000 > config->sendpersecond*timediff) {
        /* figure out how many milliseconds to rest */
        sleep_time = (long)(xfered*1000/config->sendpersecond - timediff);
        if(sleep_time > 0) {
          go_sleep (sleep_time);
          now = curlx_tvnow();
        }
      }
      config->lastsendtime = now;

      if(size > config->sendpersecond) {
        /* lower the size to actually read */
        nmemb = (size_t)config->sendpersecond;
        sz = 1;
      }
    }

    config->lastsendsize = sz*nmemb;
  }

  rc = fread(buffer, sz, nmemb, in->stream);
#if 0
  fprintf(stderr, "CALLBACK returning %d bytes data\n", (int)rc);
#endif
  return rc;
}