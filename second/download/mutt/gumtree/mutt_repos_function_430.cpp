int smime_decrypt_mime (FILE *fpin, FILE **fpout, BODY *b, BODY **cur)
{


  char tempfile[_POSIX_PATH_MAX];
  STATE s;
  LOFF_T tmpoffset = b->offset;
  size_t tmplength = b->length;
  int origType = b->type;
  FILE *tmpfp=NULL;
  int rv = 0;

  if (!mutt_is_application_smime (b))
    return -1;

  if (b->parts)
    return -1;
  
  memset (&s, 0, sizeof (s));
  s.fpin = fpin;
  fseeko (s.fpin, b->offset, 0);

  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((tmpfp = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    return (-1);
  }

  mutt_unlink (tempfile);
  s.fpout = tmpfp;
  mutt_decode_attachment (b, &s);
  fflush (tmpfp);
  b->length = ftello (s.fpout);
  b->offset = 0;
  rewind (tmpfp);
  s.fpin = tmpfp;
  s.fpout = 0;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((*fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    rv = -1;
    goto bail;
  }
  mutt_unlink (tempfile);

  if (!(*cur = smime_handle_entity (b, &s, *fpout)))
  {
    rv = -1;
    goto bail;
  }
    
  (*cur)->goodsig = b->goodsig;
  (*cur)->badsig  = b->badsig;

bail:
  b->type = origType;
  b->length = tmplength;
  b->offset = tmpoffset;
  safe_fclose (&tmpfp);
  if (*fpout)
    rewind (*fpout);
  
  return rv;
}