static void tap_ssl_key(const SSL *ssl, ssl_tap_state_t *state)
{
  const char *hex = "0123456789ABCDEF";
  int pos, i;
  char line[KEYLOG_PREFIX_LEN + 2 * SSL3_RANDOM_SIZE + 1 +
            2 * SSL_MAX_MASTER_KEY_LENGTH + 1 + 1];
  const SSL_SESSION *session = SSL_get_session(ssl);
  unsigned char client_random[SSL3_RANDOM_SIZE];
  unsigned char master_key[SSL_MAX_MASTER_KEY_LENGTH];
  int master_key_length = 0;

  if(!session || !keylog_file_fp)
    return;

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
  /* ssl->s3 is not checked in openssl 1.1.0-pre6, but let's assume that
   * we have a valid SSL context if we have a non-NULL session. */
  SSL_get_client_random(ssl, client_random, SSL3_RANDOM_SIZE);
  master_key_length =
    SSL_SESSION_get_master_key(session, master_key, SSL_MAX_MASTER_KEY_LENGTH);
#else
  if(ssl->s3 && session->master_key_length > 0) {
    master_key_length = session->master_key_length;
    memcpy(master_key, session->master_key, session->master_key_length);
    memcpy(client_random, ssl->s3->client_random, SSL3_RANDOM_SIZE);
  }
#endif

  if(master_key_length <= 0)
    return;

  /* Skip writing keys if there is no key or it did not change. */
  if(state->master_key_length == master_key_length &&
     !memcmp(state->master_key, master_key, master_key_length) &&
     !memcmp(state->client_random, client_random, SSL3_RANDOM_SIZE)) {
    return;
  }

  state->master_key_length = master_key_length;
  memcpy(state->master_key, master_key, master_key_length);
  memcpy(state->client_random, client_random, SSL3_RANDOM_SIZE);

  memcpy(line, KEYLOG_PREFIX, KEYLOG_PREFIX_LEN);
  pos = KEYLOG_PREFIX_LEN;

  /* Client Random for SSLv3/TLS */
  for(i = 0; i < SSL3_RANDOM_SIZE; i++) {
    line[pos++] = hex[client_random[i] >> 4];
    line[pos++] = hex[client_random[i] & 0xF];
  }
  line[pos++] = ' ';

  /* Master Secret (size is at most SSL_MAX_MASTER_KEY_LENGTH) */
  for(i = 0; i < master_key_length; i++) {
    line[pos++] = hex[master_key[i] >> 4];
    line[pos++] = hex[master_key[i] & 0xF];
  }
  line[pos++] = '\n';
  line[pos] = '\0';

  /* Using fputs here instead of fprintf since libcurl's fprintf replacement
     may not be thread-safe. */
  fputs(line, keylog_file_fp);
}