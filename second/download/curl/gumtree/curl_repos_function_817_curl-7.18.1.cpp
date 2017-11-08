char *Curl_strcasestr(const char *haystack, const char *needle)
{
#if defined(HAVE_STRCASESTR)
  return strcasestr(haystack, needle);
#else
  size_t nlen = strlen(needle);
  size_t hlen = strlen(haystack);

  while(hlen-- >= nlen) {
    if(curl_strnequal(haystack, needle, nlen))
      return (char *)haystack;
    haystack++;
  }
  return NULL;
#endif
}