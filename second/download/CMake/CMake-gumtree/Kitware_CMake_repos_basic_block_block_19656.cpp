{
    /* To smooth over the differences between unixes errors that
     * were reported synchronously on the first connect can be delayed
     * until the next tick--which is now.
     */
    error = stream->delayed_error;
    stream->delayed_error = 0;
  }