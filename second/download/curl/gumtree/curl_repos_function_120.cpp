void storerequest(char *reqbuf)
{
  FILE *dump;

  dump = fopen(REQUEST_DUMP, "ab"); /* b is for windows-preparing */
  if(dump) {
    size_t len = strlen(reqbuf);
    fwrite(reqbuf, 1, len, dump);

    fclose(dump);
    logmsg("Wrote request (%d bytes) input to " REQUEST_DUMP,
           (int)len);
  }
  else {
    logmsg("Failed to write request input to " REQUEST_DUMP);
  }
}