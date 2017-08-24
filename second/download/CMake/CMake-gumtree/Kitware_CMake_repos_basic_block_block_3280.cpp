{
      signal (SIGINT,  mySignalCatcher);
      signal (SIGTERM, mySignalCatcher);
#     if BZ_UNIX
      signal (SIGHUP,  mySignalCatcher);
#     endif
   }