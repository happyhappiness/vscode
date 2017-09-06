unsigned long Directory::GetNumberOfFilesInDirectory(const kwsys_stl::string& name)
{
#if _MSC_VER < 1300
  long srchHandle;
#else
  intptr_t srchHandle;
#endif
  char* buf;
  size_t n = name.size();
  if ( *name.rbegin() == '/' )
    {
    buf = new char[n + 1 + 1];
    sprintf(buf, "%s*", name.c_str());
    }
  else
    {
    buf = new char[n + 2 + 1];
    sprintf(buf, "%s/*", name.c_str());
    }
  struct _wfinddata_t data;      // data of current file

  // Now put them into the file array
  srchHandle = _wfindfirst((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
  delete [] buf;

  if ( srchHandle == -1 )
    {
    return 0;
    }

  // Loop through names
  unsigned long count = 0;
  do
    {
    count++;
    }
  while ( _wfindnext(srchHandle, &data) != -1 );
  _findclose(srchHandle);
  return count;
}