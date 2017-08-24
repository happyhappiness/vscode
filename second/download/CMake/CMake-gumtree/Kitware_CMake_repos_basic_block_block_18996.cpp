{
  uv__cf_loop_signal_t* item;
  uv__cf_loop_state_t* state;

  item = uv__malloc(sizeof(*item));
  if (item == NULL)
    return -ENOMEM;

  item->handle = handle;
  item->type = type;

  uv_mutex_lock(&loop->cf_mutex);
  QUEUE_INSERT_TAIL(&loop->cf_signals, &item->member);
  uv_mutex_unlock(&loop->cf_mutex);

  state = loop->cf_state;
  assert(state != NULL);
  pCFRunLoopSourceSignal(state->signal_source);
  pCFRunLoopWakeUp(state->loop);

  return 0;
}