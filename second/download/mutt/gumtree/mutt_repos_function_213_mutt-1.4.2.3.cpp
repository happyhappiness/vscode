static int pgp_check_traditional_one_body (FILE *fp, BODY *b, int tagged_only)
{
  char tempfile[_POSIX_PATH_MAX];
  char buf[HUGE_STRING];
  FILE *tfp;
  
  short sgn = 0;
  short enc = 0;
  
  if (b->type != TYPETEXT)
    return 0;

  if (tagged_only && !b->tagged)
    return 0;
  
  mutt_mktemp (tempfile);
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
    }
  }
  
  safe_fclose (&tfp);
  unlink (tempfile);

  if (!enc && !sgn)
    return 0;

  /* fix the content type */
  
  b->type = TYPEAPPLICATION;
  mutt_str_replace (&b->subtype, "pgp");
  
  mutt_set_parameter ("format", "text", &b->parameter);
  mutt_set_parameter ("x-action", enc ? "encrypt" : "sign", &b->parameter);
  
  return 1;
}