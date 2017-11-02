bool stdin_upload(const char *uploadfile)
{
  return (curlx_strequal(uploadfile, "-") ||
          curlx_strequal(uploadfile, ".")) ? TRUE : FALSE;
}