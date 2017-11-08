char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  return getpassword(prompt, buffer, buflen);
}