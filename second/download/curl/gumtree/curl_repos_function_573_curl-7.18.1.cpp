FILE *curl_fopen(const char *file, const char *mode,
                 int line, const char *source)
{
  FILE *res=(fopen)(file, mode);
  if(logfile)
    fprintf(logfile, "FILE %s:%d fopen(\"%s\",\"%s\") = %p\n",
            source, line, file, mode, res);
  return res;
}