int Curl_nonblock(int socket,    /* operate on this */
                  int nonblock   /* TRUE or FALSE */)
{
#undef SETBLOCK
#ifdef HAVE_O_NONBLOCK
  int flags;

  flags = fcntl(socket, F_GETFL, 0);
  if (TRUE == nonblock)
    return fcntl(socket, F_SETFL, flags | O_NONBLOCK);
  else
    return fcntl(socket, F_SETFL, flags & (~O_NONBLOCK));
#define SETBLOCK 1
#endif

#ifdef HAVE_FIONBIO
  int flags;

  flags = nonblock;
  return ioctl(socket, FIONBIO, &flags);
#define SETBLOCK 2
#endif

#ifdef HAVE_IOCTLSOCKET
  int flags;
  flags = nonblock;
  return ioctlsocket(socket, FIONBIO, &flags);
#define SETBLOCK 3
#endif

#ifdef HAVE_IOCTLSOCKET_CASE
  return IoctlSocket(socket, FIONBIO, (long)nonblock);
#define SETBLOCK 4
#endif

#ifdef HAVE_DISABLED_NONBLOCKING
  return 0; /* returns success */
#define SETBLOCK 5
#endif

#ifndef SETBLOCK
#error "no non-blocking method was found/used/set"
#endif
}