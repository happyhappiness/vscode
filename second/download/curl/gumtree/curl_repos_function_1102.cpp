static bool countcheck(const char *func, int line, const char *source)
{
  /* if source is NULL, then the call is made internally and this check
     should not be made */
  if(memlimit && source) {
    if(!memsize) {
      if(source) {
        /* log to file */
        curl_memlog("LIMIT %s:%d %s reached memlimit\n",
                    source, line, func);
        /* log to stderr also */
        fprintf(stderr, "LIMIT %s:%d %s reached memlimit\n",
                source, line, func);
      }
      SET_ERRNO(ENOMEM);
      return TRUE; /* RETURN ERROR! */
    }
    else
      memsize--; /* countdown */

    /* log the countdown */
    if(source)
      curl_memlog("LIMIT %s:%d %ld ALLOCS left\n",
                  source, line, memsize);

  }

  return FALSE; /* allow this */
}