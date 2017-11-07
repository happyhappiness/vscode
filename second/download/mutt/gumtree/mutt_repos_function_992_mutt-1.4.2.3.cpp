static SECStatus
mutt_nss_bad_cert (void *arg, PRFileDesc * fd)
{
  PRErrorCode err;
  CERTCertificate *cert, *issuer;
  unsigned char hash[16];
  int i;
  CERTCertTrust trust;
  int64 not_before, not_after;
  event_t ch;
  char status[256];

  /* first lets see why this certificate failed.  we only want to override
   * in the case where the cert was not found.
   */
  err = PR_GetError ();
  mutt_error (_("SSL_AuthCertificate failed (error %d)"), err);

  /* fetch the cert in question */
  cert = SSL_PeerCertificate (fd);

  move (LINES - 8, 0);
  clrtoeol ();
  move (LINES - 7, 0);
  clrtoeol ();
  addstr ("Issuer:      ");
  addstr (CERT_NameToAscii (&cert->issuer));
  move (LINES - 6, 0);
  clrtoeol ();
  addstr ("Subject:     ");
  addstr (CERT_NameToAscii (&cert->subject));

  move (LINES - 5, 0);
  clrtoeol ();
  addstr ("Valid:       ");
  CERT_GetCertTimes (cert, &not_before, &not_after);
  mutt_nss_pretty_time (not_before);
  addstr (" to ");
  mutt_nss_pretty_time (not_after);

  move (LINES - 4, 0);
  clrtoeol ();
  addstr ("Fingerprint: ");

  /* calculate the MD5 hash of the raw certificate */
  HASH_HashBuf (HASH_AlgMD5, hash, cert->derCert.data, cert->derCert.len);
  for (i = 0; i < 16; i++)
  {
    printw ("%0x", hash[i]);
    if (i != 15)
      addch (':');
  }
  
  mvaddstr (LINES - 3, 0, "Signature:   ");
  clrtoeol ();

  /* find the cert which signed this cert */
  issuer = CERT_FindCertByName ((CERTCertDBHandle *) arg, &cert->derIssuer);

  /* verify the sig (only) if we have the issuer cert handy */
  if (issuer &&
      CERT_VerifySignedData (&cert->signatureWrap, issuer, PR_Now (), NULL)
      == SECSuccess)
    addstr ("GOOD");
  else
    addstr ("BAD");

  move (LINES - 2, 0);
  SETCOLOR (MT_COLOR_STATUS);
  memset (status, ' ', sizeof (status) - 1);
  if (COLS < sizeof (status))
    status[COLS - 1] = 0;
  else
    status[sizeof (status) - 1] = 0;
  memcpy (status, "--- SSL Certificate Check",
	  sizeof ("--- SSL Certificate Check") - 1);
  addstr (status);
  clrtoeol ();
  SETCOLOR (MT_COLOR_NORMAL);

  for (;;)
  {
    mvaddstr (LINES - 1, 0, "(r)eject, accept (o)nce, (a)lways accept?");
    clrtoeol ();
    ch = mutt_getch ();
    if (ch.ch == -1)
    {
      i = SECFailure;
      break;
    }
    else if (ascii_tolower (ch.ch) == 'r')
    {
      i = SECFailure;
      break;
    }
    else if (ascii_tolower (ch.ch) == 'o')
    {
      i = SECSuccess;
      break;
    }
    else if (ascii_tolower (ch.ch) == 'a')
    {
      /* push this certificate onto the user's certificate store so it
       * automatically becomes valid next time we see it
       */
      
      /* set this certificate as a valid peer for SSL-auth ONLY. */
      CERT_DecodeTrustString (&trust, "P,,");
      
      CERT_AddTempCertToPerm (cert, NULL, &trust);
      i = SECSuccess;
      break;
    }
    BEEP ();
  }
  
  /* SSL_PeerCertificate() returns a copy with an updated ref count, so
   * we have to destroy our copy here.
   */
  CERT_DestroyCertificate (cert);
  
  return i;
}