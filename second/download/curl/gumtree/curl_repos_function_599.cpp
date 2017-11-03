static int parse_servercmd(struct httprequest *req)
{
  FILE *stream;
  char *filename;
  int error;

  filename = test2file(req->testno);

  stream=fopen(filename, "rb");
  if(!stream) {
    error = errno;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("  [1] Error opening file: %s", filename);
    logmsg("  Couldn't open test file %ld", req->testno);
    req->open = FALSE; /* closes connection */
    return 1; /* done */
  }
  else {
    char *orgcmd = NULL;
    char *cmd = NULL;
    size_t cmdsize = 0;
    int num=0;

    /* get the custom server control "commands" */
    error = getpart(&orgcmd, &cmdsize, "reply", "servercmd", stream);
    fclose(stream);
    if(error) {
      logmsg("getpart() failed with error: %d", error);
      req->open = FALSE; /* closes connection */
      return 1; /* done */
    }

    req->connmon = FALSE;

    cmd = orgcmd;
    while(cmd && cmdsize) {
      char *check;

      if(!strncmp(CMD_AUTH_REQUIRED, cmd, strlen(CMD_AUTH_REQUIRED))) {
        logmsg("instructed to require authorization header");
        req->auth_req = TRUE;
      }
      else if(!strncmp(CMD_IDLE, cmd, strlen(CMD_IDLE))) {
        logmsg("instructed to idle");
        req->rcmd = RCMD_IDLE;
        req->open = TRUE;
      }
      else if(!strncmp(CMD_STREAM, cmd, strlen(CMD_STREAM))) {
        logmsg("instructed to stream");
        req->rcmd = RCMD_STREAM;
      }
      else if(!strncmp(CMD_CONNECTIONMONITOR, cmd,
                       strlen(CMD_CONNECTIONMONITOR))) {
        logmsg("enabled connection monitoring");
        req->connmon = TRUE;
      }
      else if(!strncmp(CMD_UPGRADE, cmd, strlen(CMD_UPGRADE))) {
        logmsg("enabled upgrade to http2");
        req->upgrade = TRUE;
      }
      else if(1 == sscanf(cmd, "pipe: %d", &num)) {
        logmsg("instructed to allow a pipe size of %d", num);
        if(num < 0)
          logmsg("negative pipe size ignored");
        else if(num > 0)
          req->pipe = num-1; /* decrease by one since we don't count the
                                first request in this number */
      }
      else if(1 == sscanf(cmd, "skip: %d", &num)) {
        logmsg("instructed to skip this number of bytes %d", num);
        req->skip = num;
      }
      else if(1 == sscanf(cmd, "writedelay: %d", &num)) {
        logmsg("instructed to delay %d secs between packets", num);
        req->writedelay = num;
      }
      else {
        logmsg("Unknown <servercmd> instruction found: %s", cmd);
      }
      /* try to deal with CRLF or just LF */
      check = strchr(cmd, '\r');
      if(!check)
        check = strchr(cmd, '\n');

      if(check) {
        /* get to the letter following the newline */
        while((*check == '\r') || (*check == '\n'))
          check++;

        if(!*check)
          /* if we reached a zero, get out */
          break;
        cmd = check;
      }
      else
        break;
    }
    if(orgcmd)
      free(orgcmd);
  }

  return 0; /* OK! */
}