{
  /* The given stream is definitely not interactive if it is a regular
     file.  */
  struct stat stream_stat;
  if (fstat(fileno(stream), &stream_stat) == 0) {
    if (stream_stat.st_mode & S_IFREG) {
      return 1;
    }
  }
  return 0;
}