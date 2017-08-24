{
        /* spinlock: we expect this to finish quickly,
           or we are probably about to deadlock anyways
           (in the kernel), so it doesn't matter */
        pCancelSynchronousIo(h);
        SwitchToThread(); /* yield thread control briefly */
        h = handle->pipe.conn.readfile_thread;
      }