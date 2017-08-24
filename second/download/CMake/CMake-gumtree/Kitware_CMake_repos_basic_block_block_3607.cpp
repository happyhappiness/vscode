{

        int flags = 0;
        if(0 != ioctlsocket(0, FIONBIO, &flags))
          return 1;

  ;
  return 0;
}