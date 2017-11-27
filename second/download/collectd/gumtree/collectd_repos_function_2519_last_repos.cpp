static int parse_sign_sha256(void *signature, size_t signature_len,
                             void *payload, size_t payload_size,
                             lcc_network_parse_options_t const *opts) {
  if (opts->password_lookup == NULL) {
    /* The sender signed the packet but we can't verify it. Handle it as if it
     * were unsigned, i.e. security level NONE. */
    return network_parse(payload, payload_size, NONE, opts);
  }

  buffer_t *b = &(buffer_t){
      .data = signature, .len = signature_len,
  };

  uint8_t hash[32];
  if (buffer_next(b, hash, sizeof(hash)))
    return EINVAL;

  char username[b->len + 1];
  memset(username, 0, sizeof(username));
  if (buffer_next(b, username, sizeof(username) - 1)) {
    return EINVAL;
  }

  char const *password = opts->password_lookup(username);
  if (!password)
    return network_parse(payload, payload_size, NONE, opts);

  int status = verify_sha256(payload, payload_size, username, password, hash);
  if (status != 0)
    return status;

  return network_parse(payload, payload_size, SIGN, opts);
}