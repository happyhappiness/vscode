unsigned int Curl_rand(struct SessionHandle *data)
{
  unsigned int r = 0;
  static unsigned int randseed;
  static bool seeded = FALSE;

#ifdef CURLDEBUG
  char *force_entropy = getenv("CURL_ENTROPY");
  if(force_entropy) {
    if(!seeded) {
      size_t elen = strlen(force_entropy);
      size_t clen = sizeof(randseed);
      size_t min = elen < clen ? elen : clen;
      memcpy((char *)&randseed, force_entropy, min);
      seeded = TRUE;
    }
    else
      randseed++;
    return randseed;
  }
#endif

  /* data may be NULL! */
  if(!Curl_ssl_random(data, (unsigned char *)&r, sizeof(r)))
    return r;

  /* If Curl_ssl_random() returns non-zero it couldn't offer randomness and we
     instead perform a "best effort" */

#ifdef RANDOM_FILE
  if(!seeded) {
    /* if there's a random file to read a seed from, use it */
    int fd = open(RANDOM_FILE, O_RDONLY);
    if(fd > -1) {
      /* read random data into the randseed variable */
      ssize_t nread = read(fd, &randseed, sizeof(randseed));
      if(nread == sizeof(randseed))
        seeded = TRUE;
      close(fd);
    }
  }
#endif

  if(!seeded) {
    struct timeval now = curlx_tvnow();
    infof(data, "WARNING: Using weak random seed\n");
    randseed += (unsigned int)now.tv_usec + (unsigned int)now.tv_sec;
    randseed = randseed * 1103515245 + 12345;
    randseed = randseed * 1103515245 + 12345;
    randseed = randseed * 1103515245 + 12345;
    seeded = TRUE;
  }

  /* Return an unsigned 32-bit pseudo-random number. */
  r = randseed = randseed * 1103515245 + 12345;
  return (r << 16) | ((r >> 16) & 0xFFFF);
}