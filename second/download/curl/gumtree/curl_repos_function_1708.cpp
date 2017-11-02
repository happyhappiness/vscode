static void setup_des_key(const unsigned char *key_56,
                          DES_key_schedule DESKEYARG(ks))
{
  DES_cblock key;

  /* Expand the 56-bit key to 64-bits */
  extend_key_56_to_64(key_56, (char *) key);

  /* Set the key parity to odd */
#if defined(HAVE_BORINGSSL)
  Curl_des_set_odd_parity((unsigned char *) &key, sizeof(key));
#else
  DES_set_odd_parity(&key);
#endif

  /* Set the key */
  DES_set_key(&key, ks);
}