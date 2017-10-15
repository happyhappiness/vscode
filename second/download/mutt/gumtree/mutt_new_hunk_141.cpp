  if ((WithCrypto & APPLICATION_PGP)
      && post && (hdr->security & APPLICATION_PGP))
  {
    fputs ("X-Mutt-PGP: ", msg->fp);
    if (hdr->security & ENCRYPT)
      fputc ('E', msg->fp);
    if (hdr->security & OPPENCRYPT)
      fputc ('O', msg->fp);
    if (hdr->security & SIGN)
    {
      fputc ('S', msg->fp);
      if (PgpSignAs && *PgpSignAs)
        fprintf (msg->fp, "<%s>", PgpSignAs);
    }
