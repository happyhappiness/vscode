int pgp_gpgme_decrypt_mime (FILE *fpin, FILE **fpout, BODY *b, BODY **cur)
{
  char tempfile[_POSIX_PATH_MAX];
  STATE s;
  BODY *first_part = b;
  int is_signed = 0;
  int need_decode = 0;
  int saved_type;
  LOFF_T saved_offset;
  size_t saved_length;
  FILE *decoded_fp = NULL;
  int rv = 0;
  
  first_part->goodsig = 0;
  first_part->warnsig = 0;

  if (mutt_is_valid_multipart_pgp_encrypted (b))
    b = b->parts->next;
  else if (mutt_is_malformed_multipart_pgp_encrypted (b))
  {
    b = b->parts->next->next;
    need_decode = 1;
  }
  else
    return -1;
  
  memset (&s, 0, sizeof (s));
  s.fpin = fpin;

  if (need_decode)
  {
    saved_type = b->type;
    saved_offset = b->offset;
    saved_length = b->length;

    mutt_mktemp (tempfile, sizeof (tempfile));
    if ((decoded_fp = safe_fopen (tempfile, "w+")) == NULL)
    {
      mutt_perror (tempfile);
      return (-1);
    }
    unlink (tempfile);

    fseeko (s.fpin, b->offset, 0);
    s.fpout = decoded_fp;

    mutt_decode_attachment (b, &s);

    fflush (decoded_fp);
    b->length = ftello (decoded_fp);
    b->offset = 0;
    rewind (decoded_fp);
    s.fpin = decoded_fp;
    s.fpout = 0;
  }

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(*fpout = safe_fopen (tempfile, "w+")))
  {
    mutt_perror (tempfile);
    rv = -1;
    goto bail;
  }
  unlink (tempfile);

  if ((*cur = decrypt_part (b, &s, *fpout, 0, &is_signed)) == NULL)
    rv = -1;
  rewind (*fpout);
  if (is_signed > 0)
    first_part->goodsig = 1;

bail:
  if (need_decode)
  {
    b->type = saved_type;
    b->length = saved_length;
    b->offset = saved_offset;
    safe_fclose (&decoded_fp);
  }

  return rv;
}