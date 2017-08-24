(r == WAIT_OBJECT_0)
      rwlock->state_.num_readers_++;
    else if (r == WAIT_TIMEOUT)
      err = UV_EBUSY;
    else if (r == WAIT_FAILED)
      uv_fatal_error(GetLastError(), "WaitForSingleObject")