{
    size_t qlen;
    /* There was a query part, append that to the output. The 'clone' string
       may now have been altered so we copy from the original input string
       from the correct index. */
    size_t oindex = queryp - orgclone;
    qlen = strlen(&input[oindex]);
    memcpy(outptr, &input[oindex], qlen+1); /* include the ending zero byte */
  }