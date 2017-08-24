(total < KWSYSPE_PIPE_BUFFER_SIZE && n > 0) {
      /* Keep trying to read until the operation is not interrupted.  */
      while (((n = read(si->ErrorPipe[0], cp->ErrorMessage + total,
                        (size_t)(KWSYSPE_PIPE_BUFFER_SIZE - total))) < 0) &&
             (errno == EINTR))
        ;
      if (n > 0) {
        total += n;
      }
    }