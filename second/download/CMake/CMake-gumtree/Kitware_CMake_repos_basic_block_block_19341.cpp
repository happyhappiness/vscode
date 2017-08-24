{
    /*
     * Unlink the file system entity before closing the file descriptor.
     * Doing it the other way around introduces a race where our process
     * unlinks a socket with the same name that's just been created by
     * another thread or process.
     */
    unlink(handle->pipe_fname);
    uv__free((void*)handle->pipe_fname);
    handle->pipe_fname = NULL;
  }