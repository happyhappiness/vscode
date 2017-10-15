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

