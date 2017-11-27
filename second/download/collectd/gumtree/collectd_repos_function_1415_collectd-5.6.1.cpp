static void c_ipmi_error (const char *func, int status)
{
  char errbuf[4096] = { 0 };

  if (IPMI_IS_OS_ERR (status))
  {
    sstrerror (IPMI_GET_OS_ERR (status), errbuf, sizeof (errbuf));
  }
  else if (IPMI_IS_IPMI_ERR (status))
  {
    ipmi_get_error_string (IPMI_GET_IPMI_ERR (status), errbuf, sizeof (errbuf));
  }

  if (errbuf[0] == 0)
  {
    ssnprintf (errbuf, sizeof (errbuf), "Unknown error %#x", status);
  }
  errbuf[sizeof (errbuf) - 1] = 0;

  ERROR ("ipmi plugin: %s failed: %s", func, errbuf);
}