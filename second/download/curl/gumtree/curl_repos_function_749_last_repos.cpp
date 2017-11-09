static int send_doc(curl_socket_t sock, struct httprequest *req)
{
  ssize_t written;
  size_t count;
  const char *buffer;
  char *ptr = NULL;
  FILE *stream;
  char *cmd = NULL;
  size_t cmdsize = 0;
  FILE *dump;
  bool persistant = TRUE;
  bool sendfailure = FALSE;
  size_t responsesize;
  int error = 0;
  int res;

  static char weare[256];

  char partbuf[80]="data";

  logmsg("Send response number %ld part %ld", req->testno, req->partno);

  switch(req->rcmd) {
  default:
  case RCMD_NORMALREQ:
    break; /* continue with business as usual */
  case RCMD_STREAM:
#define STREAMTHIS "a string to stream 01234567890\n"
    count = strlen(STREAMTHIS);
    for(;;) {
      written = swrite(sock, STREAMTHIS, count);
      if(got_exit_signal)
        return -1;
      if(written != (ssize_t)count) {
        logmsg("Stopped streaming");
        break;
      }
    }
    return -1;
  case RCMD_IDLE:
    /* Do nothing. Sit idle. Pretend it rains. */
    return 0;
  }

  req->open = FALSE;

  if(req->testno < 0) {
    size_t msglen;
    char msgbuf[64];

    switch(req->testno) {
    case DOCNUMBER_QUIT:
      logmsg("Replying to QUIT");
      buffer = docquit;
      break;
    case DOCNUMBER_WERULEZ:
      /* we got a "friends?" question, reply back that we sure are */
      logmsg("Identifying ourselves as friends");
      snprintf(msgbuf, sizeof(msgbuf), "RTSP_SERVER WE ROOLZ: %ld\r\n",
               (long)getpid());
      msglen = strlen(msgbuf);
      snprintf(weare, sizeof(weare),
               "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\n%s",
               msglen, msgbuf);
      buffer = weare;
      break;
    case DOCNUMBER_INTERNAL:
      logmsg("Bailing out due to internal error");
      return -1;
    case DOCNUMBER_CONNECT:
      logmsg("Replying to CONNECT");
      buffer = docconnect;
      break;
    case DOCNUMBER_BADCONNECT:
      logmsg("Replying to a bad CONNECT");
      buffer = docbadconnect;
      break;
    case DOCNUMBER_404:
    default:
      logmsg("Replying to with a 404");
      if(req->protocol == RPROT_HTTP) {
        buffer = doc404_HTTP;
      }
      else {
        buffer = doc404_RTSP;
      }
      break;
    }

    count = strlen(buffer);
  }
  else {
    char *filename = test2file(req->testno);

    if(0 != req->partno)
      snprintf(partbuf, sizeof(partbuf), "data%ld", req->partno);

    stream = fopen(filename, "rb");
    if(!stream) {
      error = errno;
      logmsg("fopen() failed with error: %d %s", error, strerror(error));
      logmsg("Error opening file: %s", filename);
      logmsg("Couldn't open test file");
      return 0;
    }
    else {
      error = getpart(&ptr, &count, "reply", partbuf, stream);
      fclose(stream);
      if(error) {
        logmsg("getpart() failed with error: %d", error);
        return 0;
      }
      buffer = ptr;
    }

    if(got_exit_signal) {
      free(ptr);
      return -1;
    }

    /* re-open the same file again */
    stream = fopen(filename, "rb");
    if(!stream) {
      error = errno;
      logmsg("fopen() failed with error: %d %s", error, strerror(error));
      logmsg("Error opening file: %s", filename);
      logmsg("Couldn't open test file");
      free(ptr);
      return 0;
    }
    else {
      /* get the custom server control "commands" */
      error = getpart(&cmd, &cmdsize, "reply", "postcmd", stream);
      fclose(stream);
      if(error) {
        logmsg("getpart() failed with error: %d", error);
        free(ptr);
        return 0;
      }
    }
  }

  if(got_exit_signal) {
    free(ptr);
    free(cmd);
    return -1;
  }

  /* If the word 'swsclose' is present anywhere in the reply chunk, the
     connection will be closed after the data has been sent to the requesting
     client... */
  if(strstr(buffer, "swsclose") || !count) {
    persistant = FALSE;
    logmsg("connection close instruction \"swsclose\" found in response");
  }
  if(strstr(buffer, "swsbounce")) {
    prevbounce = TRUE;
    logmsg("enable \"swsbounce\" in the next request");
  }
  else
    prevbounce = FALSE;

  dump = fopen(RESPONSE_DUMP, "ab");