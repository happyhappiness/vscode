static void pgp_make_pgp3_fingerprint (unsigned char *buff, size_t l,
				       unsigned char *digest)
{
  unsigned char dummy;
  SHA1_CTX context;

  SHA1_Init (&context);

  dummy = buff[0] & 0x3f;

  if (dummy == PT_SUBSECKEY || dummy == PT_SUBKEY || dummy == PT_SECKEY)
    dummy = PT_PUBKEY;

  dummy = (dummy << 2) | 0x81;
  SHA1_Update (&context, &dummy, 1);
  dummy = ((l - 1) >> 8) & 0xff;
  SHA1_Update (&context, &dummy, 1);
  dummy = (l - 1) & 0xff;
  SHA1_Update (&context, &dummy, 1);
  SHA1_Update (&context, buff + 1, l - 1);
  SHA1_Final (digest, &context);

}