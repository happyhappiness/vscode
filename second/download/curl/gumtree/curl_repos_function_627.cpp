static int parse_servercmd(struct testcase *req)
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
      return 1; /* done */
    }

    cmd = orgcmd;
    while(cmd && cmdsize) {
      char *check;
      if(1 == sscanf(cmd, "writedelay: %d", &num)) {
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