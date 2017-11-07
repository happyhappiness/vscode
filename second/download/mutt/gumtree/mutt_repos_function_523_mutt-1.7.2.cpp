int mx_lock_file (const char *path, int fd, int excl, int dot, int timeout)
{
#if defined (USE_FCNTL) || defined (USE_FLOCK)
  int count;
  int attempt;
  struct stat sb = { 0 }, prev_sb = { 0 }; /* silence gcc warnings */
#endif
  int r = 0;

#ifdef USE_FCNTL
  struct flock lck;
  
  memset (&lck, 0, sizeof (struct flock));
  lck.l_type = excl ? F_WRLCK : F_RDLCK;
  lck.l_whence = SEEK_SET;

  count = 0;
  attempt = 0;
  while (fcntl (fd, F_SETLK, &lck) == -1)
  {
    dprint(1,(debugfile, "mx_lock_file(): fcntl errno %d.\n", errno));
    if (errno != EAGAIN && errno != EACCES)
    {
      mutt_perror ("fcntl");
      return -1;
    }

    if (fstat (fd, &sb) != 0)
      sb.st_size = 0;
    
    if (count == 0)
      prev_sb = sb;

    /* only unlock file if it is unchanged */
    if (prev_sb.st_size == sb.st_size && ++count >= (timeout?MAXLOCKATTEMPT:0))
    {
      if (timeout)
	mutt_error _("Timeout exceeded while attempting fcntl lock!");
      return -1;
    }

    prev_sb = sb;

    mutt_message (_("Waiting for fcntl lock... %d"), ++attempt);
    sleep (1);
  }
#endif /* USE_FCNTL */

#ifdef USE_FLOCK
  count = 0;
  attempt = 0;
  while (flock (fd, (excl ? LOCK_EX : LOCK_SH) | LOCK_NB) == -1)
  {
    if (errno != EWOULDBLOCK)
    {
      mutt_perror ("flock");
      r = -1;
      break;
    }

    if (fstat(fd, &sb) != 0)
      sb.st_size = 0;
    
    if (count == 0)
      prev_sb = sb;

    /* only unlock file if it is unchanged */
    if (prev_sb.st_size == sb.st_size && ++count >= (timeout?MAXLOCKATTEMPT:0))
    {
      if (timeout)
	mutt_error _("Timeout exceeded while attempting flock lock!");
      r = -1;
      break;
    }

    prev_sb = sb;

    mutt_message (_("Waiting for flock attempt... %d"), ++attempt);
    sleep (1);
  }
#endif /* USE_FLOCK */

#ifdef USE_DOTLOCK
  if (r == 0 && dot)
    r = dotlock_file (path, fd, timeout);
#endif /* USE_DOTLOCK */

  if (r != 0)
  {
    /* release any other locks obtained in this routine */

#ifdef USE_FCNTL
    lck.l_type = F_UNLCK;
    fcntl (fd, F_SETLK, &lck);
#endif /* USE_FCNTL */

#ifdef USE_FLOCK
    flock (fd, LOCK_UN);
#endif /* USE_FLOCK */
  }

  return r;
}