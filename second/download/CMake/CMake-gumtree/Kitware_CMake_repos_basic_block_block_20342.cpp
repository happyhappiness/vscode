{
    req->node = (WCHAR*)alloc_ptr;
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            node,
                            -1,
                            (WCHAR*) alloc_ptr,
                            nodesize / sizeof(WCHAR)) == 0) {
      err = GetLastError();
      goto error;
    }
    alloc_ptr += nodesize;
  }