int smime_gpgme_decrypt_mime (FILE *fpin, FILE **fpout, BODY *b, BODY **cur)
{
  char tempfile[_POSIX_PATH_MAX];
  STATE s;
  FILE *tmpfp=NULL;
  int is_signed;
  LOFF_T saved_b_offset;
  size_t saved_b_length;
  int saved_b_type;

  if (!mutt_is_application_smime (b))
    return -1;

  if (b->parts)
    return -1;
  
  /* Decode the body - we need to pass binary CMS to the
     backend.  The backend allows for Base64 encoded data but it does
     not allow for QP which I have seen in some messages.  So better
     do it here. */
  saved_b_type = b->type;
  saved_b_offset = b->offset;
  saved_b_length = b->length;
  memset (&s, 0, sizeof (s));
  s.fpin = fpin;
  fseeko (s.fpin, b->offset, 0); 
  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(tmpfp = safe_fopen (tempfile, "w+")))
    {
      mutt_perror (tempfile);
      return -1;
    }
  mutt_unlink (tempfile);

  s.fpout = tmpfp;
  mutt_decode_attachment (b, &s);
  fflush (tmpfp);
  b->length = ftello (s.fpout);
  b->offset = 0;
  rewind (tmpfp);

  memset (&s, 0, sizeof (s));
  s.fpin = tmpfp;
  s.fpout = 0;
  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(*fpout = safe_fopen (tempfile, "w+")))
    {
      mutt_perror (tempfile);
      return -1;
    }
  mutt_unlink (tempfile);

  *cur = decrypt_part (b, &s, *fpout, 1, &is_signed);
  if (*cur)
    (*cur)->goodsig = is_signed > 0;
  b->type = saved_b_type;
  b->length = saved_b_length;
  b->offset = saved_b_offset;
  safe_fclose (&tmpfp);
  rewind (*fpout);
  if (*cur && !is_signed && !(*cur)->parts && mutt_is_application_smime (*cur))
    {
      /* Assume that this is a opaque signed s/mime message.  This is
         an ugly way of doing it but we have anyway a problem with
         arbitrary encoded S/MIME messages: Only the outer part may be
         encrypted.  The entire mime parsing should be revamped,
         probably by keeping the temporary files so that we don't
         need to decrypt them all the time.  Inner parts of an
         encrypted part can then point into this file and there won't
         ever be a need to decrypt again.  This needs a partial
         rewrite of the MIME engine. */
      BODY *bb = *cur;
      BODY *tmp_b;

      saved_b_type = bb->type;
      saved_b_offset = bb->offset;
      saved_b_length = bb->length;
      memset (&s, 0, sizeof (s));
      s.fpin = *fpout;
      fseeko (s.fpin, bb->offset, 0); 
      mutt_mktemp (tempfile, sizeof (tempfile));
      if (!(tmpfp = safe_fopen (tempfile, "w+")))
        {
          mutt_perror (tempfile);
          return -1;
        }
      mutt_unlink (tempfile);

      s.fpout = tmpfp;
      mutt_decode_attachment (bb, &s);
      fflush (tmpfp);
      bb->length = ftello (s.fpout);
      bb->offset = 0;
      rewind (tmpfp);
      safe_fclose (fpout); 

      memset (&s, 0, sizeof (s));
      s.fpin = tmpfp;
      s.fpout = 0;
      mutt_mktemp (tempfile, sizeof (tempfile));
      if (!(*fpout = safe_fopen (tempfile, "w+")))
        {
          mutt_perror (tempfile);
          return -1;
        }
      mutt_unlink (tempfile);

      tmp_b = decrypt_part (bb, &s, *fpout, 1, &is_signed);
      if (tmp_b)
        tmp_b->goodsig = is_signed > 0;
      bb->type = saved_b_type;
      bb->length = saved_b_length;
      bb->offset = saved_b_offset;
      safe_fclose (&tmpfp);
      rewind (*fpout);
      mutt_free_body (cur);
      *cur = tmp_b;
    }
  return *cur? 0:-1;
}