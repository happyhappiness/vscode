static int decrypt_aes256(buffer_t *b, void *iv, size_t iv_size,
                          char const *password) {
  gcry_cipher_hd_t cipher = NULL;

  if (gcry_cipher_open(&cipher, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_OFB,
                       /* flags = */ 0))
    return -1;

  uint8_t pwhash[32] = {0};
  gcry_md_hash_buffer(GCRY_MD_SHA256, pwhash, password, strlen(password));

  fprintf(stderr, "sizeof(iv) = %zu\n", sizeof(iv));
  if (gcry_cipher_setkey(cipher, pwhash, sizeof(pwhash)) ||
      gcry_cipher_setiv(cipher, iv, iv_size) ||
      gcry_cipher_decrypt(cipher, b->data, b->len, /* in = */ NULL,
                          /* in_size = */ 0)) {
    gcry_cipher_close(cipher);
    return -1;
  }

  gcry_cipher_close(cipher);
  return 0;
}