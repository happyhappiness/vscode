{
  int i;
  int err = 0;
  WCHAR* path = NULL, *alloc_path = NULL;
  BOOL result;
  WCHAR* application_path = NULL, *application = NULL, *arguments = NULL,
         *env = NULL, *cwd = NULL;
  STARTUPINFOW startup;
  PROCESS_INFORMATION info;
  DWORD process_flags;

  uv_process_init(loop, process);
  process->exit_cb = options->exit_cb;

  if (options->flags & (UV_PROCESS_SETGID | UV_PROCESS_SETUID)) {
    return UV_ENOTSUP;
  }

  if (options->file == NULL ||
      options->args == NULL) {
    return UV_EINVAL;
  }

  assert(options->file != NULL);
  assert(!(options->flags & ~(UV_PROCESS_DETACHED |
                              UV_PROCESS_SETGID |
                              UV_PROCESS_SETUID |
                              UV_PROCESS_WINDOWS_HIDE |
                              UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS)));

  err = uv_utf8_to_utf16_alloc(options->file, &application);
  if (err)
    goto done;

  err = make_program_args(
      options->args,
      options->flags & UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS,
      &arguments);
  if (err)
    goto done;

  if (options->env) {
     err = make_program_env(options->env, &env);
     if (err)
       goto done;
  }

  if (options->cwd) {
    /* Explicit cwd */
    err = uv_utf8_to_utf16_alloc(options->cwd, &cwd);
    if (err)
      goto done;

  } else {
    /* Inherit cwd */
    DWORD cwd_len, r;

    cwd_len = GetCurrentDirectoryW(0, NULL);
    if (!cwd_len) {
      err = GetLastError();
      goto done;
    }

    cwd = (WCHAR*) uv__malloc(cwd_len * sizeof(WCHAR));
    if (cwd == NULL) {
      err = ERROR_OUTOFMEMORY;
      goto done;
    }

    r = GetCurrentDirectoryW(cwd_len, cwd);
    if (r == 0 || r >= cwd_len) {
      err = GetLastError();
      goto done;
    }
  }

  /* Get PATH environment variable. */
  path = find_path(env);
  if (path == NULL) {
    DWORD path_len, r;

    path_len = GetEnvironmentVariableW(L"PATH", NULL, 0);
    if (path_len == 0) {
      err = GetLastError();
      goto done;
    }

    alloc_path = (WCHAR*) uv__malloc(path_len * sizeof(WCHAR));
    if (alloc_path == NULL) {
      err = ERROR_OUTOFMEMORY;
      goto done;
    }
    path = alloc_path;

    r = GetEnvironmentVariableW(L"PATH", path, path_len);
    if (r == 0 || r >= path_len) {
      err = GetLastError();
      goto done;
    }
  }

  err = uv__stdio_create(loop, options, &process->child_stdio_buffer);
  if (err)
    goto done;

  application_path = search_path(application,
                                 cwd,
                                 path);
  if (application_path == NULL) {
    /* Not found. */
    err = ERROR_FILE_NOT_FOUND;
    goto done;
  }

  startup.cb = sizeof(startup);
  startup.lpReserved = NULL;
  startup.lpDesktop = NULL;
  startup.lpTitle = NULL;
  startup.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

  startup.cbReserved2 = uv__stdio_size(process->child_stdio_buffer);
  startup.lpReserved2 = (BYTE*) process->child_stdio_buffer;

  startup.hStdInput = uv__stdio_handle(process->child_stdio_buffer, 0);
  startup.hStdOutput = uv__stdio_handle(process->child_stdio_buffer, 1);
  startup.hStdError = uv__stdio_handle(process->child_stdio_buffer, 2);

  if (options->flags & UV_PROCESS_WINDOWS_HIDE) {
    /* Use SW_HIDE to avoid any potential process window. */
    startup.wShowWindow = SW_HIDE;
  } else {
    startup.wShowWindow = SW_SHOWDEFAULT;
  }

  process_flags = CREATE_UNICODE_ENVIRONMENT;

  if (options->flags & UV_PROCESS_DETACHED) {
    /* Note that we're not setting the CREATE_BREAKAWAY_FROM_JOB flag. That
     * means that libuv might not let you create a fully daemonized process
     * when run under job control. However the type of job control that libuv
     * itself creates doesn't trickle down to subprocesses so they can still
     * daemonize.
     *
     * A reason to not do this is that CREATE_BREAKAWAY_FROM_JOB makes the
     * CreateProcess call fail if we're under job control that doesn't allow
     * breakaway.
     */
    process_flags |= DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP;
  }

  if (!CreateProcessW(application_path,
                     arguments,
                     NULL,
                     NULL,
                     1,
                     process_flags,
                     env,
                     cwd,
                     &startup,
                     &info)) {
    /* CreateProcessW failed. */
    err = GetLastError();
    goto done;
  }

  /* Spawn succeeded */
  /* Beyond this point, failure is reported asynchronously. */

  process->process_handle = info.hProcess;
  process->pid = info.dwProcessId;

  /* If the process isn't spawned as detached, assign to the global job */
  /* object so windows will kill it when the parent process dies. */
  if (!(options->flags & UV_PROCESS_DETACHED)) {
    uv_once(&uv_global_job_handle_init_guard_, uv__init_global_job_handle);

    if (!AssignProcessToJobObject(uv_global_job_handle_, info.hProcess)) {
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
  }

  /* Set IPC pid to all IPC pipes. */
  for (i = 0; i < options->stdio_count; i++) {
    const uv_stdio_container_t* fdopt = &options->stdio[i];
    if (fdopt->flags & UV_CREATE_PIPE &&
        fdopt->data.stream->type == UV_NAMED_PIPE &&
        ((uv_pipe_t*) fdopt->data.stream)->ipc) {
      ((uv_pipe_t*) fdopt->data.stream)->pipe.conn.ipc_pid = info.dwProcessId;
    }
  }

  /* Setup notifications for when the child process exits. */
  result = RegisterWaitForSingleObject(&process->wait_handle,
      process->process_handle, exit_wait_callback, (void*)process, INFINITE,
      WT_EXECUTEINWAITTHREAD | WT_EXECUTEONLYONCE);
  if (!result) {
    uv_fatal_error(GetLastError(), "RegisterWaitForSingleObject");
  }

  CloseHandle(info.hThread);

  assert(!err);

  /* Make the handle active. It will remain active until the exit callback */
  /* is made or the handle is closed, whichever happens first. */
  uv__handle_start(process);

  /* Cleanup, whether we succeeded or failed. */
 done:
  uv__free(application);
  uv__free(application_path);
  uv__free(arguments);
  uv__free(cwd);
  uv__free(env);
  uv__free(alloc_path);

  if (process->child_stdio_buffer != NULL) {
    /* Clean up child stdio handles. */
    uv__stdio_destroy(process->child_stdio_buffer);
    process->child_stdio_buffer = NULL;
  }

  return uv_translate_sys_error(err);
}