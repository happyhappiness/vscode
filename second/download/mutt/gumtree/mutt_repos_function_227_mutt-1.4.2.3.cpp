int pgp_decrypt_mime (FILE *fpin, FILE **fpout, BODY *b, BODY **cur)
{
  char tempfile[_POSIX_PATH_MAX];
  STATE s;
  BODY *p = b;
  
  if(!mutt_is_multipart_encrypted(b))
    return -1;

  if(!b->parts || !b->parts->next)
    return -1;
  
  b = b->parts->next;
  
  memset (&s, 0, sizeof (s));
  s.fpin = fpin;
  mutt_mktemp (tempfile);
  if ((*fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    return (-1);
  }
  unlink (tempfile);

  *cur = pgp_decrypt_part (b, &s, *fpout, p);

  rewind (*fpout);
  return (0);
}