
#include "urldata.h"
#include "rawstr.h"
#include "curl_base64.h"
#include "curl_md5.h"
#include "http_digest.h"
#include "strtok.h"
#include "curl_memory.h"
#include "vtls/vtls.h" /* for Curl_rand() */
#include "non-ascii.h" /* included for Curl_convert_... prototypes */
#include "warnless.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

/* The last #include file should be: */
#include "memdebug.h"

#define MAX_VALUE_LENGTH 256
#define MAX_CONTENT_LENGTH 1024

static void digest_cleanup_one(struct digestdata *dig);

/*
 * Return 0 on success and then the buffers are filled in fine.
 *
 * Non-zero means failure to parse.
 */
static int get_pair(const char *str, char *value, char *content,
                    const char **endptr)
{
  int c;
  bool starts_with_quote = FALSE;
  bool escape = FALSE;

  for(c=MAX_VALUE_LENGTH-1; (*str && (*str != '=') && c--); )
    *value++ = *str++;
  *value=0;

  if('=' != *str++)
    /* eek, no match */
    return 1;

  if('\"' == *str) {
    /* this starts with a quote so it must end with one as well! */
    str++;
    starts_with_quote = TRUE;
  }

  for(c=MAX_CONTENT_LENGTH-1; *str && c--; str++) {
    switch(*str) {
    case '\\':
      if(!escape) {
        /* possibly the start of an escaped quote */
        escape = TRUE;
        *content++ = '\\'; /* even though this is an escape character, we still
                              store it as-is in the target buffer */
        continue;
      }
      break;
    case ',':
      if(!starts_with_quote) {
        /* this signals the end of the content if we didn't get a starting
           quote and then we do "sloppy" parsing */
        c=0; /* the end */
        continue;
      }
      break;
    case '\r':
    case '\n':
      /* end of string */
      c=0;
      continue;
    case '\"':
      if(!escape && starts_with_quote) {
        /* end of string */
        c=0;
        continue;
      }
      break;
    }
    escape = FALSE;
    *content++ = *str;
  }
  *content=0;

  *endptr = str;

  return 0; /* all is fine! */
}

/* Test example headers:

WWW-Authenticate: Digest realm="testrealm", nonce="1053604598"
Proxy-Authenticate: Digest realm="testrealm", nonce="1053604598"

*/

CURLdigest Curl_input_digest(struct connectdata *conn,
                             bool proxy,
                             const char *header) /* rest of the *-authenticate:
                                                    header */
{
  char *token = NULL;
  char *tmp = NULL;
  bool foundAuth = FALSE;
  bool foundAuthInt = FALSE;
  struct SessionHandle *data=conn->data;
  bool before = FALSE; /* got a nonce before */
  struct digestdata *d;

  if(proxy) {
    d = &data->state.proxydigest;
  }
  else {
    d = &data->state.digest;
  }

  if(checkprefix("Digest", header)) {
    header += strlen("Digest");

    /* If we already have received a nonce, keep that in mind */
    if(d->nonce)
      before = TRUE;

    /* clear off any former leftovers and init to defaults */
    digest_cleanup_one(d);

    for(;;) {
      char value[MAX_VALUE_LENGTH];
      char content[MAX_CONTENT_LENGTH];

      while(*header && ISSPACE(*header))
        header++;

      /* extract a value=content pair */
      if(!get_pair(header, value, content, &header)) {
        if(Curl_raw_equal(value, "nonce")) {
          d->nonce = strdup(content);
          if(!d->nonce)
            return CURLDIGEST_NOMEM;
        }
        else if(Curl_raw_equal(value, "stale")) {
          if(Curl_raw_equal(content, "true")) {
            d->stale = TRUE;
            d->nc = 1; /* we make a new nonce now */
          }
        }
        else if(Curl_raw_equal(value, "realm")) {
          d->realm = strdup(content);
          if(!d->realm)
            return CURLDIGEST_NOMEM;
        }
        else if(Curl_raw_equal(value, "opaque")) {
          d->opaque = strdup(content);
          if(!d->opaque)
            return CURLDIGEST_NOMEM;
        }
        else if(Curl_raw_equal(value, "qop")) {
          char *tok_buf;
          /* tokenize the list and choose auth if possible, use a temporary
             clone of the buffer since strtok_r() ruins it */
          tmp = strdup(content);
          if(!tmp)
            return CURLDIGEST_NOMEM;
          token = strtok_r(tmp, ",", &tok_buf);
          while(token != NULL) {
            if(Curl_raw_equal(token, "auth")) {
              foundAuth = TRUE;
            }
            else if(Curl_raw_equal(token, "auth-int")) {
              foundAuthInt = TRUE;
            }
            token = strtok_r(NULL, ",", &tok_buf);
          }
          free(tmp);
          /*select only auth o auth-int. Otherwise, ignore*/
          if(foundAuth) {
            d->qop = strdup("auth");
            if(!d->qop)
              return CURLDIGEST_NOMEM;
          }
          else if(foundAuthInt) {
            d->qop = strdup("auth-int");
            if(!d->qop)
              return CURLDIGEST_NOMEM;
          }
        }
        else if(Curl_raw_equal(value, "algorithm")) {
          d->algorithm = strdup(content);
          if(!d->algorithm)
            return CURLDIGEST_NOMEM;
          if(Curl_raw_equal(content, "MD5-sess"))
            d->algo = CURLDIGESTALGO_MD5SESS;
          else if(Curl_raw_equal(content, "MD5"))
            d->algo = CURLDIGESTALGO_MD5;
          else
            return CURLDIGEST_BADALGO;
        }
        else {
          /* unknown specifier, ignore it! */
        }
      }
      else
        break; /* we're done here */

      /* pass all additional spaces here */
      while(*header && ISSPACE(*header))
        header++;
      if(',' == *header)
        /* allow the list to be comma-separated */
        header++;
    }
    /* We had a nonce since before, and we got another one now without
       'stale=true'. This means we provided bad credentials in the previous
       request */
    if(before && !d->stale)
      return CURLDIGEST_BAD;

    /* We got this header without a nonce, that's a bad Digest line! */
    if(!d->nonce)
      return CURLDIGEST_BAD;
  }
  else
    /* else not a digest, get out */
    return CURLDIGEST_NONE;

  return CURLDIGEST_FINE;
}

