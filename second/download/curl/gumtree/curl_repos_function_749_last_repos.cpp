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
  if(!dump) {
    error = errno;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("Error opening file: %s", RESPONSE_DUMP);
    logmsg("couldn't create logfile: " RESPONSE_DUMP);
    free(ptr);
    free(cmd);
    return -1;
  }

  responsesize = count;
  do {
    /* Ok, we send no more than 200 bytes at a time, just to make sure that
       larger chunks are split up so that the client will need to do multiple
       recv() calls to get it and thus we exercise that code better */
    size_t num = count;
    if(num > 200)
      num = 200;
    written = swrite(sock, buffer, num);
    if(written < 0) {
      sendfailure = TRUE;
      break;
    }
    else {
      logmsg("Sent off %zd bytes", written);
    }
    /* write to file as well */
    fwrite(buffer, 1, (size_t)written, dump);
    if(got_exit_signal)
      break;

    count -= written;
    buffer += written;
  } while(count>0);

  /* Send out any RTP data */
  if(req->rtp_buffer) {
    logmsg("About to write %zu RTP bytes", req->rtp_buffersize);
    count = req->rtp_buffersize;
    do {
      size_t num = count;
      if(num > 200)
        num = 200;
      written = swrite(sock, req->rtp_buffer + (req->rtp_buffersize - count),
                       num);
      if(written < 0) {
        sendfailure = TRUE;
        break;
      }
      count -= written;
    } while(count > 0);

    free(req->rtp_buffer);
    req->rtp_buffersize = 0;
  }

  do {
    res = fclose(dump);
  } while(res && ((error = errno) == EINTR));
  if(res)
    logmsg("Error closing file %s error: %d %s",
           RESPONSE_DUMP, error, strerror(error));

  if(got_exit_signal) {
    free(ptr);
    free(cmd);
    return -1;
  }

  if(sendfailure) {
    logmsg("Sending response failed. Only (%zu bytes) of "
           "(%zu bytes) were sent",
           responsesize-count, responsesize);
    free(ptr);
    free(cmd);
    return -1;
  }

  logmsg("Response sent (%zu bytes) and written to " RESPONSE_DUMP,
         responsesize);
  free(ptr);

  if(cmdsize > 0) {
    char command[32];
    int quarters;
    int num;
    ptr = cmd;
    do {
      if(2 == sscanf(ptr, "%31s %d", command, &num)) {
        if(!strcmp("wait", command)) {
          logmsg("Told to sleep for %d seconds", num);
          quarters = num * 4;
          while(quarters > 0) {
            quarters--;
            res = wait_ms(250);
            if(got_exit_signal)
              break;
            if(res) {
              /* should not happen */
              error = errno;
              logmsg("wait_ms() failed with error: (%d) %s",
                     error, strerror(error));
              break;
            }
          }
          if(!quarters)
            logmsg("Continuing after sleeping %d seconds", num);
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
  free(cmd);
  req->open = persistant;

  prevtestno = req->testno;
  prevpartno = req->partno;

  return 0;
}