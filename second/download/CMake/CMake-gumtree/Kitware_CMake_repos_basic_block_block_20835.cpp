{

    UNREGISTER_HANDLE_REQ(loop, handle, handle->stream.conn.shutdown_req);

    err = 0;
    if (handle->flags & UV__HANDLE_CLOSING) {
      err = ERROR_OPERATION_ABORTED;
    } else if (shutdown(handle->socket, SD_SEND) == SOCKET_ERROR) {
      err = WSAGetLastError();
    }

    if (handle->stream.conn.shutdown_req->cb) {
      handle->stream.conn.shutdown_req->cb(handle->stream.conn.shutdown_req,
                               uv_translate_sys_error(err));
    }

    handle->stream.conn.shutdown_req = NULL;
    DECREASE_PENDING_REQ_COUNT(handle);
    return;
  }