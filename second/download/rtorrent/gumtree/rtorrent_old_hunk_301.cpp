      if (m_logFd != -1) {
        write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
        write(m_logFd, m_capture.data(), m_capture.length());
      }
    }

    int status;
    int wpid = waitpid(childPid, &status, 0);

    while (wpid == -1 && rak::error_number::current().value() == rak::error_number::e_intr)
      wpid = waitpid(childPid, &status, 0);

    if (wpid != childPid)
      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

    // Check return value?
    if (m_logFd != -1) {
