
#if (OPENSSL_VERSION_NUMBER < 0x0090808fL)
/* not present in older OpenSSL */
#define OPENSSL_load_builtin_modules(x)
#endif

/*
 * Whether SSL_CTX_set_keylog_callback is available.
 * OpenSSL: supported since 1.1.1 https://github.com/openssl/openssl/pull/2287
 * BoringSSL: supported since d28f59c27bac (committed 2015-11-19), the
 *            BORINGSSL_201512 macro from 2016-01-21 should be close enough.
 * LibreSSL: unsupported in at least 2.5.1 (explicitly check for it since it
 *           lies and pretends to be OpenSSL 2.0.0).
 */
#if (OPENSSL_VERSION_NUMBER >= 0x10101000L && \
     !defined(LIBRESSL_VERSION_NUMBER)) || \
    defined(BORINGSSL_201512)
#define HAVE_KEYLOG_CALLBACK
#endif

#if defined(LIBRESSL_VERSION_NUMBER)
#define OSSL_PACKAGE "LibreSSL"
#elif defined(OPENSSL_IS_BORINGSSL)
#define OSSL_PACKAGE "BoringSSL"
#else
#define OSSL_PACKAGE "OpenSSL"
#endif

#if (OPENSSL_VERSION_NUMBER >= 0x10100000L)
/* up2date versions of OpenSSL maintain the default reasonably secure without
 * breaking compatibility, so it is better not to override the default by curl
 */
#define DEFAULT_CIPHER_SELECTION NULL
#else
/* ... but it is not the case with old versions of OpenSSL */
#define DEFAULT_CIPHER_SELECTION \
  "ALL:!EXPORT:!EXPORT40:!EXPORT56:!aNULL:!LOW:!RC4:@STRENGTH"
#endif

#ifdef ENABLE_SSLKEYLOGFILE
typedef struct ssl_tap_state {
  int master_key_length;
  unsigned char master_key[SSL_MAX_MASTER_KEY_LENGTH];
  unsigned char client_random[SSL3_RANDOM_SIZE];
} ssl_tap_state_t;
#endif /* ENABLE_SSLKEYLOGFILE */

struct ssl_backend_data {
  /* these ones requires specific SSL-types */
  SSL_CTX* ctx;
  SSL*     handle;
  X509*    server_cert;
#ifdef ENABLE_SSLKEYLOGFILE
  /* tap_state holds the last seen master key if we're logging them */
  ssl_tap_state_t tap_state;
#endif
};

#define BACKEND connssl->backend

/*
 * Number of bytes to read from the random number seed file. This must be
 * a finite value (because some entropy "files" like /dev/urandom have
 * an infinite length), but must be large enough to provide enough
 * entropy to properly seed OpenSSL's PRNG.
 */
#define RAND_LOAD_LENGTH 1024

#ifdef ENABLE_SSLKEYLOGFILE
/* The fp for the open SSLKEYLOGFILE, or NULL if not open */
static FILE *keylog_file_fp;

#ifdef HAVE_KEYLOG_CALLBACK
static void ossl_keylog_callback(const SSL *ssl, const char *line)
{
  (void)ssl;

  /* Using fputs here instead of fprintf since libcurl's fprintf replacement
     may not be thread-safe. */
  if(keylog_file_fp && line && *line) {
    char stackbuf[256];
    char *buf;
    size_t linelen = strlen(line);

    if(linelen <= sizeof(stackbuf) - 2)
      buf = stackbuf;
    else {
      buf = malloc(linelen + 2);
      if(!buf)
        return;
    }
    strncpy(buf, line, linelen);
    buf[linelen] = '\n';
    buf[linelen + 1] = '\0';

    fputs(buf, keylog_file_fp);
    if(buf != stackbuf)
      free(buf);
  }
}
#else
#define KEYLOG_PREFIX      "CLIENT_RANDOM "
#define KEYLOG_PREFIX_LEN  (sizeof(KEYLOG_PREFIX) - 1)
/*
 * tap_ssl_key is called by libcurl to make the CLIENT_RANDOMs if the OpenSSL
 * being used doesn't have native support for doing that.
 */
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
#endif /* !HAVE_KEYLOG_CALLBACK */
#endif /* ENABLE_SSLKEYLOGFILE */

static const char *SSL_ERROR_to_str(int err)
{
  switch(err) {
  case SSL_ERROR_NONE:
    return "SSL_ERROR_NONE";
  case SSL_ERROR_SSL:
