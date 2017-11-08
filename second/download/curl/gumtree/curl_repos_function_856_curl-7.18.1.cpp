static bool isBadFtpString(const char *string)
{
  return (bool)((NULL != strchr(string, '\r')) || (NULL != strchr(string, '\n')));
}