BOOL amiga_init()
{
  if(!SocketBase)
    SocketBase = OpenLibrary("bsdsocket.library", 4);

  if(!SocketBase) {
    fprintf(stderr, "No TCP/IP Stack running!\n\a");
    return FALSE;
  }

  atexit(amiga_cleanup);
  return TRUE;
}