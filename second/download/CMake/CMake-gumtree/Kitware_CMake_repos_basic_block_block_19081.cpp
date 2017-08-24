{
    /* When FSEvents is used, we don't use the event_watcher's fd under certain
     * confitions. (see uv_fs_event_start) */
    uv__close(handle->event_watcher.fd);
    handle->event_watcher.fd = -1;
  }