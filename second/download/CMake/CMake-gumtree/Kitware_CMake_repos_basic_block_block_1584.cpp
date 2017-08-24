{
  char* ret;
  char* ptr;

  ret = regcode;
  if (ret == &regdummy) {
    regsize += 3;
    return (ret);
  }

  ptr = ret;
  *ptr++ = op;
  *ptr++ = '\0'; // Null "next" pointer.
  *ptr++ = '\0';
  regcode = ptr;

  return (ret);
}