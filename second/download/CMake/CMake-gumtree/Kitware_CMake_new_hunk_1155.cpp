}
inline const char* Getcwd(char* buf, unsigned int len)
{
  if(const char* ret = _getcwd(buf, len))
    {
    // make sure the drive letter is capital
    if(strlen(buf) > 1 && buf[1] == ':')
      {
      buf[0] = toupper(buf[0]);
      }
    return ret;
    }
  return 0;
}
inline int Chdir(const char* dir)
{
