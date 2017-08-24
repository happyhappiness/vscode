{
    new_capacity = uv__loops_capacity + UV__LOOPS_CHUNK_SIZE;
    new_loops = uv__realloc(uv__loops, sizeof(uv_loop_t*) * new_capacity);
    if (!new_loops)
      goto failed_loops_realloc;
    uv__loops = new_loops;
    for (i = uv__loops_capacity; i < new_capacity; ++i)
      uv__loops[i] = NULL;
    uv__loops_capacity = new_capacity;
  }