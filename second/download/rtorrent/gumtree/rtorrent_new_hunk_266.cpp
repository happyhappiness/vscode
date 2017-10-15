    int result = execvp(file, argv);

    _exit(result);

  } else {
    int status;
    int wpid = waitpid(childPid, &status, 0);

    while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr)
      wpid = waitpid(childPid, &status, 0);

    if (wpid != childPid)
      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

    // Check return value?
    if (m_logFd) {
      if (status == 0)
        write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
