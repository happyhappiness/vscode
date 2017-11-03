static void hmac_md5 (const char* password, char* challenge,
  unsigned char* response)
{
  struct md5_ctx ctx;
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
    md5_buffer (password, secret_len, hash_passwd);
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
  md5_init_ctx (&ctx);
  md5_process_bytes (ipad, MD5_BLOCK_LEN, &ctx);
  md5_process_bytes (challenge, chal_len, &ctx);
  md5_finish_ctx (&ctx, response);

  /* outer hash: inner hash and opadded secret */
  md5_init_ctx (&ctx);
  md5_process_bytes (opad, MD5_BLOCK_LEN, &ctx);
  md5_process_bytes (response, MD5_DIGEST_LEN, &ctx);
  md5_finish_ctx (&ctx, response);
}