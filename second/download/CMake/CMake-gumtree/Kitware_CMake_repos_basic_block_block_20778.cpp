{
    /* When it is closing, it must be stopped at this point. */
    assert(handle->signum == 0);
    uv_want_endgame(loop, (uv_handle_t*) handle);
  }