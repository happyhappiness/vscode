void logmsg(const char *msg, ...)
{
  va_list ap;
  char buffer[2048 + 1];
  FILE *logfp;
  int error;
  struct timeval tv;
  time_t sec;
  struct tm *now;
  char timebuf[20];
  static time_t epoch_offset;
  static int    known_offset;

  if (!serverlogfile) {
    fprintf(stderr, "Error: serverlogfile not set\n");
    return;
  }

  tv = curlx_tvnow();
  if(!known_offset) {
    epoch_offset = time(NULL) - tv.tv_sec;
    known_offset = 1;
  }
  sec = epoch_offset + tv.tv_sec;
  now = localtime(&sec); /* not thread safe but we don't care */

  snprintf(timebuf, sizeof(timebuf), "%02d:%02d:%02d.%06ld",
    (int)now->tm_hour, (int)now->tm_min, (int)now->tm_sec, (long)tv.tv_usec);

  va_start(ap, msg);
  vsnprintf(buffer, sizeof(buffer), msg, ap);
  va_end(ap);

  logfp = fopen(serverlogfile, "ab");
  if(logfp) {
    fprintf(logfp, "%s %s\n", timebuf, buffer);
    fclose(logfp);
  }
  else {
    error = errno;
    fprintf(stderr, "fopen() failed with error: %d %s\n",
            error, strerror(error));
    fprintf(stderr, "Error opening file: %s\n", serverlogfile);
    fprintf(stderr, "Msg not logged: %s %s\n", timebuf, buffer);
  }
}