int getdnsdomainname (char *s, size_t l)
{
  FILE *f;
  char tmp[1024];
  char *p = NULL;
  char *q;

  if ((f = fopen ("/etc/resolv.conf", "r")) == NULL) return (-1);

  tmp[sizeof (tmp) - 1] = 0;

  l--; /* save room for the terminal \0 */

  while (fgets (tmp, sizeof (tmp) - 1, f) != NULL)
  {
    p = tmp;
    while (ISSPACE (*p)) p++;
    if (mutt_strncmp ("domain", p, 6) == 0 || mutt_strncmp ("search", p, 6) == 0)
    {
      p += 6;
      
      for (q = strtok (p, " \t\n"); q; q = strtok (NULL, " \t\n"))
	if (strcmp (q, "."))
	  break;

      if (q)
      {
	strip_trailing_dot (q);
	strfcpy (s, q, l);
	safe_fclose (&f);
	return 0;
      }
      
    }
  }

  safe_fclose (&f);
  return (-1);
}