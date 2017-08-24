{
    result = TRUE;
    *resp = curlx_sltosi(strtol(line, NULL, 10));

    /* Make sure real server never sends internal value */
    if(*resp == 1)
      *resp = 0;
  }