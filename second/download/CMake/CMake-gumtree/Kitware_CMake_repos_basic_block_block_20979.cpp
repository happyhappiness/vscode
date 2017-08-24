{
  /* Initialize the semaphore that acts as the write lock. */
  HANDLE handle = CreateSemaphoreW(NULL, 1, 1, NULL);
  if (handle == NULL)
    return uv_translate_sys_error(GetLastError());
  rwlock->state_.write_semaphore_ = handle;

  /* Initialize the critical section protecting the reader count. */
  InitializeCriticalSection(&rwlock->state_.num_readers_lock_);

  /* Initialize the reader count. */
  rwlock->state_.num_readers_ = 0;

  return 0;
}