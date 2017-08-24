{
    DWORD r = WaitForSingleObject(rwlock->state_.write_semaphore_, INFINITE);
    if (r != WAIT_OBJECT_0)
      uv_fatal_error(GetLastError(), "WaitForSingleObject");
  }