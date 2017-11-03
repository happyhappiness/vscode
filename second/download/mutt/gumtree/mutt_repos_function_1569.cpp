int crypt_write_signed(BODY *a, STATE *s, const char *tempfile)
{
  FILE *fp;
  int c;
  short hadcr;
  size_t bytes;

  if (!WithCrypto)
    return -1;

  if (!(fp = safe_fopen (tempfile, "w")))
  {
    mutt_perror (tempfile);
    return -1;
  }
      
  fseeko (s->fpin, a->hdr_offset, 0);
  bytes = a->length + a->offset - a->hdr_offset;
  hadcr = 0;
  while (bytes > 0)
  {
    if ((c = fgetc (s->fpin)) == EOF)
      break;
    
    bytes--;
    
    if  (c == '\r')
      hadcr = 1;
    else 
    {
      if (c == '\n' && !hadcr)
	fputc ('\r', fp);
      
      hadcr = 0;
    }
    
    fputc (c, fp);
    
  }
  safe_fclose (&fp);

  return 0;
}