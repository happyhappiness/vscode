}
inline const char* Getcwd(char* buf, unsigned int len)
{
  const char* ret = _getcwd(buf, len);
  if(!ret)
    {
    fprintf(stderr, "No current working directory.\n");
    abort();
    }
  // make sure the drive letter is capital
  if(strlen(buf) > 1 && buf[1] == ':')
    {
    buf[0] = toupper(buf[0]);
    }
  return ret;
}
inline int Chdir(const char* dir)
{
