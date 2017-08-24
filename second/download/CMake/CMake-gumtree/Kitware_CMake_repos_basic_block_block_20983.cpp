(r == WAIT_FAILED)
      uv_fatal_error(GetLastError(), "WaitForSingleObject")