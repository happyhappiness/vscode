{
  uv_signal_t* removed_handle;

  /* If the watcher wasn't started, this is a no-op. */
  if (handle->signum == 0)
    return 0;

  EnterCriticalSection(&uv__signal_lock);

  removed_handle = RB_REMOVE(uv_signal_tree_s, &uv__signal_tree, handle);
  assert(removed_handle == handle);

  LeaveCriticalSection(&uv__signal_lock);

  handle->signum = 0;
  uv__handle_stop(handle);

  return 0;
}