{
          handle->read_cb((uv_stream_t*) handle, buf_used, &buf);
          buf = uv_null_buf_;
          buf_used = 0;
        }