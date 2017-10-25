void amiga_cleanup()
{
  if(SocketBase)
    CloseLibrary(SocketBase);

  SocketBase = NULL;
}