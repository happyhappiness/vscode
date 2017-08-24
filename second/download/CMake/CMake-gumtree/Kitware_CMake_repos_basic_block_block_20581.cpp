{
    unsigned char events = 0;

    if ((afd_poll_info->Handles[0].Events & (AFD_POLL_RECEIVE |
        AFD_POLL_DISCONNECT | AFD_POLL_ACCEPT | AFD_POLL_ABORT)) != 0) {
      events |= UV_READABLE;
      if ((afd_poll_info->Handles[0].Events & AFD_POLL_DISCONNECT) != 0) {
        events |= UV_DISCONNECT;
      }
    }
    if ((afd_poll_info->Handles[0].Events & (AFD_POLL_SEND |
        AFD_POLL_CONNECT_FAIL)) != 0) {
      events |= UV_WRITABLE;
    }

    events &= handle->events & ~mask_events;

    if (afd_poll_info->Handles[0].Events & AFD_POLL_LOCAL_CLOSE) {
      /* Stop polling. */
      handle->events = 0;
      if (uv__is_active(handle))
        uv__handle_stop(handle);
    }

    if (events != 0) {
      handle->poll_cb(handle, 0, events);
    }
  }