{
  time_t parsed = -1;
  int rc = parsedate(p, &parsed);
  (void)now; /* legacy argument from the past that we ignore */

  switch(rc) {
  case PARSEDATE_OK:
  case PARSEDATE_LATER:
  case PARSEDATE_SOONER:
    return parsed;
  }
  /* everything else is fail */
  return -1;
}