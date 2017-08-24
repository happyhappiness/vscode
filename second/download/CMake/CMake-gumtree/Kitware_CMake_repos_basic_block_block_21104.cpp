{
      /* Read successful */
      /* TODO: read unicode, convert to utf-8 */
      DWORD bytes = req->u.io.overlapped.InternalHigh;
      handle->read_cb((uv_stream_t*) handle, bytes, &buf);
    }