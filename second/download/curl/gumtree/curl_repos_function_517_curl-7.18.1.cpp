static void mk_lm_hash(struct SessionHandle *data,
                       char *password, 
                       unsigned char *lmbuffer /* 21 bytes */)
{
  unsigned char pw[14];
  static const unsigned char magic[] = {
    0x4B, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25 /* i.e. KGS!@#$% */
  };
  unsigned int i;
  size_t len = strlen(password);

  if(len > 14)
    len = 14;

  for (i=0; i<len; i++)
    pw[i] = (unsigned char)toupper(password[i]);

  for (; i<14; i++)
    pw[i] = 0;

#ifdef CURL_DOES_CONVERSIONS
  /*
   * The LanManager hashed password needs to be created using the
   * password in the network encoding not the host encoding.
   */
  if(data)
    Curl_convert_to_network(data, (char *)pw, 14);
#else
  (void)data;
#endif

  {
    /* Create LanManager hashed password. */

    DES_key_schedule ks;

    setup_des_key(pw, DESKEY(ks));
    DES_ecb_encrypt((DES_cblock *)magic, (DES_cblock *)lmbuffer,
                    DESKEY(ks), DES_ENCRYPT);

    setup_des_key(pw+7, DESKEY(ks));
    DES_ecb_encrypt((DES_cblock *)magic, (DES_cblock *)(lmbuffer+8),
                    DESKEY(ks), DES_ENCRYPT);

    memset(lmbuffer + 16, 0, 21 - 16);
  }
  }