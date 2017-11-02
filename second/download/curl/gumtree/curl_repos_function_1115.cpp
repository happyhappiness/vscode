FILE *curl_fdopen(int filedes, const char *mode,
                  int line, const char *source)
{
  FILE *res=fdopen(filedes, mode);

  if(source)
    curl_memlog("FILE %s:%d fdopen(\"%d\",\"%s\") = %p\n",
                source, line, filedes, mode, (void *)res);

  return res;
}