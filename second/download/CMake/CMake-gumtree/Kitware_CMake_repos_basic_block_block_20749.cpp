{
      /* Unconditionally terminate the process. On Windows, killed processes */
      /* normally return 1. */
      DWORD status;
      int err;

      if (TerminateProcess(process_handle, 1))
        return 0;

      /* If the process already exited before TerminateProcess was called, */
      /* TerminateProcess will fail with ERROR_ACCESS_DENIED. */
      err = GetLastError();
      if (err == ERROR_ACCESS_DENIED &&
          GetExitCodeProcess(process_handle, &status) &&
          status != STILL_ACTIVE) {
        return UV_ESRCH;
      }

      return uv_translate_sys_error(err);
    }