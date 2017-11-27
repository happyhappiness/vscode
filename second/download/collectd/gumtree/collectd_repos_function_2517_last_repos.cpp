static int verify_sha256(void *payload, size_t payload_size,
                         char const *username, char const *password,
                         uint8_t hash_provided[32]) {
  gcry_md_hd_t hd = NULL;

  gcry_error_t err = gcry_md_open(&hd, GCRY_MD_SHA256, GCRY_MD_FLAG_HMAC);
  if (err != 0) {
    return (int)err;
  }

  err = gcry_md_setkey(hd, password, strlen(password));
  if (err != 0) {
    gcry_md_close(hd);
    return (int)err;
  }

  gcry_md_write(hd, username, strlen(username));
  gcry_md_write(hd, payload, payload_size);

  unsigned char *hash_calculated = gcry_md_read(hd, GCRY_MD_SHA256);
  if (!hash_calculated) {
    gcry_md_close(hd);
    return -1;
  }

  int ret = memcmp(hash_provided, hash_calculated, 32);

  gcry_md_close(hd);
  hash_calculated = NULL;

  return !!ret;
}