static int parse_encrypt_aes256(void *data, size_t data_size,
                                lcc_network_parse_options_t const *opts) {
  if (opts->password_lookup == NULL) {
    /* Without a password source it's (hopefully) impossible to decrypt the
     * network packet. */
    return ENOENT;
  }

  buffer_t *b = &(buffer_t){
      .data = data, .len = data_size,
  };

  uint16_t username_len;
  if (buffer_uint16(b, &username_len))
    return EINVAL;
  if ((size_t)username_len > data_size)
    return ENOMEM;
  char username[((size_t)username_len) + 1];
  memset(username, 0, sizeof(username));
  if (buffer_next(b, username, (size_t)username_len))
    return EINVAL;

  char const *password = opts->password_lookup(username);
  if (!password)
    return ENOENT;

  uint8_t iv[16];
  if (buffer_next(b, iv, sizeof(iv)))
    return EINVAL;

  int status = decrypt_aes256(b, iv, sizeof(iv), password);
  if (status != 0)
    return status;

  uint8_t hash_provided[20];
  if (buffer_next(b, hash_provided, sizeof(hash_provided))) {
    return -1;
  }

  uint8_t hash_calculated[20];
  gcry_md_hash_buffer(GCRY_MD_SHA1, hash_calculated, b->data, b->len);

  if (memcmp(hash_provided, hash_calculated, sizeof(hash_provided)) != 0) {
    return -1;
  }

  return network_parse(b->data, b->len, ENCRYPT, opts);
}