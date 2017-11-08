static void storerequest(char *reqbuf, size_t totalsize)
{
  int res;
  int error = 0;
  size_t written;
  size_t writeleft;
  FILE *dump;

  if (reqbuf == NULL)
    return;
  if (totalsize == 0)
    return;

  do {
    dump = fopen(REQUEST_DUMP, "ab");
  } while ((dump == NULL) && ((error = errno) == EINTR));
  if (dump == NULL) {
    logmsg("Error opening file %s error: %d %s",
           REQUEST_DUMP, error, strerror(error));
    logmsg("Failed to write request input to " REQUEST_DUMP);
    return;
  }

  writeleft = totalsize;
  do {
    written = fwrite(&reqbuf[totalsize-writeleft],
                     1, writeleft, dump);
    if(got_exit_signal)
      goto storerequest_cleanup;
    if(written > 0)
      writeleft -= written;
  } while ((writeleft > 0) && ((error = errno) == EINTR));

  if(writeleft == 0)
    logmsg("Wrote request (%zu bytes) input to " REQUEST_DUMP, totalsize);
  else if(writeleft > 0) {
    logmsg("Error writing file %s error: %d %s",
           REQUEST_DUMP, error, strerror(error));
    logmsg("Wrote only (%zu bytes) of (%zu bytes) request input to %s",
           totalsize-writeleft, totalsize, REQUEST_DUMP);
  }

storerequest_cleanup:

  do {
    res = fclose(dump);
  } while(res && ((error = errno) == EINTR));
  if(res)
    logmsg("Error closing file %s error: %d %s",
           REQUEST_DUMP, error, strerror(error));
}