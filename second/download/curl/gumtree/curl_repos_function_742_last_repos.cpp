int strncasecompare(const char *first, const char *second, size_t max)
{
  while(*first && *second && max) {
    if(raw_toupper(*first) != raw_toupper(*second)) {
      break;
    }
    max--;
    first++;
    second++;
  }
  if(0 == max)
    return 1; /* they are equal this far */

  return raw_toupper(*first) == raw_toupper(*second);
}