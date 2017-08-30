  intptr_t srchHandle;

#endif

  char* buf;

  size_t n = name.size();

  if ( *name.rbegin() == '/' || *name.rbegin() == '\\' )

    {

    buf = new char[n + 1 + 1];

    sprintf(buf, "%s*", name.c_str());

    }

  else

    {

    // Make sure the slashes in the wildcard suffix are consistent with the

    // rest of the path

    buf = new char[n + 2 + 1];

    if ( name.find('\\') != name.npos )

      {

      sprintf(buf, "%s\\*", name.c_str());

      }

    else

      {

      sprintf(buf, "%s/*", name.c_str());

      }

    }

  struct _wfinddata_t data;      // data of current file

