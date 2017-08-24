(!ReleaseSemaphore(rwlock->state_.write_semaphore_, 1, NULL))
      uv_fatal_error(GetLastError(), "ReleaseSemaphore")