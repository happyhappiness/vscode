static void hmac_md5 (const char* password, char* challenge,
  unsigned char* response)
{
  MD5_CTX ctx;
  unsigned char ipad[MD5_BLOCK_LEN], opad[MD5_BLOCK_LEN];
  unsigned char secret[MD5_BLOCK_LEN+1];
  unsigned char hash_passwd[MD5_DIGEST_LEN];
  unsigned int secret_len, chal_len;
  int i;

  secret_len = strlen (password);
  chal_len = strlen (challenge);

  /* passwords longer than MD5_BLOCK_LEN bytes are substituted with their MD5
   * digests */
  if (secret_len > MD5_BLOCK_LEN)
  {
    MD5Init (&ctx);
    MD5Update (&ctx, (unsigned char*) password, secret_len);
    MD5Final (hash_passwd, &ctx);
    strfcpy ((char*) secret, (char*) hash_passwd, MD5_DIGEST_LEN);
    secret_len = MD5_DIGEST_LEN;
  }
  else
    strfcpy ((char *) secret, password, sizeof (secret));

  memset (ipad, 0, sizeof (ipad));
  memset (opad, 0, sizeof (opad));
  memcpy (ipad, secret, secret_len);
  memcpy (opad, secret, secret_len);

  for (i = 0; i < MD5_BLOCK_LEN; i++)
  {
    ipad[i] ^= 0x36;
    opad[i] ^= 0x5c;
  }

  /* inner hash: challenge and ipadded secret */
  MD5Init (&ctx);
  MD5Update (&ctx, ipad, MD5_BLOCK_LEN);
  MD5Update (&ctx, (unsigned char*) challenge, chal_len);
  MD5Final (response, &ctx);

  /* outer hash: inner hash and opadded secret */
  MD5Init (&ctx);
  MD5Update (&ctx, opad, MD5_BLOCK_LEN);
  MD5Update (&ctx, response, MD5_DIGEST_LEN);
  MD5Final (response, &ctx);
}