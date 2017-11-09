static int _strlen_check(int linenumber, char *buf, size_t len)
{
  size_t buflen = strlen(buf);
  if(len != buflen) {
    /* they shouldn't differ */
    printf("sprintf strlen:%d failed:\nwe '%d'\nsystem: '%d'\n",
           linenumber, buflen, len);
    return 1;
  }
  return 0;
}