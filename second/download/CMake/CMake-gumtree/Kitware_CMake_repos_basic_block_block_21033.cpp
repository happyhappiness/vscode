{
  uv_loop_t* loop = handle->loop;
  uv_timer_t* old;

  if (timer_cb == NULL)
    return UV_EINVAL;

  if (uv__is_active(handle))
    uv_timer_stop(handle);

  handle->timer_cb = timer_cb;
  handle->due = get_clamped_due_time(loop->time, timeout);
  handle->repeat = repeat;
  uv__handle_start(handle);

  /* start_id is the second index to be compared in uv__timer_cmp() */
  handle->start_id = handle->loop->timer_counter++;

  old = RB_INSERT(uv_timer_tree_s, &loop->timers, handle);
  assert(old == NULL);

  return 0;
}