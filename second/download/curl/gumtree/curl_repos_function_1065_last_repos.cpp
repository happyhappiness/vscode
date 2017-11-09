static size_t strlen_url(const char *url, bool relative)
{
  const unsigned char *ptr;
  size_t newlen = 0;
  bool left = TRUE; /* left side of the ? */
  const unsigned char *host_sep = (const unsigned char *) url;

  if(!relative)
    host_sep = (const unsigned char *) find_host_sep(url);

  for(ptr = (unsigned char *)url; *ptr; ptr++) {

    if(ptr < host_sep) {
      ++newlen;
      continue;
    }

    switch(*ptr) {
    case '?':
      left = FALSE;
      /* fall through */
    default:
      if(*ptr >= 0x80)
        newlen += 2;
      newlen++;
      break;
    case ' ':
      if(left)
        newlen += 3;
      else
        newlen++;
      break;
    }
  }
  return newlen;
}