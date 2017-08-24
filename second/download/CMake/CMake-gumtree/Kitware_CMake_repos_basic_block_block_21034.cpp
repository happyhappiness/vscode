{
  uv_loop_t* loop = handle->loop;

  if (!uv__is_active(handle))
    return 0;

  RB_REMOVE(uv_timer_tree_s, &loop->timers, handle);
  uv__handle_stop(handle);

  return 0;
}