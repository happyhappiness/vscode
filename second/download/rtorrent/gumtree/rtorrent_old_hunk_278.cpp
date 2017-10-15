      write(m_logFd, *itr, std::strlen(*itr));
    }

    write(m_logFd, "\n---\n", sizeof("\n---\n"));
  }

  pid_t childPid = fork();

  if (childPid == -1)
    throw torrent::input_error("ExecFile::execute(...) Fork failed.");

  if (childPid == 0) {
    ::close(0);
    ::close(1);
    ::close(2);

    if (m_logFd != -1) {
      dup2(m_logFd, 1);
      dup2(m_logFd, 2);
    }

    // Close all fd's.
    for (int i = 3, last = sysconf(_SC_OPEN_MAX); i != last; i++)
      ::close(i);

    int result = execvp(file, argv);

    _exit(result);

  } else {
    int status;
    int wpid = waitpid(childPid, &status, 0);

    while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr)
      wpid = waitpid(childPid, &status, 0);

