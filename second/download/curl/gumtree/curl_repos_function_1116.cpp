int curl_fclose(FILE *file, int line, const char *source)
{
  int res;

  assert(file != NULL);

  res=fclose(file);

  if(source)
    curl_memlog("FILE %s:%d fclose(%p)\n",
                source, line, (void *)file);

  return res;
}