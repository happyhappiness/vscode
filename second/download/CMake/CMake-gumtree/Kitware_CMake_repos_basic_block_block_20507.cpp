{
          assert(handle->pipe.conn.remaining_ipc_rawdata_bytes >= bytes);
          handle->pipe.conn.remaining_ipc_rawdata_bytes =
            handle->pipe.conn.remaining_ipc_rawdata_bytes - bytes;
        }