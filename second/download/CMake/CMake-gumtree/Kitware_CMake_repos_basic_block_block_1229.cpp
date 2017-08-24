{
    /* Keep trying to close until it is not interrupted by a
     * signal.  */
    while ((close(*pfd) < 0) && (errno == EINTR))
      ;
    *pfd = -1;
  }