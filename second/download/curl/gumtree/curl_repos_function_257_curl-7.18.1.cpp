void storerequest(char *reqbuf, ssize_t totalsize)
{
  int error;
  ssize_t written;
  ssize_t writeleft;
  FILE *dump;

  if (reqbuf == NULL)
    return;

  if (totalsize == 0)
    return;
  else if (totalsize < 0) {
    logmsg("Invalid size (%d bytes) for request input. Not written to %s",
           totalsize, REQUEST_DUMP);
    return;
  }

  do {
    dump = fopen(REQUEST_DUMP, "ab");
  } while ((dump == NULL) && ((error = ERRNO) == EINTR));
  if (dump == NULL) {
    logmsg("Error opening file %s error: %d %s",
           REQUEST_DUMP, error, strerror(error));
    logmsg("Failed to write request input to " REQUEST_DUMP);
    return;
  }

  writeleft = totalsize;
  do {
    written = (ssize_t)fwrite((void *) &reqbuf[totalsize-writeleft],
                              1, (size_t)writeleft, dump);
    if (written > 0)
      writeleft -= written;
  } while ((writeleft > 0) && ((error = ERRNO) == EINTR));

  fclose(dump);  /* close it ASAP */

  if (writeleft > 0) {
    logmsg("Error writing file %s error: %d %s",
           REQUEST_DUMP, error, strerror(error));
    logmsg("Wrote only (%d bytes) of (%d bytes) request input to %s",
           totalsize-writeleft, totalsize, REQUEST_DUMP);
  }
  else {
    logmsg("Wrote request (%d bytes) input to " REQUEST_DUMP,
           totalsize);
  }
}