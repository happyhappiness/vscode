wchar_t *curl_dowcsdup(const wchar_t *str, int line, const char *source)
{
  wchar_t *mem;
  size_t wsiz, bsiz;

  DEBUGASSERT(str != NULL);

  if(countcheck("wcsdup", line, source))
    return NULL;

  wsiz = wcslen(str) + 1;
  bsiz = wsiz * sizeof(wchar_t);

  mem = curl_domalloc(bsiz, 0, NULL); /* NULL prevents logging */
  if(mem)
    memcpy(mem, str, bsiz);

  if(source)
    curl_memlog("MEM %s:%d wcsdup(%p) (%zu) = %p\n",
                source, line, (void *)str, bsiz, (void *)mem);

  return mem;
}