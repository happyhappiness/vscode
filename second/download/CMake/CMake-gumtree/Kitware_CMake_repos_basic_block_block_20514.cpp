(buf.base == NULL || buf.len == 0) {
        handle->read_cb((uv_stream_t*) handle, UV_ENOBUFS, &buf);
        break;
      }