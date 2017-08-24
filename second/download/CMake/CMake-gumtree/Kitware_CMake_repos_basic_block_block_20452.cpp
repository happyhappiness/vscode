(handle->flags & UV_HANDLE_READING) {
        /* just a brief break to do something else */
        handle->pipe.conn.readfile_thread = NULL;
        /* resume after it is finished */
        uv_mutex_lock(m);
        handle->pipe.conn.readfile_thread = hThread;
        uv_mutex_unlock(m);
        goto restart_readfile;
      } else {
        result = 1; /* successfully stopped reading */
      }