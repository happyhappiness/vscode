int
poll (struct pollfd *pfd, nfds_t nfd, int timeout)
{
#ifndef WIN32_NATIVE
  fd_set rfds, wfds, efds;
  struct timeval tv;
  struct timeval *ptv;
  int maxfd, rc;
  nfds_t i;

# ifdef _SC_OPEN_MAX
  static int sc_open_max = -1;

  if (nfd < 0
      || (nfd > sc_open_max
	  && (sc_open_max != -1
	      || nfd > (sc_open_max = sysconf (_SC_OPEN_MAX)))))
    {
      errno = EINVAL;
      return -1;
    }
# else /* !_SC_OPEN_MAX */
#  ifdef OPEN_MAX
  if (nfd < 0 || nfd > OPEN_MAX)
    {
      errno = EINVAL;
      return -1;
    }
#  endif /* OPEN_MAX -- else, no check is needed */
# endif /* !_SC_OPEN_MAX */

  /* EFAULT is not necessary to implement, but let's do it in the
     simplest case. */
  if (!pfd && nfd)
    {
      errno = EFAULT;
      return -1;
    }

  /* convert timeout number into a timeval structure */
  if (timeout == 0)
    {
      ptv = &tv;
      ptv->tv_sec = 0;
      ptv->tv_usec = 0;
    }
  else if (timeout > 0)
    {
      ptv = &tv;
      ptv->tv_sec = timeout / 1000;
      ptv->tv_usec = (timeout % 1000) * 1000;
    }
  else if (timeout == INFTIM)
    /* wait forever */
    ptv = NULL;
  else
    {
      errno = EINVAL;
      return -1;
    }

  /* create fd sets and determine max fd */
  maxfd = -1;
  FD_ZERO (&rfds);
  FD_ZERO (&wfds);
  FD_ZERO (&efds);
  for (i = 0; i < nfd; i++)
    {
      if (pfd[i].fd < 0)
	continue;

      if (pfd[i].events & (POLLIN | POLLRDNORM))
	FD_SET (pfd[i].fd, &rfds);

      /* see select(2): "the only exceptional condition detectable
	 is out-of-band data received on a socket", hence we push
	 POLLWRBAND events onto wfds instead of efds. */
      if (pfd[i].events & (POLLOUT | POLLWRNORM | POLLWRBAND))
	FD_SET (pfd[i].fd, &wfds);
      if (pfd[i].events & (POLLPRI | POLLRDBAND))
	FD_SET (pfd[i].fd, &efds);
      if (pfd[i].fd >= maxfd
	  && (pfd[i].events & (POLLIN | POLLOUT | POLLPRI
			       | POLLRDNORM | POLLRDBAND
			       | POLLWRNORM | POLLWRBAND)))
	{
	  maxfd = pfd[i].fd;
	  if (maxfd > FD_SETSIZE)
	    {
	      errno = EOVERFLOW;
	      return -1;
	    }
	}
    }

  /* examine fd sets */
  rc = select (maxfd + 1, &rfds, &wfds, &efds, ptv);
  if (rc < 0)
    return rc;

  /* establish results */
  rc = 0;
  for (i = 0; i < nfd; i++)
    if (pfd[i].fd < 0)
      pfd[i].revents = 0;
    else
      {
	int happened = compute_revents (pfd[i].fd, pfd[i].events,
					&rfds, &wfds, &efds);
	if (happened)
	  {
	    pfd[i].revents = happened;
	    rc++;
	  }
      }

  return rc;
#else
  static struct timeval tv0;
  static HANDLE hEvent;
  WSANETWORKEVENTS ev;
  HANDLE h, handle_array[FD_SETSIZE + 2];
  DWORD ret, wait_timeout, nhandles, start = 0, elapsed, orig_timeout = 0;
  fd_set rfds, wfds, xfds;
  BOOL poll_again;
  MSG msg;
  int rc = 0;
  nfds_t i;

  if (nfd < 0 || timeout < -1)
    {
      errno = EINVAL;
      return -1;
    }

  if (timeout != INFTIM)
    {
      orig_timeout = timeout;
      start = GetTickCount();
    }

  if (!hEvent)
    hEvent = CreateEvent (NULL, FALSE, FALSE, NULL);

restart:
  handle_array[0] = hEvent;
  nhandles = 1;
  FD_ZERO (&rfds);
  FD_ZERO (&wfds);
  FD_ZERO (&xfds);

  /* Classify socket handles and create fd sets. */
  for (i = 0; i < nfd; i++)
    {
      int sought = pfd[i].events;
      pfd[i].revents = 0;
      if (pfd[i].fd < 0)
	continue;
      if (!(sought & (POLLIN | POLLRDNORM | POLLOUT | POLLWRNORM | POLLWRBAND
		      | POLLPRI | POLLRDBAND)))
	continue;

      h = (HANDLE) _get_osfhandle (pfd[i].fd);
      assert (h != NULL);
      if (IsSocketHandle (h))
	{
	  int requested = FD_CLOSE;

	  /* see above; socket handles are mapped onto select.  */
	  if (sought & (POLLIN | POLLRDNORM))
	    {
	      requested |= FD_READ | FD_ACCEPT;
	      FD_SET ((SOCKET) h, &rfds);
	    }
	  if (sought & (POLLOUT | POLLWRNORM | POLLWRBAND))
	    {
	      requested |= FD_WRITE | FD_CONNECT;
	      FD_SET ((SOCKET) h, &wfds);
	    }
	  if (sought & (POLLPRI | POLLRDBAND))
	    {
	      requested |= FD_OOB;
	      FD_SET ((SOCKET) h, &xfds);
	    }

	  if (requested)
	    WSAEventSelect ((SOCKET) h, hEvent, requested