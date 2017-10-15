int
ExecFile::execute(const char* file, char* const* argv, int flags) {
  // Write the execued command and its parameters to the log fd.
  int __UNUSED result;

  if (m_logFd != -1) {
    for (char* const* itr = argv; *itr != NULL; itr++) {
      if (itr == argv)
        result = write(m_logFd, "\n---\n", sizeof("\n---\n"));
      else
        result = write(m_logFd, " ", 1);

      result = write(m_logFd, *itr, std::strlen(*itr));
    }

    result = write(m_logFd, "\n---\n", sizeof("\n---\n"));
  }

  int pipeFd[2];

  if ((flags & flag_capture) && pipe(pipeFd))
    throw torrent::input_error("ExecFile::execute(...) Pipe creation failed.");

  pid_t childPid = fork();

  if (childPid == -1)
    throw torrent::input_error("ExecFile::execute(...) Fork failed.");

  if (childPid == 0) {
    if (flags & flag_background) {
      pid_t detached_pid = fork();

      if (detached_pid == -1)
        _exit(-1);

      if (detached_pid != 0) {
        if (m_logFd != -1)
          result = write(m_logFd, "\n--- Background task ---\n", sizeof("\n--- Background task ---\n"));
        
        _exit(0);
      }

      m_logFd = -1;
      flags &= ~flag_capture;
    }

    int devNull = open("/dev/null", O_RDWR);
    if (devNull != -1)
      dup2(devNull, 0);
    else
      ::close(0);

    if (flags & flag_capture)
      dup2(pipeFd[1], 1);
    else if (m_logFd != -1)
      dup2(m_logFd, 1);
    else if (devNull != -1)
      dup2(devNull, 1);
    else
      ::close(1);

    if (m_logFd != -1)
      dup2(m_logFd, 2);
    else if (devNull != -1)
      dup2(devNull, 2);
    else
      ::close(2);

    // Close all fd's.
    for (int i = 3, last = sysconf(_SC_OPEN_MAX); i != last; i++)
      ::close(i);

    int result = execvp(file, argv);

    _exit(result);
  }

  // We yield the global lock when waiting for the executed command to
  // finish so that XMLRPC and other threads can continue working.
  ThreadBase::release_global_lock();

  if (flags & flag_capture) {
    m_capture = std::string();
    ::close(pipeFd[1]);

    char buffer[4096];
    ssize_t length;

    do {
      length = read(pipeFd[0], buffer, sizeof(buffer));

      if (length > 0)
        m_capture += std::string(buffer, length);
    } while (length > 0);

    ::close(pipeFd[0]);

    if (m_logFd != -1) {
      result = write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
      result = write(m_logFd, m_capture.data(), m_capture.length());
    }
  }

  int status;
  int wpid;

  do {
    wpid = waitpid(childPid, &status, 0);
  } while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr);

  ThreadBase::acquire_global_lock();

  if (wpid != childPid)
    throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

  // Check return value?
  if (m_logFd != -1) {
    if (status == 0)
      result = write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
    else
      result = write(m_logFd, "\n--- Error ---\n", sizeof("\n--- Error ---\n"));
  }

  return status;
}