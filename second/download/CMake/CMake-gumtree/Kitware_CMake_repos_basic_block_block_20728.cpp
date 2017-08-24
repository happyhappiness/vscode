(!AssignProcessToJobObject(uv_global_job_handle_, info.hProcess)) {
      /* AssignProcessToJobObject might fail if this process is under job
       * control and the job doesn't have the
       * JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK flag set, on a Windows version
       * that doesn't support nested jobs.
       *
       * When that happens we just swallow the error and continue without
       * establishing a kill-child-on-parent-exit relationship, otherwise
       * there would be no way for libuv applications run under job control
       * to spawn processes at all.
       */
      DWORD err = GetLastError();
      if (err != ERROR_ACCESS_DENIED)
        uv_fatal_error(err, "AssignProcessToJobObject");
    }