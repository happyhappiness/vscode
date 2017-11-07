static char *binary_fingerprint_to_string (unsigned char *buff, size_t length)
{
  int i;
  char *fingerprint, *pf;

  pf = fingerprint = (char *)safe_malloc ((length * 2) + 1);

  for (i = 0; i < length; i++)
  {
    sprintf (pf, "%02X", buff[i]);
    pf += 2;
  }
  *pf = 0;

  return fingerprint;
}