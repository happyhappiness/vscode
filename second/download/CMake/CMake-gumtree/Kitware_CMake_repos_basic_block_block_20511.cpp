(ipc_frame.header.flags & UV_IPC_RAW_DATA) {
            handle->pipe.conn.remaining_ipc_rawdata_bytes =
              ipc_frame.header.raw_data_length;
            continue;
          }