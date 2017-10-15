    int result = execvp(file, argv);

    _exit(result);

  } else {
    int status;

    if (waitpid(childPid, &status, 0) != childPid)
      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

    // Check return value?
    if (m_logFd) {
      if (status == 0)
        write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
