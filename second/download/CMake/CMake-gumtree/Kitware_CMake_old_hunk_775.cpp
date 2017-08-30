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

