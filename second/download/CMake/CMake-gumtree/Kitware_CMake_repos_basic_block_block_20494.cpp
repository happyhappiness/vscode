{
      /*
       * Try to use the preallocated write req if it's available.
       * Otherwise allocate a new one.
       */
      if (handle->pipe.conn.ipc_header_write_req.type != UV_WRITE) {
        ipc_header_req = (uv_write_t*)&handle->pipe.conn.ipc_header_write_req;
      } else {
        ipc_header_req = (uv_write_t*)uv__malloc(sizeof(uv_write_t));
        if (!ipc_header_req) {
          uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
        }
      }

      UV_REQ_INIT(ipc_header_req, UV_WRITE);
      ipc_header_req->handle = (uv_stream_t*) handle;
      ipc_header_req->cb = NULL;
      ipc_header_req->ipc_header = 1;
    }