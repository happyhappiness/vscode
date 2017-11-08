int curl_fclose(FILE *file, int line, const char *source)
{
  int res;

  if(NULL == file) {
    fprintf(stderr, "ILLEGAL flose() on NULL at %s:%d\n",
            source, line);
    exit(2);
  }

  res=(fclose)(file);
  if(logfile)
    fprintf(logfile, "FILE %s:%d fclose(%p)\n",
            source, line, file);
  return res;
}