/* convert md5 chunk to RFC2617 (section 3.1.3) -suitable ascii string*/
static void md5_to_ascii(unsigned char *source, /* 16 bytes */
                         unsigned char *dest) /* 33 bytes */
{
  int i;
  for(i=0; i<16; i++)
    snprintf((char *)&dest[i*2], 3, "%02x", source[i]);
}

/* Perform quoted-string escaping as described in RFC2616 and its errata */
static char *string_quoted(const char *source)
{
  char *dest, *d;
  const char *s = source;
  size_t n = 1; /* null terminator */

  /* Calculate size needed */
  while(*s) {
    ++n;
    if(*s == '"' || *s == '\\') {
      ++n;
    }
    ++s;
  }

  dest = malloc(n);
  if(dest) {
    s = source;
    d = dest;
    while(*s) {
      if(*s == '"' || *s == '\\') {
        *d++ = '\\';
      }
      *d++ = *s++;
    }
    *d = 0;
  }

  return dest;
}

CURLcode Curl_output_digest(struct connectdata *conn,
                            bool proxy,
                            const unsigned char *request,
                            const unsigned char *uripath)
{
  /* We have a Digest setup for this, use it!  Now, to get all the details for
     this sorted out, I must urge you dear friend to read up on the RFC2617
     section 3.2.2, */
  size_t urilen;
  unsigned char md5buf[16]; /* 16 bytes/128 bits */
  unsigned char request_digest[33];
  unsigned char *md5this;
  unsigned char ha1[33];/* 32 digits and 1 zero byte */
  unsigned char ha2[33];/* 32 digits and 1 zero byte */
  char cnoncebuf[33];
  char *cnonce = NULL;
  size_t cnonce_sz = 0;
  char *tmp = NULL;
  char **allocuserpwd;
  size_t userlen;
  const char *userp;
  char *userp_quoted;
  const char *passwdp;
  struct auth *authp;

  struct SessionHandle *data = conn->data;
  struct digestdata *d;
  CURLcode rc;
/* The CURL_OUTPUT_DIGEST_CONV macro below is for non-ASCII machines.
   It converts digest text to ASCII so the MD5 will be correct for
   what ultimately goes over the network.
*/
#define CURL_OUTPUT_DIGEST_CONV(a, b) \
  rc = Curl_convert_to_network(a, (char *)b, strlen((const char*)b)); \
  if(rc != CURLE_OK) { \
    free(b); \
    return rc; \
  }

  if(proxy) {
    d = &data->state.proxydigest;
    allocuserpwd = &conn->allocptr.proxyuserpwd;
    userp = conn->proxyuser;
    passwdp = conn->proxypasswd;
    authp = &data->state.authproxy;
  }
  else {
    d = &data->state.digest;
    allocuserpwd = &conn->allocptr.userpwd;
    userp = conn->user;
    passwdp = conn->passwd;
