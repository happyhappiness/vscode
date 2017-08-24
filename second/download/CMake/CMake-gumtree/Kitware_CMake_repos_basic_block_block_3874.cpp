{
    /* Create LanManager hashed password. */

#ifdef USE_OPENSSL
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
#elif defined(USE_MBEDTLS) || defined(USE_NSS) || defined(USE_DARWINSSL) \
  || defined(USE_OS400CRYPTO) || defined(USE_WIN32_CRYPTO)
    encrypt_des(magic, lmbuffer, pw);
    encrypt_des(magic, lmbuffer + 8, pw + 7);
#endif

    memset(lmbuffer + 16, 0, 21 - 16);
  }