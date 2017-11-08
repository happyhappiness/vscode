static bool isBadFtpString(const char *string)
{
  return strchr(string, 0x0D) != NULL || strchr(string, 0x0A) != NULL;
}