static int hostmatch(const char *hostname, const char *pattern)
{
  while(1) {
    char c = *pattern++;

    if(c == '\0')
      return (*hostname ? HOST_NOMATCH : HOST_MATCH);

    if(c == '*') {
      c = *pattern;
      if(c == '\0')      /* "*\0" matches anything remaining */
        return HOST_MATCH;

      while(*hostname) {
        /* The only recursive function in libcurl! */
        if(hostmatch(hostname++,pattern) == HOST_MATCH)
          return HOST_MATCH;
      }
      break;
    }

    if(toupper(c) != toupper(*hostname++))
      break;
  }
  return HOST_NOMATCH;
}