(handle->flags & UV_HANDLE_READING) {
      /* Real error */
      handle->flags &= ~UV_HANDLE_READING;
      DECREASE_ACTIVE_COUNT(loop, handle);
      handle->read_cb((uv_stream_t*) handle,
                      uv_translate_sys_error(GET_REQ_ERROR(req)),
                      &buf);
    } else {
      /* The read was cancelled, or whatever we don't care */
      handle->read_cb((uv_stream_t*) handle, 0, &buf);
    }