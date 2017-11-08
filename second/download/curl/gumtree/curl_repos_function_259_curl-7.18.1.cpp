static int send_doc(curl_socket_t sock, struct httprequest *req)
{
  ssize_t written;
  size_t count;
  const char *buffer;
  char *ptr;
  FILE *stream;
  char *cmd=NULL;
  size_t cmdsize=0;
  FILE *dump;
  bool persistant = TRUE;
  size_t responsesize;
  int error;

  static char weare[256];

  char partbuf[80]="data";

  logmsg("Send response number %d part %d", req->testno, req->partno);

  switch(req->rcmd) {
  default:
  case RCMD_NORMALREQ:
    break; /* continue with business as usual */
  case RCMD_STREAM:
#define STREAMTHIS "a string to stream 01234567890\n"
    count = strlen(STREAMTHIS);
    while(1) {
      written = swrite(sock, STREAMTHIS, count);
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
      sprintf(msgbuf, "WE ROOLZ: %ld\r\n", (long)getpid());
      msglen = strlen(msgbuf);
      sprintf(weare, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s",
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
      buffer = doc404;
      break;
    }
    ptr = NULL;
    stream=NULL;

    count = strlen(buffer);
  }
  else {
    char *filename = test2file(req->testno);

    if(0 != req->partno)
      sprintf(partbuf, "data%ld", req->partno);

    stream=fopen(filename, "rb");
    if(!stream) {
      error = ERRNO;
      logmsg("fopen() failed with error: %d %s", error, strerror(error));
      logmsg("Error opening file: %s", filename);
      logmsg("Couldn't open test file");
      return 0;
    }
    else {
      buffer = spitout(stream, "reply", partbuf, &count);
      ptr = (char *)buffer;
      fclose(stream);
    }

    /* re-open the same file again */
    stream=fopen(filename, "rb");
    if(!stream) {
      error = ERRNO;
      logmsg("fopen() failed with error: %d %s", error, strerror(error));
      logmsg("Error opening file: %s", filename);
      logmsg("Couldn't open test file");
      return 0;
    }
    else {
      /* get the custom server control "commands" */
      cmd = (char *)spitout(stream, "reply", "postcmd", &cmdsize);
      fclose(stream);
    }
  }

  dump = fopen(RESPONSE_DUMP, "ab"); /* b is for windows-preparing */
  if(!dump) {
    error = ERRNO;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("Error opening file: %s", RESPONSE_DUMP);
    logmsg("couldn't create logfile: " RESPONSE_DUMP);
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


  responsesize = count;
  do {
    /* Ok, we send no more than 200 bytes at a time, just to make sure that
       larger chunks are split up so that the client will need to do multiple
       recv() calls to get it and thus we exercise that code better */
    size_t num = count;
    if(num > 200)
      num = 200;
    written = swrite(sock, buffer, num);
    if (written < 0) {
      fclose(dump);
      logmsg("Sending response failed and we bailed out!");
      return -1;
    }
    else {
      logmsg("Sent off %d bytes", written);
    }
    /* write to file as well */
    fwrite(buffer, 1, written, dump);

    count -= written;
    buffer += written;
  } while(count>0);

  fclose(dump);

  logmsg("Response sent (%d bytes) and written to " RESPONSE_DUMP,
         responsesize);

  if(ptr)
    free(ptr);

  if(cmdsize > 0 ) {
    char command[32];
    int num;
    ptr=cmd;
    do {
      if(2 == sscanf(ptr, "%31s %d", command, &num)) {
        if(!strcmp("wait", command)) {
          logmsg("Told to sleep for %d seconds", num);
          sleep(num); /* wait this many seconds */
        }
        else
          logmsg("Unknown command in reply command section");
      }
      ptr = strchr(ptr, '\n');
      if(ptr)
        ptr++;
      else
        ptr = NULL;
    } while(ptr && *ptr);
  }
  if(cmd)
    free(cmd);

  req->open = persistant;

  prevtestno = req->testno;
  prevpartno = req->partno;

  return 0;
}