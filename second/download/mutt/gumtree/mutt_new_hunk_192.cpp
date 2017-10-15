    mutt_free_body (&cur);
    safe_fclose (&fp);
  }
  else
  {
    fseeko (fpin, body->offset, 0);
    if (flags & MUTT_CM_PREFIX)
    {
      int c;
      size_t bytes = body->length;
      
      fputs(prefix, fpout);
      
