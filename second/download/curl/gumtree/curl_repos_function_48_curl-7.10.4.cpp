static int send_doc(int sock, int doc, int part_no)
{
  int written;
  int count;
  const char *buffer;
  char *ptr;
  FILE *stream;
  char *cmd=NULL;
  int cmdsize=0;
  FILE *dump;

  static char weare[256];

  char filename[256];
  char partbuf[80]="data";

  if(doc < 0) {
    switch(doc) {
    case DOCNUMBER_WERULEZ:
      /* we got a "friends?" question, reply back that we sure are */
      logmsg("Identifying ourselves as friends");
      sprintf(weare, "HTTP/1.1 200 OK\r\n\r\nWE ROOLZ: %d\r\n",
              (int)getpid());
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
    logmsg("Fetch response data");

    if(0 != part_no)
      sprintf(partbuf, "data%d", part_no);

    sprintf(filename, TEST_DATA_PATH, doc);

    stream=fopen(filename, "rb");
    if(!stream) {
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
    logmsg("couldn't create logfile: " RESPONSE_DUMP);
    return -1;
  }

  do {
    written = send(sock, buffer, count, 0);
    if (written < 0) {
      logmsg("Sending response failed and we bailed out!");
      return -1;
    }
    /* write to file as well */
    fwrite(buffer, 1, written, dump);

    count -= written;
    buffer += written;
  } while(count>0);

  fclose(dump);

  logmsg("Response sent!");

  if(ptr)
    free(ptr);

  if(cmdsize > 0 ) {
    char command[32];
    int num;
    char *ptr=cmd;
    do {
      if(2 == sscanf(ptr, "%31s %d", command, &num)) {
        if(!strcmp("wait", command))
          sleep(num); /* wait this many seconds */
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

  return 0;
}