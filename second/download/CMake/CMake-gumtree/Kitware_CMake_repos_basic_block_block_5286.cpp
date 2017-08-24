{
  char *unix_path;
  char *test_str;

  /* See if the result is in VMS format, if not, we are done */
  /* Assume that this is a PATH, not just some data */
  test_str = strpbrk(path, ":[<^");
  if(test_str == NULL) {
    return (char *)path;
  }

  unix_path = decc$translate_vms(path);

  if((int)unix_path <= 0) {
    /* We can not translate it, so return the original string */
    return (char *)path;
  }
}