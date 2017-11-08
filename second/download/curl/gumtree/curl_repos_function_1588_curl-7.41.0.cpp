int curl_strnequal(const char *first, const char *second, size_t max)
{
#if defined(HAVE_STRNCASECMP)
  return !strncasecmp(first, second, max);
#elif defined(HAVE_STRNCMPI)
  return !strncmpi(first, second, max);
#elif defined(HAVE_STRNICMP)
  return !strnicmp(first, second, max);
#else
  while(*first && *second && max) {
    if(toupper(*first) != toupper(*second)) {
      break;
    }
    max--;
    first++;
    second++;
  }
  if(0 == max)
    return 1; /* they are equal this far */

  return toupper(*first) == toupper(*second);
#endif
}