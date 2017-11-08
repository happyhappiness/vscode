void logmsg(const char *msg, ...)
{
  va_list ap;
  char buffer[256]; /* possible overflow if you pass in a huge string */
  FILE *logfp;

  struct timeval tv = curlx_tvnow();
  struct tm *now =
    localtime(&tv.tv_sec); /* not multithread safe but we don't care */

  char timebuf[20];
  snprintf(timebuf, sizeof(timebuf), "%02d:%02d:%02d.%06ld",
           now->tm_hour, now->tm_min, now->tm_sec, tv.tv_usec);

  va_start(ap, msg);
  vsprintf(buffer, msg, ap);
  va_end(ap);

  logfp = fopen(serverlogfile, "a");
  if(logfp) {
    fprintf(logfp, "%s %s\n", timebuf, buffer);
    fclose(logfp);
  }
}