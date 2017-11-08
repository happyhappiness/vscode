static bool countcheck(const char *func, int line, const char *source)
{
  /* if source is NULL, then the call is made internally and this check
     should not be made */
  if(memlimit && source) {
    if(!memsize) {
      if(logfile && source)
        fprintf(logfile, "LIMIT %s:%d %s reached memlimit\n",
                source, line, func);
      if(source)
        fprintf(stderr, "LIMIT %s:%d %s reached memlimit\n",
                source, line, func);
      errno = ENOMEM;
      return TRUE; /* RETURN ERROR! */
    }
    else
      memsize--; /* countdown */

    /* log the countdown */
    if(logfile && source)
      fprintf(logfile, "LIMIT %s:%d %ld ALLOCS left\n",
              source, line, memsize);

  }

  return FALSE; /* allow this */
}