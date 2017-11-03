static int hostname_match (const char *hostname, const char *certname)
{
  const char *cmp1, *cmp2;

  if (strncmp(certname, "*.", 2) == 0)
  {
    cmp1 = certname + 2;
    cmp2 = strchr(hostname, '.');
    if (!cmp2)
    {
      return 0;
    }
    else
    {
      cmp2++;
    }
  }
  else
  {
    cmp1 = certname;
    cmp2 = hostname;
  }

  if (*cmp1 == '\0' || *cmp2 == '\0')
  {
    return 0;
  }

  if (strcasecmp(cmp1, cmp2) != 0)
  {
    return 0;
  }

  return 1;
}