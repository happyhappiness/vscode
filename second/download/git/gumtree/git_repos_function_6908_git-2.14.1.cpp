static int
win32_compute_revents_socket (SOCKET h, int sought, long lNetworkEvents)
{
  int happened = 0;

  if ((lNetworkEvents & (FD_READ | FD_ACCEPT | FD_CLOSE)) == FD_ACCEPT)
    happened |= (POLLIN | POLLRDNORM) & sought;

  else if (lNetworkEvents & (FD_READ | FD_ACCEPT | FD_CLOSE))
    {
      int r, error;

      char data[64];
      WSASetLastError (0);
      r = recv (h, data, sizeof (data), MSG_PEEK);
      error = WSAGetLastError ();
      WSASetLastError (0);

      if (r > 0 || error == WSAENOTCONN)
	happened |= (POLLIN | POLLRDNORM) & sought;

      /* Distinguish hung-up sockets from other errors.  */
      else if (r == 0 || error == WSAESHUTDOWN || error == WSAECONNRESET
	       || error == WSAECONNABORTED || error == WSAENETRESET)
	happened |= POLLHUP;

      else
	happened |= POLLERR;
    }

  if (lNetworkEvents & (FD_WRITE | FD_CONNECT))
    happened |= (POLLOUT | POLLWRNORM | POLLWRBAND) & sought;

  if (lNetworkEvents & FD_OOB)
    happened |= (POLLPRI | POLLRDBAND) & sought;

  return happened;
}