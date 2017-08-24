(handle->flags & UV__HANDLE_CLOSING) {
        handle->stream.conn.shutdown_req->cb(handle->stream.conn.shutdown_req, UV_ECANCELED);
      } else {
        handle->stream.conn.shutdown_req->cb(handle->stream.conn.shutdown_req, 0);
      }