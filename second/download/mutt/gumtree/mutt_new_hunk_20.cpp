    if (flags & M_CM_PRINTING)
      s.flags |= M_PRINTING;
    if (flags & M_CM_WEED)
      s.flags |= M_WEED;
    if (flags & M_CM_CHARCONV)
      s.flags |= M_CHARCONV;
    if (flags & M_CM_REPLYING)
      s.flags |= M_REPLYING;
    
    if (WithCrypto && flags & M_CM_VERIFY)
      s.flags |= M_VERIFY;

    rc = mutt_body_handler (body, &s);
  }
  else if (WithCrypto
           && (flags & M_CM_DECODE_CRYPT) && (hdr->security & ENCRYPT))
  {
    BODY *cur = NULL;
    FILE *fp;

    if ((WithCrypto & APPLICATION_PGP)
        && (flags & M_CM_DECODE_PGP) && (hdr->security & APPLICATION_PGP) &&
	hdr->content->type == TYPEMULTIPART)
    {
      if (crypt_pgp_decrypt_mime (fpin, &fp, hdr->content, &cur))
	return (-1);
      fputs ("MIME-Version: 1.0\n", fpout);
    }

    if ((WithCrypto & APPLICATION_SMIME)
        && (flags & M_CM_DECODE_SMIME) && (hdr->security & APPLICATION_SMIME)
	     && hdr->content->type == TYPEAPPLICATION)
    {
      if (crypt_smime_decrypt_mime (fpin, &fp, hdr->content, &cur))
	return (-1);
    }

    if (!cur)
    {
      mutt_error (_("No decryption engine available for message"));
      return -1;
    }

    mutt_write_mime_header (cur, fpout);
    fputc ('\n', fpout);

    fseeko (fp, cur->offset, 0);
    if (mutt_copy_bytes (fp, fpout, cur->length) == -1)
    {
      safe_fclose (&fp);
      mutt_free_body (&cur);
      return (-1);
    }
    mutt_free_body (&cur);
    safe_fclose (&fp);
  }
  else
  {
    fseeko (fpin, body->offset, 0);
    if (flags & M_CM_PREFIX)
    {
      int c;
      size_t bytes = body->length;
      
      fputs(prefix, fpout);
