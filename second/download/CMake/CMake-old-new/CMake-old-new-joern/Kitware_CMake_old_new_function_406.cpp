bool Directory::Load(const char* name)
{
  this->Clear();
#if _MSC_VER < 1300
  long srchHandle;
#else
  intptr_t srchHandle;
#endif
  char* buf;
  size_t n = strlen(name);
  if ( name[n - 1] == '/' || name[n - 1] == '\\' )
    {
    buf = new char[n + 1 + 1];
    sprintf(buf, "%s*", name);
    }
  else
    {
    // Make sure the slashes in the wildcard suffix are consistent with the
    // rest of the path
    buf = new char[n + 2 + 1];
    if ( strchr(name, '\\') )
      {
      sprintf(buf, "%s\\*", name);
      }
    else
      {
      sprintf(buf, "%s/*", name);
      }
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
  do
    {
    this->Internal->Files.push_back(Encoding::ToNarrow(data.name));
    }
  while ( _wfindnext(srchHandle, &data) != -1 );
  this->Internal->Path = name;
  return _findclose(srchHandle) != -1;
}