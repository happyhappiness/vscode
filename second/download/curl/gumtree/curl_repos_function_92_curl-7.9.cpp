int curl_fclose(FILE *file, int line, const char *source)
{
  int res=(fclose)(file);
  fprintf(logfile?logfile:stderr, "FILE %s:%d fclose(%p)\n",
          source, line, file);
  return res;
}