static void pgp_extract_keys_from_attachment (FILE *fp, BODY *top)
{
  STATE s;
  FILE *tempfp;
  char tempfname[_POSIX_PATH_MAX];

  mutt_mktemp (tempfname, sizeof (tempfname));
  if (!(tempfp = safe_fopen (tempfname, "w")))
  {
    mutt_perror (tempfname);
    return;
  }

  memset (&s, 0, sizeof (STATE));
  
  s.fpin = fp;
  s.fpout = tempfp;
  
  mutt_body_handler (top, &s);

  safe_fclose (&tempfp);

  pgp_invoke_import (tempfname);
  mutt_any_key_to_continue (NULL);

  mutt_unlink (tempfname);
}