{
    int r = uv_signal_stop(handle);
    /* uv_signal_stop is infallible. */
    assert(r == 0);
  }