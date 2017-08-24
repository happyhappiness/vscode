{
  int err;
  uv__cf_loop_state_t* state;

  err = uv__fsevents_loop_init(handle->loop);
  if (err)
    return err;

  /* Get absolute path to file */
  handle->realpath = realpath(handle->path, NULL);
  if (handle->realpath == NULL)
    return -errno;
  handle->realpath_len = strlen(handle->realpath);

  /* Initialize event queue */
  QUEUE_INIT(&handle->cf_events);
  handle->cf_error = 0;

  /*
   * Events will occur in other thread.
   * Initialize callback for getting them back into event loop's thread
   */
  handle->cf_cb = uv__malloc(sizeof(*handle->cf_cb));
  if (handle->cf_cb == NULL) {
    err = -ENOMEM;
    goto fail_cf_cb_malloc;
  }

  handle->cf_cb->data = handle;
  uv_async_init(handle->loop, handle->cf_cb, uv__fsevents_cb);
  handle->cf_cb->flags |= UV__HANDLE_INTERNAL;
  uv_unref((uv_handle_t*) handle->cf_cb);

  err = uv_mutex_init(&handle->cf_mutex);
  if (err)
    goto fail_cf_mutex_init;

  /* Insert handle into the list */
  state = handle->loop->cf_state;
  uv_mutex_lock(&state->fsevent_mutex);
  QUEUE_INSERT_TAIL(&state->fsevent_handles, &handle->cf_member);
  state->fsevent_handle_count++;
  state->fsevent_need_reschedule = 1;
  uv_mutex_unlock(&state->fsevent_mutex);

  /* Reschedule FSEventStream */
  assert(handle != NULL);
  err = uv__cf_loop_signal(handle->loop, handle, kUVCFLoopSignalRegular);
  if (err)
    goto fail_loop_signal;

  return 0;

fail_loop_signal:
  uv_mutex_destroy(&handle->cf_mutex);

fail_cf_mutex_init:
  uv__free(handle->cf_cb);
  handle->cf_cb = NULL;

fail_cf_cb_malloc:
  uv__free(handle->realpath);
  handle->realpath = NULL;
  handle->realpath_len = 0;

  return err;
}