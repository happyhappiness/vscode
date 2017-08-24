{
    /* pthread_attr_setstacksize() expects page-aligned values. */
    lim.rlim_cur -= lim.rlim_cur % (rlim_t) getpagesize();

    if (lim.rlim_cur >= PTHREAD_STACK_MIN)
      if (pthread_attr_setstacksize(attr, lim.rlim_cur))
        abort();
  }