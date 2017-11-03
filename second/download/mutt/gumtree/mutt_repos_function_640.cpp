static char **
be_snarf_data (FILE *f, char **buf, int *bufmax, int *buflen, LOFF_T offset,
	       int bytes, int prefix)
{
  char tmp[HUGE_STRING];
  char *p = tmp;
  int tmplen = sizeof (tmp);

  tmp[sizeof (tmp) - 1] = 0;
  if (prefix)
  {
    strfcpy (tmp, NONULL(Prefix), sizeof (tmp));
    tmplen = mutt_strlen (tmp);
    p = tmp + tmplen;
    tmplen = sizeof (tmp) - tmplen;
  }

  fseeko (f, offset, 0);
  while (bytes > 0)
  {
    if (fgets (p, tmplen - 1, f) == NULL) break;
    bytes -= mutt_strlen (p);
    if (*bufmax == *buflen)
      safe_realloc (&buf, sizeof (char *) * (*bufmax += 25));
    buf[(*buflen)++] = safe_strdup (tmp);
  }
  if (buf && *bufmax == *buflen) { /* Do not smash memory past buf */
    safe_realloc (&buf, sizeof (char *) * (++*bufmax));
  }
  if (buf) buf[*buflen] = NULL;
  return (buf);
}