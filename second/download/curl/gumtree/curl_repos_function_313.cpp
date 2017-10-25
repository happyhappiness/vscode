void curl_memdebug(const char *logname)
{
  if(logname)
    logfile = fopen(logname, "w");
  else
    logfile = stderr;
}