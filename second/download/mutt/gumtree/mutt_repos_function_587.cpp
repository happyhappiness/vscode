static void pgp_dearmor (FILE *in, FILE *out)
{
  char line[HUGE_STRING];
  LOFF_T start;
  LOFF_T end;
  char *r;

  STATE state;
  
  memset (&state, 0, sizeof (STATE));
  state.fpin = in;
  state.fpout = out;
  
  /* find the beginning of ASCII armor */
  
  while ((r = fgets (line, sizeof (line), in)) != NULL)
  {
    if (!strncmp (line, "-----BEGIN", 10))
      break;
  }
  if (r == NULL)
  {
    dprint (1, (debugfile, "pgp_dearmor: Can't find begin of ASCII armor.\n"));
    return;
  }

  /* skip the armor header */
  
  while ((r = fgets (line, sizeof (line), in)) != NULL)
  {
    SKIPWS (r);
    if (!*r) break;
  }
  if (r == NULL)
  {
    dprint (1, (debugfile, "pgp_dearmor: Armor header doesn't end.\n"));
    return;
  }
  
  /* actual data starts here */
  start = ftello (in);
  
  /* find the checksum */
  
  while ((r = fgets (line, sizeof (line), in)) != NULL)
  {
    if (*line == '=' || !strncmp (line, "-----END", 8))
      break;
  }
  if (r == NULL)
  {
    dprint (1, (debugfile, "pgp_dearmor: Can't find end of ASCII armor.\n"));
    return;
  }
  
  if ((end = ftello (in) - strlen (line)) < start)
  {
    dprint (1, (debugfile, "pgp_dearmor: end < start???\n"));
    return;
  }
  
  if (fseeko (in, start, SEEK_SET) == -1)
  {
    dprint (1, (debugfile, "pgp_dearmor: Can't seekto start.\n"));
    return;
  }

  mutt_decode_base64 (&state, end - start, 0, (iconv_t) -1);
}