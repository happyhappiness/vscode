static int validate_access(struct testcase *test,
                           const char *filename, int mode)
{
  char *ptr;
  long testno, partno;
  int error;
  char partbuf[80]="data";

  logmsg("trying to get file: %s mode %x", filename, mode);

  if(!strncmp("verifiedserver", filename, 14)) {
    char weare[128];
    size_t count = sprintf(weare, "WE ROOLZ: %ld\r\n", (long)getpid());

    logmsg("Are-we-friendly question received");
    test->buffer = strdup(weare);
    test->rptr = test->buffer; /* set read pointer */
    test->bufsize = count;    /* set total count */
    test->rcount = count;     /* set data left to read */
    return 0; /* fine */
  }

  /* find the last slash */
  ptr = strrchr(filename, '/');

  if(ptr) {
    char *file;

    ptr++; /* skip the slash */

    /* skip all non-numericals following the slash */
    while(*ptr && !ISDIGIT(*ptr))
      ptr++;

    /* get the number */
    testno = strtol(ptr, &ptr, 10);

    if(testno > 10000) {
      partno = testno % 10000;
      testno /= 10000;
    }
    else
      partno = 0;


    logmsg("requested test number %ld part %ld", testno, partno);

    test->testno = testno;

    (void)parse_servercmd(test);

    file = test2file(testno);

    if(0 != partno)
      sprintf(partbuf, "data%ld", partno);

    if(file) {
      FILE *stream=fopen(file, "rb");
      if(!stream) {
        error = errno;
        logmsg("fopen() failed with error: %d %s", error, strerror(error));
        logmsg("Error opening file: %s", file);
        logmsg("Couldn't open test file: %s", file);
        return EACCESS;
      }
      else {
        size_t count;
        error = getpart(&test->buffer, &count, "reply", partbuf, stream);
        fclose(stream);
        if(error) {
          logmsg("getpart() failed with error: %d", error);
          return EACCESS;
        }
        if(test->buffer) {
          test->rptr = test->buffer; /* set read pointer */
          test->bufsize = count;    /* set total count */
          test->rcount = count;     /* set data left to read */
        }
        else
          return EACCESS;
      }

    }
    else
      return EACCESS;
  }
  else {
    logmsg("no slash found in path");
    return EACCESS; /* failure */
  }

  logmsg("file opened and all is good");
  return 0;
}