(handle->type == UV_NAMED_PIPE) {
      uv__pipe_stop_read((uv_pipe_t*) handle);
    } else {
      handle->flags &= ~UV_HANDLE_READING;
    }