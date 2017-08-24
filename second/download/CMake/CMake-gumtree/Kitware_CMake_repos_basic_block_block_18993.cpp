{
  uv__cf_loop_signal_t* s;
  uv__cf_loop_state_t* state;
  QUEUE* q;

  if (loop->cf_state == NULL)
    return;

  if (uv__cf_loop_signal(loop, NULL, kUVCFLoopSignalRegular) != 0)
    abort();

  uv_thread_join(&loop->cf_thread);
  uv_sem_destroy(&loop->cf_sem);
  uv_mutex_destroy(&loop->cf_mutex);

  /* Free any remaining data */
  while (!QUEUE_EMPTY(&loop->cf_signals)) {
    q = QUEUE_HEAD(&loop->cf_signals);
    s = QUEUE_DATA(q, uv__cf_loop_signal_t, member);
    QUEUE_REMOVE(q);
    uv__free(s);
  }

  /* Destroy state */
  state = loop->cf_state;
  uv_sem_destroy(&state->fsevent_sem);
  uv_mutex_destroy(&state->fsevent_mutex);
  pCFRelease(state->signal_source);
  uv__free(state);
  loop->cf_state = NULL;
}