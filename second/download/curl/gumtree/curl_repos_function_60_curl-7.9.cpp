static
int random_the_seed(struct connectdata *conn)
{
  char *buf = conn->data->state.buffer; /* point to the big buffer */
  int nread=0;
  struct SessionHandle *data=conn->data;

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
                            16384);
    if(seed_enough(conn, nread))
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
    int ret = RAND_egd(data->set.ssl.egdsocket?data->set.ssl.egdsocket:EGD_SOCKET);
    if(-1 != ret) {
      nread += ret;
      if(seed_enough(conn, nread))
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
    char *area = Curl_FormBoundary();
    if(!area)
      return 3; /* out of memory */
	
    len = strlen(area);
    RAND_seed(area, len);

    free(area); /* now remove the random junk */
  }
#endif

  /* generates a default path for the random seed file */
  buf[0]=0; /* blank it first */
  RAND_file_name(buf, BUFSIZE);
  if ( buf[0] ) {
    /* we got a file name to try */
    nread += RAND_load_file(buf, 16384);
    if(seed_enough(conn, nread))
      return nread;
  }

  infof(conn->data, "Your connection is using a weak random seed!\n");
  return nread;
}