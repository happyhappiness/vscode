static int pgp_check_traditional_one_body (FILE *fp, BODY *b)
{
  char tempfile[_POSIX_PATH_MAX];
  char buf[HUGE_STRING];
  FILE *tfp;
  
  short sgn = 0;
  short enc = 0;
  short key = 0;
  
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
    if (mutt_strncmp ("-----BEGIN PGP ", buf, 15) == 0)
    {
      if (mutt_strcmp ("MESSAGE-----\n", buf + 15) == 0)
	enc = 1;
      else if (mutt_strcmp ("SIGNED MESSAGE-----\n", buf + 15) == 0)
	sgn = 1;
      else if (mutt_strcmp ("PUBLIC KEY BLOCK-----\n", buf + 15) == 0)
	key = 1;
    }
  }
  safe_fclose (&tfp);
  unlink (tempfile);

  if (!enc && !sgn && !key)
    return 0;

  /* fix the content type */
  
  mutt_set_parameter ("format", "fixed", &b->parameter);
  if (enc)
    mutt_set_parameter ("x-action", "pgp-encrypted", &b->parameter);
  else if (sgn)
    mutt_set_parameter ("x-action", "pgp-signed", &b->parameter);
  else if (key)
    mutt_set_parameter ("x-action", "pgp-keys", &b->parameter);
  
  return 1;
}