{
      err = GET_REQ_ERROR(req);
      handle->events = 0; /* Stop the watcher */
      handle->poll_cb(handle, uv_translate_sys_error(err), 0);
    }