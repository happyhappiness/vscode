{
    uv_mutex_lock(m); /* mutex controls *setting* of readfile_thread */
    if (DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
                        GetCurrentProcess(), &hThread,
                        0, FALSE, DUPLICATE_SAME_ACCESS)) {
      handle->pipe.conn.readfile_thread = hThread;
    } else {
      hThread = NULL;
    }
    uv_mutex_unlock(m);
  }