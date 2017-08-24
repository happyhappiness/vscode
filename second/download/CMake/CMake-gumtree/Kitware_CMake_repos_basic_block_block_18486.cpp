(i = 0; i < nthreads; i++)
    if (uv_thread_create(threads + i, worker, NULL))
      abort()