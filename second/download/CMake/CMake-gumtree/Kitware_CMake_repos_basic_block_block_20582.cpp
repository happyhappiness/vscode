{
      handle->events = 0; /* Stop the watcher */
      handle->poll_cb(handle, uv_translate_sys_error(error), 0);
    }