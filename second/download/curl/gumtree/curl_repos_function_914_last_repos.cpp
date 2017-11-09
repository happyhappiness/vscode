bool stdin_upload(const char *uploadfile)
{
  return (!strcmp(uploadfile, "-") ||
          !strcmp(uploadfile, ".")) ? TRUE : FALSE;
}