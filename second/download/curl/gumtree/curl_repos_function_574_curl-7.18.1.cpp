FILE *curl_fdopen(int filedes, const char *mode,
                  int line, const char *source)
{
  FILE *res=(fdopen)(filedes, mode);
  if(logfile)
    fprintf(logfile, "FILE %s:%d fdopen(\"%d\",\"%s\") = %p\n",
            source, line, filedes, mode, res);
  return res;
}