{
    rem_oneshot = handle->flags & UV__SIGNAL_ONE_SHOT;
    first_oneshot = first_handle->flags & UV__SIGNAL_ONE_SHOT;
    if (first_oneshot && !rem_oneshot) {
      ret = uv__signal_register_handler(handle->signum, 1);
      assert(ret == 0);
    }
  }