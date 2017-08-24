{
    assert(hThread == handle->pipe.conn.readfile_thread);
    /* mutex does not control clearing readfile_thread */
    handle->pipe.conn.readfile_thread = NULL;
    uv_mutex_lock(m);
    /* only when we hold the mutex lock is it safe to
       open or close the handle */
    CloseHandle(hThread);
    uv_mutex_unlock(m);
  }