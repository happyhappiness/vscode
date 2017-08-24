{
      handle->flags &= ~UV_HANDLE_READING;
      handle->read_cb((uv_stream_t*)handle,
                      uv_translate_sys_error(GET_REQ_ERROR(req)),
                      &uv_null_buf_);
    }