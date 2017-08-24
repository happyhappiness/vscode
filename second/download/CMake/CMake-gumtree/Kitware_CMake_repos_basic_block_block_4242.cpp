{
    for(; p != end && (*p == ' ' || *p == '\t'); ++p)
      ;
    if(p == end || (size_t)(end - p) < sizeof("trailers") - 1)
      return FALSE;
    if(strncasecompare("trailers", p, sizeof("trailers") - 1)) {
      p += sizeof("trailers") - 1;
      for(; p != end && (*p == ' ' || *p == '\t'); ++p)
        ;
      if(p == end || *p == ',')
        return TRUE;
    }
    /* skip to next token */
    for(; p != end && *p != ','; ++p)
      ;
    if(p == end)
      return FALSE;
    ++p;
  }