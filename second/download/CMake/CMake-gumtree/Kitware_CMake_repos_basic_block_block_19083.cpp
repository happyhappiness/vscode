{
  if (!uv__is_active(handle))
    return 0;

  uv__handle_stop(handle);

#if defined(__APPLE__)
  if (uv__has_forked_with_cfrunloop || uv__fsevents_close(handle))
#endif /* defined(__APPLE__) */
  {
    uv__io_close(handle->loop, &handle->event_watcher);
  }

  uv__free(handle->path);
  handle->path = NULL;

  if (handle->event_watcher.fd != -1) {
    /* When FSEvents is used, we don't use the event_watcher's fd under certain
     * confitions. (see uv_fs_event_start) */
    uv__close(handle->event_watcher.fd);
    handle->event_watcher.fd = -1;
  }

  return 0;
}