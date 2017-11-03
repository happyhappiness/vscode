static void copy_clearsigned (gpgme_data_t data, STATE *s, char *charset)
{
  char buf[HUGE_STRING];
  short complete, armor_header;
  FGETCONV *fc;
  char *fname;
  FILE *fp;

  fname = data_object_to_tempfile (data, NULL, &fp);
  if (!fname)
    return;
  unlink (fname);
  FREE (&fname);

  /* fromcode comes from the MIME Content-Type charset label. It might
   * be a wrong label, so we want the ability to do corrections via
   * charset-hooks. Therefore we set flags to MUTT_ICONV_HOOK_FROM.
   */
  fc = fgetconv_open (fp, charset, Charset, MUTT_ICONV_HOOK_FROM);
  
  for (complete = 1, armor_header = 1;
       fgetconvs (buf, sizeof (buf), fc) != NULL;
       complete = strchr (buf, '\n') != NULL)
  {
    if (!complete)
    {
      if (!armor_header)
	state_puts (buf, s);
      continue;
    }

    if (BEGIN_PGP_SIGNATURE(buf))
      break;
    
    if (armor_header)
    {
      if (buf[0] == '\n') 
	armor_header = 0;
      continue;
    }
    
    if (s->prefix) 
      state_puts (s->prefix, s);
    
    if (buf[0] == '-' && buf[1] == ' ')
      state_puts (buf + 2, s);
    else
      state_puts (buf, s);
  }
  
  fgetconv_close (&fc);
  safe_fclose (&fp);
}