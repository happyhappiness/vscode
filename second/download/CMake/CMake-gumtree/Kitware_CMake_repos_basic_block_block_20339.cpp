{
    req->service = (WCHAR*)alloc_ptr;
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            service,
                            -1,
                            (WCHAR*) alloc_ptr,
                            servicesize / sizeof(WCHAR)) == 0) {
      err = GetLastError();
      goto error;
    }
    alloc_ptr += servicesize;
  }