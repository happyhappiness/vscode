{
  int err;
  uv__cf_loop_state_t* state;

  if (handle->cf_cb == NULL)
    return -EINVAL;

  /* Remove handle from  the list */
  state = handle->loop->cf_state;
  uv_mutex_lock(&state->fsevent_mutex);
  QUEUE_REMOVE(&handle->cf_member);
  state->fsevent_handle_count--;
  state->fsevent_need_reschedule = 1;
  uv_mutex_unlock(&state->fsevent_mutex);

  /* Reschedule FSEventStream */
  assert(handle != NULL);
  err = uv__cf_loop_signal(handle->loop, handle, kUVCFLoopSignalClosing);
  if (err)
    return -err;

  /* Wait for deinitialization */
  uv_sem_wait(&state->fsevent_sem);

  uv_close((uv_handle_t*) handle->cf_cb, (uv_close_cb) uv__free);
  handle->cf_cb = NULL;

  /* Free data in queue */
  UV__FSEVENTS_PROCESS(handle, {
    /* NOP */
  })