static
int random_the_seed(struct SessionHandle *data)
{
  char *buf = data->state.buffer; /* point to the big buffer */
  int nread=0;

  /* Q: should we add support for a random file name as a libcurl option?
     A: Yes, it is here */

#ifndef RANDOM_FILE
  /* if RANDOM_FILE isn't defined, we only perform this if an option tells
     us to! */
  if(data->set.ssl.random_file)
#define RANDOM_FILE "" /* doesn't matter won't be used */
#endif
  {
    /* let the option override the define */
    nread += RAND_load_file((data->set.ssl.random_file?
                             data->set.ssl.random_file:RANDOM_FILE),
                            RAND_LOAD_LENGTH);
    if(seed_enough(nread))
      return nread;
  }

#if defined(HAVE_RAND_EGD)
  /* only available in OpenSSL 0.9.5 and later */
  /* EGD_SOCKET is set at configure time or not at all */
#ifndef EGD_SOCKET
  /* If we don't have the define set, we only do this if the egd-option
     is set */
  if(data->set.ssl.egdsocket)
#define EGD_SOCKET "" /* doesn't matter won't be used */
#endif
  {
    /* If there's an option and a define, the option overrides the
       define */
    int ret = RAND_egd(data->set.ssl.egdsocket?
                       data->set.ssl.egdsocket:EGD_SOCKET);
    if(-1 != ret) {
      nread += ret;
      if(seed_enough(nread))
        return nread;
    }
  }
#endif

  /* If we get here, it means we need to seed the PRNG using a "silly"
     approach! */
#ifdef HAVE_RAND_SCREEN
  /* This one gets a random value by reading the currently shown screen */
  RAND_screen();
  nread = 100; /* just a value */
#else
  {
    int len;
    char *area;

    /* Changed call to RAND_seed to use the underlying RAND_add implementation
     * directly.  Do this in a loop, with the amount of additional entropy
     * being dependent upon the algorithm used by Curl_FormBoundary(): N bytes
     * of a 7-bit ascii set. -- Richard Gorton, March 11 2003.
     */

    do {
      area = Curl_FormBoundary();
      if(!area)
        return 3; /* out of memory */

      len = (int)strlen(area);
      RAND_add(area, len, (len >> 1));

      free(area); /* now remove the random junk */
    } while (!RAND_status());
  }
#endif

  /* generates a default path for the random seed file */
  buf[0]=0; /* blank it first */
  RAND_file_name(buf, BUFSIZE);
  if(buf[0]) {
    /* we got a file name to try */
    nread += RAND_load_file(buf, RAND_LOAD_LENGTH);
    if(seed_enough(nread))
      return nread;
  }

  infof(data, "libcurl is now using a weak random seed!\n");
  return nread;
}