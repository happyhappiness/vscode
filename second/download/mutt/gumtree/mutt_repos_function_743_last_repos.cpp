static int pgp_check_traditional_one_body (FILE *fp, BODY *b)
{
  char tempfile[_POSIX_PATH_MAX];
  char buf[HUGE_STRING];
  FILE *tfp;
  
  short sgn = 0;
  short enc = 0;
  
  if (b->type != TYPETEXT)
    return 0;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (mutt_decode_save_attachment (fp, b, tempfile, 0, 0) != 0)
  {
    unlink (tempfile);
    return 0;
  }
  
  if ((tfp = fopen (tempfile, "r")) == NULL)
  {
    unlink (tempfile);
    return 0;
  }
  
  while (fgets (buf, sizeof (buf), tfp))
  {
    if (!mutt_strncmp ("-----BEGIN PGP ", buf, 15))
    {
      if (MESSAGE(buf + 15))
      {
	enc = 1;
	break;
      }
      else if (SIGNED_MESSAGE(buf + 15))
      {
	sgn = 1;
	break;
      }
    }
  }
  safe_fclose (&tfp);
  unlink (tempfile);

  if (!enc && !sgn)
    return 0;

  /* fix the content type */
  
  mutt_set_parameter ("format", "fixed", &b->parameter);
  mutt_set_parameter ("x-action", enc ? "pgp-encrypted" : "pgp-signed",
                      &b->parameter);
  
  return 1;
}