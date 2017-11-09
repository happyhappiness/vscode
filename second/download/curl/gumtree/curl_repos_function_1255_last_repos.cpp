char *curl_dostrdup(const char *str, int line, const char *source)
{
  char *mem;
  size_t len;

  DEBUGASSERT(str != NULL);

  if(countcheck("strdup", line, source))
    return NULL;

  len = strlen(str) + 1;

  mem = curl_domalloc(len, 0, NULL); /* NULL prevents logging */
  if(mem)
    memcpy(mem, str, len);

  if(source)
    curl_memlog("MEM %s:%d strdup(%p) (%zu) = %p\n",
                source, line, (const void *)str, len, (const void *)mem);

  return mem;
}