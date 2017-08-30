    buf = new char[n + 2 + 1];
    sprintf(buf, "%s/*", name);
    }
  struct _finddata_t data;      // data of current file
  
  // Now put them into the file array
  size_t srchHandle = _findfirst(buf, &data);
