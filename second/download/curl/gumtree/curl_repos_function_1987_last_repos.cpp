bool Curl_amiga_init()
{
  if(!SocketBase)
    SocketBase = OpenLibrary("bsdsocket.library", 4);

  if(!SocketBase) {
    __request("No TCP/IP Stack running!");
    return FALSE;
  }

  if(SocketBaseTags(SBTM_SETVAL(SBTC_ERRNOPTR(sizeof(errno))), (ULONG) &errno,
                    SBTM_SETVAL(SBTC_LOGTAGPTR), (ULONG) "curl",
                    TAG_DONE)) {
    __request("SocketBaseTags ERROR");
    return FALSE;
  }

#ifndef __libnix__
  atexit(Curl_amiga_cleanup);
#endif

  return TRUE;
}