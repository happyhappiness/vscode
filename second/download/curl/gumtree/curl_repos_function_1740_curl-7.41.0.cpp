static bool isBadFtpString(const char *string)
{
  return ((NULL != strchr(string, '\r')) ||
          (NULL != strchr(string, '\n'))) ? TRUE : FALSE;
}