    if (flags & M_CM_PRINTING)
      s.flags |= M_PRINTING;
    if (flags & M_CM_WEED)
      s.flags |= M_WEED;
    if (flags & M_CM_CHARCONV)
      s.flags |= M_CHARCONV;
    
#ifdef HAVE_PGP
    if (flags & M_CM_VERIFY)
      s.flags |= M_VERIFY;
#endif

    mutt_body_handler (body, &s);
  }
#ifdef HAVE_PGP
  else if ((flags & M_CM_DECODE_PGP) && (hdr->pgp & PGPENCRYPT) &&
      hdr->content->type == TYPEMULTIPART)
  {
    BODY *cur;
    FILE *fp;

    if (pgp_decrypt_mime (fpin, &fp, hdr->content, &cur))
      return (-1);
    fputs ("Mime-Version: 1.0\n", fpout);
    mutt_write_mime_header (cur, fpout);
    fputc ('\n', fpout);

    fseek (fp, cur->offset, 0);
    if (mutt_copy_bytes (fp, fpout, cur->length) == -1)
    {
      fclose (fp);
      mutt_free_body (&cur);
      return (-1);
    }
    mutt_free_body (&cur);
    fclose (fp);
  }
#endif
  else
  {
    fseek (fpin, body->offset, 0);
    if (flags & M_CM_PREFIX)
    {
      int c;
      size_t bytes = body->length;
      
      fputs(prefix, fpout);
