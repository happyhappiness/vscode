{
      handle->flags &= ~UV_HANDLE_LISTENING;
      DECREASE_ACTIVE_COUNT(loop, handle);
      if (handle->stream.serv.connection_cb) {
        err = GET_REQ_SOCK_ERROR(req);
        handle->stream.serv.connection_cb((uv_stream_t*)handle,
                                      uv_translate_sys_error(err));
      }
    }