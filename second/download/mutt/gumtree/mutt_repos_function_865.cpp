static char *asn1time_to_string (ASN1_UTCTIME *tm)
{
  static char buf[64];
  BIO *bio;

  strfcpy (buf, _("[invalid date]"), sizeof (buf));

  bio = BIO_new (BIO_s_mem());
  if (bio)
  {
    if (ASN1_TIME_print (bio, tm))
      (void) BIO_read (bio, buf, sizeof (buf));
    BIO_free (bio);
  }

  return buf;
}