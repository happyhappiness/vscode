void curl_memdebug(const char *logname)
{
  if(!logfile) {
    if(logname)
      logfile = fopen(logname, "w");
    else
      logfile = stderr;
#ifdef MEMDEBUG_LOG_SYNC
    /* Flush the log file after every line so the log isn't lost in a crash */
    setvbuf(logfile, (char *)NULL, _IOLBF, 0);
#endif
  }
}