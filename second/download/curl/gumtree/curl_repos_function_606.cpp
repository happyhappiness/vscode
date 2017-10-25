static bool tailmatch(const char *little, const char *bigone)
{
  size_t littlelen = strlen(little);
  size_t biglen = strlen(bigone);

  if(littlelen > biglen)
    return FALSE;

  return (bool)strequal(little, bigone+biglen-littlelen);
}