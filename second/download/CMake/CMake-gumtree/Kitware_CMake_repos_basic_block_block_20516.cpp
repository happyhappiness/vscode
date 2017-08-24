(!PeekNamedPipe(handle->handle,
                          NULL,
                          0,
                          NULL,
                          &avail,
                          NULL)) {
        uv_pipe_read_error_or_eof(loop, handle, GetLastError(), uv_null_buf_);
        break;
      }