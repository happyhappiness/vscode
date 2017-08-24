{
      handle->stream.conn.shutdown_req->cb(handle->stream.conn.shutdown_req,
                               uv_translate_sys_error(err));
    }