int curl_fclose(FILE *file, int line, const char *source)
{
  int res;

  DEBUGASSERT(file != NULL);

  res=(fclose)(file);
  if(logfile)
    fprintf(logfile, "FILE %s:%d fclose(%p)\n",
            source, line, file);
  return res;
}