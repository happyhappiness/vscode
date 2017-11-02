FILE *curl_fopen(const char *file, const char *mode,
                 int line, const char *source)
{
  FILE *res=fopen(file, mode);

  if(source)
    curl_memlog("FILE %s:%d fopen(\"%s\",\"%s\") = %p\n",
                source, line, file, mode, (void *)res);

  return res;
}