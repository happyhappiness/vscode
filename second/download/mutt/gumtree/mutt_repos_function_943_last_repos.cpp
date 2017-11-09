int fgetconv (FGETCONV *_fc)
{
  struct fgetconv_s *fc = (struct fgetconv_s *)_fc;

  if (!fc)
    return EOF;
  if (fc->cd == (iconv_t)-1)
    return fgetc (fc->file);
  if (!fc->p)
    return EOF;
  if (fc->p < fc->ob)
    return (unsigned char)*(fc->p)++;

  /* Try to convert some more */
  fc->p = fc->ob = fc->bufo;
  if (fc->ibl)
  {
    size_t obl = sizeof (fc->bufo);
    iconv (fc->cd, (ICONV_CONST char **)&fc->ib, &fc->ibl, &fc->ob, &obl);
    if (fc->p < fc->ob)
      return (unsigned char)*(fc->p)++;
  }

  /* If we trusted iconv a bit more, we would at this point
   * ask why it had stopped converting ... */

  /* Try to read some more */
  if (fc->ibl == sizeof (fc->bufi) ||
      (fc->ibl && fc->ib + fc->ibl < fc->bufi + sizeof (fc->bufi)))
  {
    fc->p = 0;
    return EOF;
  }
  if (fc->ibl)
    memcpy (fc->bufi, fc->ib, fc->ibl);
  fc->ib = fc->bufi;
  fc->ibl += fread (fc->ib + fc->ibl, 1, sizeof (fc->bufi) - fc->ibl, fc->file);

  /* Try harder this time to convert some */
  if (fc->ibl)
  {
    size_t obl = sizeof (fc->bufo);
    mutt_iconv (fc->cd, (ICONV_CONST char **)&fc->ib, &fc->ibl, &fc->ob, &obl,
		fc->inrepls, 0);
    if (fc->p < fc->ob)
      return (unsigned char)*(fc->p)++;
  }

  /* Either the file has finished or one of the buffers is too small */
  fc->p = 0;
  return EOF;
}