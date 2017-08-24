{
      /* Pause the ReadFile task briefly, to work
         around the Windows kernel bug that causes
         any access to a NamedPipe to deadlock if
         any process has called ReadFile */
      HANDLE h;
      uv_mutex_lock(&handle->pipe.conn.readfile_mutex);
      h = handle->pipe.conn.readfile_thread;
      while (h) {
        /* spinlock: we expect this to finish quickly,
           or we are probably about to deadlock anyways
           (in the kernel), so it doesn't matter */
        pCancelSynchronousIo(h);
        SwitchToThread(); /* yield thread control briefly */
        h = handle->pipe.conn.readfile_thread;
      }
  }