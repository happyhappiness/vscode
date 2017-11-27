static void *exec_read_one (void *arg) /* {{{ */
{
  program_list_t *pl = (program_list_t *) arg;
  int fd, fd_err, highest_fd;
  fd_set fdset, copy;
  int status;
  char buffer[1200];  /* if not completely read */
  char buffer_err[1024];
  char *pbuffer = buffer;
  char *pbuffer_err = buffer_err;

  status = fork_child (pl, NULL, &fd, &fd_err);
  if (status < 0)
  {
    /* Reset the "running" flag */
    pthread_mutex_lock (&pl_lock);
    pl->flags &= ~PL_RUNNING;
    pthread_mutex_unlock (&pl_lock);
    pthread_exit ((void *) 1);
  }
  pl->pid = status;

  assert (pl->pid != 0);

  FD_ZERO( &fdset );
  FD_SET(fd, &fdset);
  FD_SET(fd_err, &fdset);

  /* Determine the highest file descriptor */
  highest_fd = (fd > fd_err) ? fd : fd_err;

  /* We use a copy of fdset, as select modifies it */
  copy = fdset;

  while (1)
  {
    int len;

    status = select (highest_fd + 1, &copy, NULL, NULL, NULL);
    if (status < 0)
    {
      if (errno == EINTR)
        continue;
      break;
    }

    if (FD_ISSET(fd, &copy))
    {
      char *pnl;

      len = read(fd, pbuffer, sizeof(buffer) - 1 - (pbuffer - buffer));

      if (len < 0)
      {
        if (errno == EAGAIN || errno == EINTR)  continue;
        break;
      }
      else if (len == 0) break;  /* We've reached EOF */

      pbuffer[len] = '\0';

      len += pbuffer - buffer;
      pbuffer = buffer;

      while ((pnl = strchr(pbuffer, '\n')))
      {
        *pnl = '\0';
        if (*(pnl-1) == '\r' ) *(pnl-1) = '\0';

        parse_line (pbuffer);

        pbuffer = ++pnl;
      }
      /* not completely read ? */
      if (pbuffer - buffer < len)
      {
        len -= pbuffer - buffer;
        memmove(buffer, pbuffer, len);
        pbuffer = buffer + len;
      }
      else
        pbuffer = buffer;
    }
    else if (FD_ISSET(fd_err, &copy))
    {
      char *pnl;

      len = read(fd_err, pbuffer_err, sizeof(buffer_err) - 1 - (pbuffer_err - buffer_err));

      if (len < 0)
      {
        if (errno == EAGAIN || errno == EINTR)
          continue;
        break;
      }
      else if (len == 0)
      {
        /* We've reached EOF */
        NOTICE ("exec plugin: Program `%s' has closed STDERR.", pl->exec);

        /* Remove file descriptor form select() set. */
        FD_CLR (fd_err, &fdset);
        copy = fdset;
        highest_fd = fd;

        /* Clean up file descriptor */
        close (fd_err);
        fd_err = -1;
        continue;
      }

      pbuffer_err[len] = '\0';

      len += pbuffer_err - buffer_err;
      pbuffer_err = buffer_err;

      while ((pnl = strchr(pbuffer_err, '\n')))
      {
        *pnl = '\0';
        if (*(pnl-1) == '\r' ) *(pnl-1) = '\0';

        ERROR ("exec plugin: exec_read_one: error = %s", pbuffer_err);

        pbuffer_err = ++pnl;
      }
      /* not completely read ? */
      if (pbuffer_err - buffer_err < len)
      {
        len -= pbuffer_err - buffer_err;
        memmove(buffer_err, pbuffer_err, len);
        pbuffer_err = buffer_err + len;
      }
      else
        pbuffer_err = buffer_err;
    }
    /* reset copy */
    copy = fdset;
  }

  DEBUG ("exec plugin: exec_read_one: Waiting for `%s' to exit.", pl->exec);
  if (waitpid (pl->pid, &status, 0) > 0)
    pl->status = status;

  DEBUG ("exec plugin: Child %i exited with status %i.",
      (int) pl->pid, pl->status);

  pl->pid = 0;

  pthread_mutex_lock (&pl_lock);
  pl->flags &= ~PL_RUNNING;
  pthread_mutex_unlock (&pl_lock);

  close (fd);
  if (fd_err >= 0)
    close (fd_err);

  pthread_exit ((void *) 0);
  return (NULL);
}