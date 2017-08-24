{
  CFRunLoopSourceContext ctx;
  uv__cf_loop_state_t* state;
  pthread_attr_t attr_storage;
  pthread_attr_t* attr;
  int err;

  if (loop->cf_state != NULL)
    return 0;

  err = uv__fsevents_global_init();
  if (err)
    return err;

  state = uv__calloc(1, sizeof(*state));
  if (state == NULL)
    return -ENOMEM;

  err = uv_mutex_init(&loop->cf_mutex);
  if (err)
    goto fail_mutex_init;

  err = uv_sem_init(&loop->cf_sem, 0);
  if (err)
    goto fail_sem_init;

  QUEUE_INIT(&loop->cf_signals);

  err = uv_sem_init(&state->fsevent_sem, 0);
  if (err)
    goto fail_fsevent_sem_init;

  err = uv_mutex_init(&state->fsevent_mutex);
  if (err)
    goto fail_fsevent_mutex_init;

  QUEUE_INIT(&state->fsevent_handles);
  state->fsevent_need_reschedule = 0;
  state->fsevent_handle_count = 0;

  memset(&ctx, 0, sizeof(ctx));
  ctx.info = loop;
  ctx.perform = uv__cf_loop_cb;
  state->signal_source = pCFRunLoopSourceCreate(NULL, 0, &ctx);
  if (state->signal_source == NULL) {
    err = -ENOMEM;
    goto fail_signal_source_create;
  }

  /* In the unlikely event that pthread_attr_init() fails, create the thread
   * with the default stack size. We'll use a little more address space but
   * that in itself is not a fatal error.
   */
  attr = &attr_storage;
  if (pthread_attr_init(attr))
    attr = NULL;

  if (attr != NULL)
    if (pthread_attr_setstacksize(attr, 4 * PTHREAD_STACK_MIN))
      abort();

  loop->cf_state = state;

  /* uv_thread_t is an alias for pthread_t. */
  err = -pthread_create(&loop->cf_thread, attr, uv__cf_loop_runner, loop);

  if (attr != NULL)
    pthread_attr_destroy(attr);

  if (err)
    goto fail_thread_create;

  /* Synchronize threads */
  uv_sem_wait(&loop->cf_sem);
  return 0;

fail_thread_create:
  loop->cf_state = NULL;

fail_signal_source_create:
  uv_mutex_destroy(&state->fsevent_mutex);

fail_fsevent_mutex_init:
  uv_sem_destroy(&state->fsevent_sem);

fail_fsevent_sem_init:
  uv_sem_destroy(&loop->cf_sem);

fail_sem_init:
  uv_mutex_destroy(&loop->cf_mutex);

fail_mutex_init:
  uv__free(state);
  return err;
}