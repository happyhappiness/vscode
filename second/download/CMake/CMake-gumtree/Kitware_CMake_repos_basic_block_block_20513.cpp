{
          /* We're reading a new frame.  First, read the header. */
          assert(avail >= sizeof(ipc_frame.header));

          if (!ReadFile(handle->handle,
                        &ipc_frame.header,
                        sizeof(ipc_frame.header),
                        &bytes,
                        NULL)) {
            uv_pipe_read_error_or_eof(loop, handle, GetLastError(),
              uv_null_buf_);
            break;
          }

          assert(bytes == sizeof(ipc_frame.header));
          assert(ipc_frame.header.flags <= (UV_IPC_TCP_SERVER | UV_IPC_RAW_DATA |
            UV_IPC_TCP_CONNECTION));

          if (ipc_frame.header.flags & UV_IPC_TCP_SERVER) {
            assert(avail - sizeof(ipc_frame.header) >=
              sizeof(ipc_frame.socket_info_ex));

            /* Read the TCP socket info. */
            if (!ReadFile(handle->handle,
                          &ipc_frame.socket_info_ex,
                          sizeof(ipc_frame) - sizeof(ipc_frame.header),
                          &bytes,
                          NULL)) {
              uv_pipe_read_error_or_eof(loop, handle, GetLastError(),
                uv_null_buf_);
              break;
            }

            assert(bytes == sizeof(ipc_frame) - sizeof(ipc_frame.header));

            /* Store the pending socket info. */
            uv__pipe_insert_pending_socket(
                handle,
                &ipc_frame.socket_info_ex,
                ipc_frame.header.flags & UV_IPC_TCP_CONNECTION);
          }

          if (ipc_frame.header.flags & UV_IPC_RAW_DATA) {
            handle->pipe.conn.remaining_ipc_rawdata_bytes =
              ipc_frame.header.raw_data_length;
            continue;
          }
        }