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



  // Now put them into the file array

  srchHandle = _wfindfirst_func((wchar_t*)Encoding::ToWide(buf).c_str(), &data);

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

  while ( _wfindnext_func(srchHandle, &data) != -1 );

  this->Internal->Path = name;

  return _findclose(srchHandle) != -1;

}

