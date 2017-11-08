int curl_strnequal(const char *first, const char *second, size_t max)
{
#if defined(HAVE_STRCASECMP)
  return !strncasecmp(first, second, max);
#elif defined(HAVE_STRCMPI)
  return !strncmpi(first, second, max);
#elif defined(HAVE_STRICMP)
  return !strnicmp(first, second, max);
#else
  while (*first && *second && max) {
    if (toupper(*first) != toupper(*second)) {
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