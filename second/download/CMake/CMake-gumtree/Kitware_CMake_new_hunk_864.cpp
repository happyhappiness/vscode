    buf = new char[n + 2 + 1];

    sprintf(buf, "%s/*", name);

    }

  struct _wfinddata_t data;      // data of current file



  // Now put them into the file array

  srchHandle = _wfindfirst((wchar_t*)Encoding::ToWide(buf).c_str(), &data);

  delete [] buf;



  if ( srchHandle == -1 )

