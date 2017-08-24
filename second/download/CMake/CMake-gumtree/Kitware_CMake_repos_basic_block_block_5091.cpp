{

    /* Add the time zone diff between local time zone and GMT. */
    long delta = (long)(tzoff!=-1?tzoff:0);

    if((delta>0) && (t > LONG_MAX - delta)) {
      *output = 0x7fffffff;
      return PARSEDATE_LATER; /* time_t overflow */
    }

    t += delta;
  }