      wpid = waitpid(childPid, &status, 0);

    if (wpid != childPid)
      throw torrent::internal_error("ExecFile::execute(...) waitpid failed.");

    // Check return value?
    if (m_logFd) {
      if (status == 0)
        write(m_logFd, "\n--- Success ---\n", sizeof("\n--- Success ---\n"));
      else
        write(m_logFd, "\n--- Error ---\n", sizeof("\n--- Error ---\n"));
    }

