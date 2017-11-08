FILE *curl_fopen(const char *file, const char *mode,
                 int line, const char *source)
{
  FILE *res=(fopen)(file, mode);
  fprintf(logfile?logfile:stderr, "FILE %s:%d fopen(\"%s\") = %p\n",
          source, line, file, res);
  return res;
}