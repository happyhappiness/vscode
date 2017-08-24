((handle->flags & UV__HANDLE_CLOSING) &&
             handle->submitted_events_1 == 0 &&
             handle->submitted_events_2 == 0) {
    uv_want_endgame(loop, (uv_handle_t*) handle);
  }