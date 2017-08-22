  return _findclose(srchHandle) != -1;
}

unsigned long Directory::GetNumberOfFilesInDirectory(const char* name)
{
#if _MSC_VER < 1300
  long srchHandle;
#else
  intptr_t srchHandle;
#endif
  char* buf;
  size_t n = strlen(name);
  if ( name[n - 1] == '/' )
    {
    buf = new char[n + 1 + 1];
    sprintf(buf, "%s*", name);
    }
  else
    {
    buf = new char[n + 2 + 1];
    sprintf(buf, "%s/*", name);
    }
  struct _wfinddata_t data;      // data of current file

