{
        handle->stream.conn.shutdown_req->cb(handle->stream.conn.shutdown_req, UV_ECANCELED);
      }