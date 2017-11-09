void curl_memdebug(const char *logname)
{
  if(!logfile) {
    if(logname && *logname)
      logfile = fopen(logname, FOPEN_WRITETEXT);
    else
      logfile = stderr;
#ifdef MEMDEBUG_LOG_SYNC
    /* Flush the log file after every line so the log isn't lost in a crash */
    if(logfile)
      setbuf(logfile, (char *)NULL);
#endif
  }
}