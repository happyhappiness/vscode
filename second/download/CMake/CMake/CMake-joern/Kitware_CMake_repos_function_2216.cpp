static const char* Getcwd(char* buf, unsigned int len)
{
  const char* ret = getcwd(buf, len);
  if (!ret) {
    fprintf(stderr, "No current working directory\n");
    abort();
  }
  return ret;
}