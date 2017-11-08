void logmsg(const char *msg, ...)
{
  va_list ap;
  char buffer[512]; /* possible overflow if you pass in a huge string */
  FILE *logfp;
  int error;
  struct timeval tv;
  time_t sec;
  struct tm *now;
  char timebuf[20];

  if (!serverlogfile) {
    fprintf(stderr, "Error: serverlogfile not set\n");
    return;
  }

  tv = curlx_tvnow();
  sec = tv.tv_sec;
  now = localtime(&sec); /* not multithread safe but we don't care */

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
  else {
    error = ERRNO;
    fprintf(stderr, "fopen() failed with error: %d %s\n",
            error, strerror(error));
    fprintf(stderr, "Error opening file: %s\n", serverlogfile);
    fprintf(stderr, "Msg not logged: %s %s\n", timebuf, buffer);
  }
}