static int pgp_check_decryption_okay (FILE *fpin)
{
  int rv = -1;

  if (PgpDecryptionOkay.pattern)
  {
    char *line = NULL;
    int lineno = 0;
    size_t linelen;

    while ((line = mutt_read_line (line, &linelen, fpin, &lineno, 0)) != NULL)
    {
      if (regexec (PgpDecryptionOkay.rx, line, 0, NULL, 0) == 0)
      {
        dprint (2, (debugfile, "pgp_check_decryption_okay: \"%s\" matches regexp.\n",
                    line));
        rv = 0;
        break;
      }
      else
        dprint (2, (debugfile, "pgp_check_decryption_okay: \"%s\" doesn't match regexp.\n",
                    line));
    }
    FREE (&line);
  }
  else
  {
    dprint (2, (debugfile, "pgp_check_decryption_okay: No pattern.\n"));
    rv = 1;
  }

  return rv;
}