{
      tcp_send_handle = (uv_tcp_t*)send_handle;

      if (handle->pipe.conn.ipc_pid == 0) {
          handle->pipe.conn.ipc_pid = uv_current_pid();
      }

      err = uv_tcp_duplicate_socket(tcp_send_handle, handle->pipe.conn.ipc_pid,
          &ipc_frame.socket_info_ex.socket_info);
      if (err) {
        return err;
      }

      ipc_frame.socket_info_ex.delayed_error = tcp_send_handle->delayed_error;

      ipc_frame.header.flags |= UV_IPC_TCP_SERVER;

      if (tcp_send_handle->flags & UV_HANDLE_CONNECTION) {
        ipc_frame.header.flags |= UV_IPC_TCP_CONNECTION;
      }
    }