int strequal(const char *first, const char *second)
{
#if defined(HAVE_STRCASECMP)
  return !strcasecmp(first, second);
#elif defined(HAVE_STRCMPI)
  return !strcmpi(first, second);
#elif defined(HAVE_STRICMP)
  return !stricmp(first, second);
#else
  while (*first && *second) {
    if (toupper(*first) != toupper(*second)) {
      break;
    }
    first++;
    second++;
  }
  return toupper(*first) == toupper(*second);
#endif
}