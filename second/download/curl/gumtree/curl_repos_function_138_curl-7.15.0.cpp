static int validate_access(struct testcase *test,
                           const char *filename, int mode)
{
  char *ptr;
  long testno;

  logmsg("trying to get file: %s mode %x", filename, mode);

  if(!strncmp("/verifiedserver", filename, 15)) {
    char weare[128];
    size_t count = sprintf(weare, "WE ROOLZ: %d\r\n", (int)getpid());

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
    while(*ptr && !isdigit((int)*ptr))
      ptr++;

    /* get the number */
    testno = strtol(ptr, &ptr, 10);

    logmsg("requested test number %d", testno);

    test->num = testno;

    file = test2file(testno);

    if(file) {
      FILE *stream=fopen(file, "rb");
      if(!stream) {
        logmsg("Couldn't open test file: %s", file);
        return EACCESS;
      }
      else {
        size_t count;
        test->buffer = (char *)spitout(stream, "reply", "data", &count);
        fclose(stream);
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

  return 0;
}