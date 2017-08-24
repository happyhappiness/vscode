{
  uv_loop_t** new_loops;
  int new_capacity, i;

  uv_mutex_lock(&uv__loops_lock);

  if (uv__loops_size == uv__loops_capacity) {
    new_capacity = uv__loops_capacity + UV__LOOPS_CHUNK_SIZE;
    new_loops = uv__realloc(uv__loops, sizeof(uv_loop_t*) * new_capacity);
    if (!new_loops)
      goto failed_loops_realloc;
    uv__loops = new_loops;
    for (i = uv__loops_capacity; i < new_capacity; ++i)
      uv__loops[i] = NULL;
    uv__loops_capacity = new_capacity;
  }
  uv__loops[uv__loops_size] = loop;
  ++uv__loops_size;

  uv_mutex_unlock(&uv__loops_lock);
  return 0;

failed_loops_realloc:
  uv_mutex_unlock(&uv__loops_lock);
  return ERROR_OUTOFMEMORY;
}