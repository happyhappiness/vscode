void Curl_ntlm_core_mk_lm_hash(struct SessionHandle *data,
                               const char *password,
                               unsigned char *lmbuffer /* 21 bytes */)
{
  CURLcode res;
  unsigned char pw[14];
  static const unsigned char magic[] = {
    0x4B, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25 /* i.e. KGS!@#$% */
  };
  size_t len = CURLMIN(strlen(password), 14);

  Curl_strntoupper((char *)pw, password, len);
  memset(&pw[len], 0, 14 - len);

  /*
   * The LanManager hashed password needs to be created using the
   * password in the network encoding not the host encoding.
   */
  res = Curl_convert_to_network(data, (char *)pw, 14);
  if(res)
    return;

  {
    /* Create LanManager hashed password. */

#ifdef USE_SSLEAY
    DES_key_schedule ks;

    setup_des_key(pw, DESKEY(ks));
    DES_ecb_encrypt((DES_cblock *)magic, (DES_cblock *)lmbuffer,
                    DESKEY(ks), DES_ENCRYPT);

    setup_des_key(pw + 7, DESKEY(ks));
    DES_ecb_encrypt((DES_cblock *)magic, (DES_cblock *)(lmbuffer + 8),
                    DESKEY(ks), DES_ENCRYPT);
#elif defined(USE_GNUTLS_NETTLE)
    struct des_ctx des;
    setup_des_key(pw, &des);
    des_encrypt(&des, 8, lmbuffer, magic);
    setup_des_key(pw + 7, &des);
    des_encrypt(&des, 8, lmbuffer + 8, magic);
#elif defined(USE_GNUTLS)
    gcry_cipher_hd_t des;

    gcry_cipher_open(&des, GCRY_CIPHER_DES, GCRY_CIPHER_MODE_ECB, 0);
    setup_des_key(pw, &des);
    gcry_cipher_encrypt(des, lmbuffer, 8, magic, 8);
    gcry_cipher_close(des);

    gcry_cipher_open(&des, GCRY_CIPHER_DES, GCRY_CIPHER_MODE_ECB, 0);
    setup_des_key(pw + 7, &des);
    gcry_cipher_encrypt(des, lmbuffer + 8, 8, magic, 8);
    gcry_cipher_close(des);
#elif defined(USE_NSS) || defined(USE_DARWINSSL)
    encrypt_des(magic, lmbuffer, pw);
    encrypt_des(magic, lmbuffer + 8, pw + 7);
#endif

    memset(lmbuffer + 16, 0, 21 - 16);
  }
}