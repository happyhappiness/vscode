      write(m_logFd, *itr, std::strlen(*itr));
    }

    write(m_logFd, "\n---\n", sizeof("\n---\n"));
  }

  int pipeFd[2];

  if ((flags & flag_capture) && pipe(pipeFd))
    throw torrent::input_error("ExecFile::execute(...) Pipe creation failed.");

  pid_t childPid = fork();

  if (childPid == -1)
    throw torrent::input_error("ExecFile::execute(...) Fork failed.");

  if (childPid == 0) {
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

  } else {
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

      if (m_logFd != -1) {
        write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
        write(m_logFd, m_capture.data(), m_capture.length());
      }
    }

    int status;
    int wpid = waitpid(childPid, &status, 0);

    while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr)
      wpid = waitpid(childPid, &status, 0);

