@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -26,322 +26,82 @@
 
 #include "urldata.h"
 #include "rawstr.h"
-#include "curl_base64.h"
-#include "curl_md5.h"
+#include "curl_sasl.h"
 #include "http_digest.h"
-#include "strtok.h"
-#include "curl_memory.h"
-#include "vtls/vtls.h" /* for Curl_rand() */
-#include "non-ascii.h" /* included for Curl_convert_... prototypes */
-#include "warnless.h"
-
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
+#include "curl_printf.h"
 
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
-#define MAX_VALUE_LENGTH 256
-#define MAX_CONTENT_LENGTH 1024
-
-static void digest_cleanup_one(struct digestdata *dig);
-
-/*
- * Return 0 on success and then the buffers are filled in fine.
- *
- * Non-zero means failure to parse.
- */
-static int get_pair(const char *str, char *value, char *content,
-                    const char **endptr)
-{
-  int c;
-  bool starts_with_quote = FALSE;
-  bool escape = FALSE;
-
-  for(c=MAX_VALUE_LENGTH-1; (*str && (*str != '=') && c--); )
-    *value++ = *str++;
-  *value=0;
-
-  if('=' != *str++)
-    /* eek, no match */
-    return 1;
-
-  if('\"' == *str) {
-    /* this starts with a quote so it must end with one as well! */
-    str++;
-    starts_with_quote = TRUE;
-  }
-
-  for(c=MAX_CONTENT_LENGTH-1; *str && c--; str++) {
-    switch(*str) {
-    case '\\':
-      if(!escape) {
-        /* possibly the start of an escaped quote */
-        escape = TRUE;
-        *content++ = '\\'; /* even though this is an escape character, we still
-                              store it as-is in the target buffer */
-        continue;
-      }
-      break;
-    case ',':
-      if(!starts_with_quote) {
-        /* this signals the end of the content if we didn't get a starting
-           quote and then we do "sloppy" parsing */
-        c=0; /* the end */
-        continue;
-      }
-      break;
-    case '\r':
-    case '\n':
-      /* end of string */
-      c=0;
-      continue;
-    case '\"':
-      if(!escape && starts_with_quote) {
-        /* end of string */
-        c=0;
-        continue;
-      }
-      break;
-    }
-    escape = FALSE;
-    *content++ = *str;
-  }
-  *content=0;
-
-  *endptr = str;
-
-  return 0; /* all is fine! */
-}
-
 /* Test example headers:
 
 WWW-Authenticate: Digest realm="testrealm", nonce="1053604598"
 Proxy-Authenticate: Digest realm="testrealm", nonce="1053604598"
 
 */
 
-CURLdigest Curl_input_digest(struct connectdata *conn,
-                             bool proxy,
-                             const char *header) /* rest of the *-authenticate:
-                                                    header */
+CURLcode Curl_input_digest(struct connectdata *conn,
+                           bool proxy,
+                           const char *header) /* rest of the *-authenticate:
+                                                  header */
 {
-  char *token = NULL;
-  char *tmp = NULL;
-  bool foundAuth = FALSE;
-  bool foundAuthInt = FALSE;
-  struct SessionHandle *data=conn->data;
-  bool before = FALSE; /* got a nonce before */
-  struct digestdata *d;
+  struct SessionHandle *data = conn->data;
+
+  /* Point to the correct struct with this */
+  struct digestdata *digest;
 
   if(proxy) {
-    d = &data->state.proxydigest;
+    digest = &data->state.proxydigest;
   }
   else {
-    d = &data->state.digest;
-  }
-
-  if(checkprefix("Digest", header)) {
-    header += strlen("Digest");
-
-    /* If we already have received a nonce, keep that in mind */
-    if(d->nonce)
-      before = TRUE;
-
-    /* clear off any former leftovers and init to defaults */
-    digest_cleanup_one(d);
-
-    for(;;) {
-      char value[MAX_VALUE_LENGTH];
-      char content[MAX_CONTENT_LENGTH];
-
-      while(*header && ISSPACE(*header))
-        header++;
-
-      /* extract a value=content pair */
-      if(!get_pair(header, value, content, &header)) {
-        if(Curl_raw_equal(value, "nonce")) {
-          d->nonce = strdup(content);
-          if(!d->nonce)
-            return CURLDIGEST_NOMEM;
-        }
-        else if(Curl_raw_equal(value, "stale")) {
-          if(Curl_raw_equal(content, "true")) {
-            d->stale = TRUE;
-            d->nc = 1; /* we make a new nonce now */
-          }
-        }
-        else if(Curl_raw_equal(value, "realm")) {
-          d->realm = strdup(content);
-          if(!d->realm)
-            return CURLDIGEST_NOMEM;
-        }
-        else if(Curl_raw_equal(value, "opaque")) {
-          d->opaque = strdup(content);
-          if(!d->opaque)
-            return CURLDIGEST_NOMEM;
-        }
-        else if(Curl_raw_equal(value, "qop")) {
-          char *tok_buf;
-          /* tokenize the list and choose auth if possible, use a temporary
-             clone of the buffer since strtok_r() ruins it */
-          tmp = strdup(content);
-          if(!tmp)
-            return CURLDIGEST_NOMEM;
-          token = strtok_r(tmp, ",", &tok_buf);
-          while(token != NULL) {
-            if(Curl_raw_equal(token, "auth")) {
-              foundAuth = TRUE;
-            }
-            else if(Curl_raw_equal(token, "auth-int")) {
-              foundAuthInt = TRUE;
-            }
-            token = strtok_r(NULL, ",", &tok_buf);
-          }
-          free(tmp);
-          /*select only auth o auth-int. Otherwise, ignore*/
-          if(foundAuth) {
-            d->qop = strdup("auth");
-            if(!d->qop)
-              return CURLDIGEST_NOMEM;
-          }
-          else if(foundAuthInt) {
-            d->qop = strdup("auth-int");
-            if(!d->qop)
-              return CURLDIGEST_NOMEM;
-          }
-        }
-        else if(Curl_raw_equal(value, "algorithm")) {
-          d->algorithm = strdup(content);
-          if(!d->algorithm)
-            return CURLDIGEST_NOMEM;
-          if(Curl_raw_equal(content, "MD5-sess"))
-            d->algo = CURLDIGESTALGO_MD5SESS;
-          else if(Curl_raw_equal(content, "MD5"))
-            d->algo = CURLDIGESTALGO_MD5;
-          else
-            return CURLDIGEST_BADALGO;
-        }
-        else {
-          /* unknown specifier, ignore it! */
-        }
-      }
-      else
-        break; /* we're done here */
-
-      /* pass all additional spaces here */
-      while(*header && ISSPACE(*header))
-        header++;
-      if(',' == *header)
-        /* allow the list to be comma-separated */
-        header++;
-    }
-    /* We had a nonce since before, and we got another one now without
-       'stale=true'. This means we provided bad credentials in the previous
-       request */
-    if(before && !d->stale)
-      return CURLDIGEST_BAD;
-
-    /* We got this header without a nonce, that's a bad Digest line! */
-    if(!d->nonce)
-      return CURLDIGEST_BAD;
+    digest = &data->state.digest;
   }
-  else
-    /* else not a digest, get out */
-    return CURLDIGEST_NONE;
-
-  return CURLDIGEST_FINE;
-}
 
-/* convert md5 chunk to RFC2617 (section 3.1.3) -suitable ascii string*/
-static void md5_to_ascii(unsigned char *source, /* 16 bytes */
-                         unsigned char *dest) /* 33 bytes */
-{
-  int i;
-  for(i=0; i<16; i++)
-    snprintf((char *)&dest[i*2], 3, "%02x", source[i]);
-}
-
-/* Perform quoted-string escaping as described in RFC2616 and its errata */
-static char *string_quoted(const char *source)
-{
-  char *dest, *d;
-  const char *s = source;
-  size_t n = 1; /* null terminator */
-
-  /* Calculate size needed */
-  while(*s) {
-    ++n;
-    if(*s == '"' || *s == '\\') {
-      ++n;
-    }
-    ++s;
-  }
+  if(!checkprefix("Digest", header))
+    return CURLE_BAD_CONTENT_ENCODING;
 
-  dest = malloc(n);
-  if(dest) {
-    s = source;
-    d = dest;
-    while(*s) {
-      if(*s == '"' || *s == '\\') {
-        *d++ = '\\';
-      }
-      *d++ = *s++;
-    }
-    *d = 0;
-  }
+  header += strlen("Digest");
+  while(*header && ISSPACE(*header))
+    header++;
 
-  return dest;
+  return Curl_sasl_decode_digest_http_message(header, digest);
 }
 
 CURLcode Curl_output_digest(struct connectdata *conn,
                             bool proxy,
                             const unsigned char *request,
                             const unsigned char *uripath)
 {
-  /* We have a Digest setup for this, use it!  Now, to get all the details for
-     this sorted out, I must urge you dear friend to read up on the RFC2617
-     section 3.2.2, */
-  size_t urilen;
-  unsigned char md5buf[16]; /* 16 bytes/128 bits */
-  unsigned char request_digest[33];
-  unsigned char *md5this;
-  unsigned char ha1[33];/* 32 digits and 1 zero byte */
-  unsigned char ha2[33];/* 32 digits and 1 zero byte */
-  char cnoncebuf[33];
-  char *cnonce = NULL;
-  size_t cnonce_sz = 0;
-  char *tmp = NULL;
+  CURLcode result;
+  struct SessionHandle *data = conn->data;
+  unsigned char *path;
+  char *tmp;
+  char *response;
+  size_t len;
+  bool have_chlg;
+
+  /* Point to the address of the pointer that holds the string to send to the
+     server, which is for a plain host or for a HTTP proxy */
   char **allocuserpwd;
-  size_t userlen;
+
+  /* Point to the name and password for this */
   const char *userp;
-  char *userp_quoted;
   const char *passwdp;
-  struct auth *authp;
 
-  struct SessionHandle *data = conn->data;
-  struct digestdata *d;
-  CURLcode rc;
-/* The CURL_OUTPUT_DIGEST_CONV macro below is for non-ASCII machines.
-   It converts digest text to ASCII so the MD5 will be correct for
-   what ultimately goes over the network.
-*/
-#define CURL_OUTPUT_DIGEST_CONV(a, b) \
-  rc = Curl_convert_to_network(a, (char *)b, strlen((const char*)b)); \
-  if(rc != CURLE_OK) { \
-    free(b); \
-    return rc; \
-  }
+  /* Point to the correct struct with this */
+  struct digestdata *digest;
+  struct auth *authp;
 
   if(proxy) {
-    d = &data->state.proxydigest;
+    digest = &data->state.proxydigest;
     allocuserpwd = &conn->allocptr.proxyuserpwd;
     userp = conn->proxyuser;
     passwdp = conn->proxypasswd;
     authp = &data->state.authproxy;
   }
   else {
-    d = &data->state.digest;
+    digest = &data->state.digest;
     allocuserpwd = &conn->allocptr.userpwd;
     userp = conn->user;
     passwdp = conn->passwd;
@@ -352,75 +112,21 @@ CURLcode Curl_output_digest(struct connectdata *conn,
 
   /* not set means empty */
   if(!userp)
-    userp="";
+    userp = "";
 
   if(!passwdp)
-    passwdp="";
+    passwdp = "";
+
+#if defined(USE_WINDOWS_SSPI)
+  have_chlg = digest->input_token ? TRUE : FALSE;
+#else
+  have_chlg = digest->nonce ? TRUE : FALSE;
+#endif
 
-  if(!d->nonce) {
+  if(!have_chlg) {
     authp->done = FALSE;
     return CURLE_OK;
   }
-  authp->done = TRUE;
-
-  if(!d->nc)
-    d->nc = 1;
-
-  if(!d->cnonce) {
-    snprintf(cnoncebuf, sizeof(cnoncebuf), "%08x%08x%08x%08x",
-             Curl_rand(data), Curl_rand(data),
-             Curl_rand(data), Curl_rand(data));
-    rc = Curl_base64_encode(data, cnoncebuf, strlen(cnoncebuf),
-                            &cnonce, &cnonce_sz);
-    if(rc)
-      return rc;
-    d->cnonce = cnonce;
-  }
-
-  /*
-    if the algorithm is "MD5" or unspecified (which then defaults to MD5):
-
-    A1 = unq(username-value) ":" unq(realm-value) ":" passwd
-
-    if the algorithm is "MD5-sess" then:
-
-    A1 = H( unq(username-value) ":" unq(realm-value) ":" passwd )
-         ":" unq(nonce-value) ":" unq(cnonce-value)
-  */
-
-  md5this = (unsigned char *)
-    aprintf("%s:%s:%s", userp, d->realm, passwdp);
-  if(!md5this)
-    return CURLE_OUT_OF_MEMORY;
-
-  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
-  Curl_md5it(md5buf, md5this);
-  Curl_safefree(md5this);
-  md5_to_ascii(md5buf, ha1);
-
-  if(d->algo == CURLDIGESTALGO_MD5SESS) {
-    /* nonce and cnonce are OUTSIDE the hash */
-    tmp = aprintf("%s:%s:%s", ha1, d->nonce, d->cnonce);
-    if(!tmp)
-      return CURLE_OUT_OF_MEMORY;
-    CURL_OUTPUT_DIGEST_CONV(data, tmp); /* convert on non-ASCII machines */
-    Curl_md5it(md5buf, (unsigned char *)tmp);
-    Curl_safefree(tmp);
-    md5_to_ascii(md5buf, ha1);
-  }
-
-  /*
-    If the "qop" directive's value is "auth" or is unspecified, then A2 is:
-
-      A2       = Method ":" digest-uri-value
-
-          If the "qop" value is "auth-int", then A2 is:
-
-      A2       = Method ":" digest-uri-value ":" H(entity-body)
-
-    (The "Method" value is the HTTP request method as specified in section
-    5.1.1 of RFC 2616)
-  */
 
   /* So IE browsers < v7 cut off the URI part at the query part when they
      evaluate the MD5 and some (IIS?) servers work with them so we may need to
@@ -435,164 +141,39 @@ CURLcode Curl_output_digest(struct connectdata *conn,
      http://www.fngtps.com/2006/09/http-authentication
   */
 
-  if(authp->iestyle && ((tmp = strchr((char *)uripath, '?')) != NULL))
-    urilen = tmp - (char *)uripath;
-  else
-    urilen = strlen((char *)uripath);
-
-  md5this = (unsigned char *)aprintf("%s:%.*s", request, urilen, uripath);
+  if(authp->iestyle && ((tmp = strchr((char *)uripath, '?')) != NULL)) {
+    size_t urilen = tmp - (char *)uripath;
 
-  if(d->qop && Curl_raw_equal(d->qop, "auth-int")) {
-    /* We don't support auth-int for PUT or POST at the moment.
-       TODO: replace md5 of empty string with entity-body for PUT/POST */
-    unsigned char *md5this2 = (unsigned char *)
-      aprintf("%s:%s", md5this, "d41d8cd98f00b204e9800998ecf8427e");
-    Curl_safefree(md5this);
-    md5this = md5this2;
+    path = (unsigned char *) aprintf("%.*s", urilen, uripath);
   }
+  else
+    path = (unsigned char *) strdup((char *) uripath);
 
-  if(!md5this)
-    return CURLE_OUT_OF_MEMORY;
-
-  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
-  Curl_md5it(md5buf, md5this);
-  Curl_safefree(md5this);
-  md5_to_ascii(md5buf, ha2);
-
-  if(d->qop) {
-    md5this = (unsigned char *)aprintf("%s:%s:%08x:%s:%s:%s",
-                                       ha1,
-                                       d->nonce,
-                                       d->nc,
-                                       d->cnonce,
-                                       d->qop,
-                                       ha2);
-  }
-  else {
-    md5this = (unsigned char *)aprintf("%s:%s:%s",
-                                       ha1,
-                                       d->nonce,
-                                       ha2);
-  }
-  if(!md5this)
+  if(!path)
     return CURLE_OUT_OF_MEMORY;
 
-  CURL_OUTPUT_DIGEST_CONV(data, md5this); /* convert on non-ASCII machines */
-  Curl_md5it(md5buf, md5this);
-  Curl_safefree(md5this);
-  md5_to_ascii(md5buf, request_digest);
-
-  /* for test case 64 (snooped from a Mozilla 1.3a request)
-
-    Authorization: Digest username="testuser", realm="testrealm", \
-    nonce="1053604145", uri="/64", response="c55f7f30d83d774a3d2dcacf725abaca"
-
-    Digest parameters are all quoted strings.  Username which is provided by
-    the user will need double quotes and backslashes within it escaped.  For
-    the other fields, this shouldn't be an issue.  realm, nonce, and opaque
-    are copied as is from the server, escapes and all.  cnonce is generated
-    with web-safe characters.  uri is already percent encoded.  nc is 8 hex
-    characters.  algorithm and qop with standard values only contain web-safe
-    chracters.
-  */
-  userp_quoted = string_quoted(userp);
-  if(!userp_quoted)
-    return CURLE_OUT_OF_MEMORY;
+  result = Curl_sasl_create_digest_http_message(data, userp, passwdp, request,
+                                                path, digest, &response, &len);
+  free(path);
+  if(result)
+    return result;
 
-  if(d->qop) {
-    *allocuserpwd =
-      aprintf( "%sAuthorization: Digest "
-               "username=\"%s\", "
-               "realm=\"%s\", "
-               "nonce=\"%s\", "
-               "uri=\"%.*s\", "
-               "cnonce=\"%s\", "
-               "nc=%08x, "
-               "qop=%s, "
-               "response=\"%s\"",
-               proxy?"Proxy-":"",
-               userp_quoted,
-               d->realm,
-               d->nonce,
-               urilen, uripath, /* this is the PATH part of the URL */
-               d->cnonce,
-               d->nc,
-               d->qop,
-               request_digest);
-
-    if(Curl_raw_equal(d->qop, "auth"))
-      d->nc++; /* The nc (from RFC) has to be a 8 hex digit number 0 padded
-                  which tells to the server how many times you are using the
-                  same nonce in the qop=auth mode. */
-  }
-  else {
-    *allocuserpwd =
-      aprintf( "%sAuthorization: Digest "
-               "username=\"%s\", "
-               "realm=\"%s\", "
-               "nonce=\"%s\", "
-               "uri=\"%.*s\", "
-               "response=\"%s\"",
-               proxy?"Proxy-":"",
-               userp_quoted,
-               d->realm,
-               d->nonce,
-               urilen, uripath, /* this is the PATH part of the URL */
-               request_digest);
-  }
-  Curl_safefree(userp_quoted);
+  *allocuserpwd = aprintf("%sAuthorization: Digest %s\r\n",
+                          proxy ? "Proxy-" : "",
+                          response);
+  free(response);
   if(!*allocuserpwd)
     return CURLE_OUT_OF_MEMORY;
 
-  /* Add optional fields */
-  if(d->opaque) {
-    /* append opaque */
-    tmp = aprintf("%s, opaque=\"%s\"", *allocuserpwd, d->opaque);
-    if(!tmp)
-      return CURLE_OUT_OF_MEMORY;
-    free(*allocuserpwd);
-    *allocuserpwd = tmp;
-  }
-
-  if(d->algorithm) {
-    /* append algorithm */
-    tmp = aprintf("%s, algorithm=\"%s\"", *allocuserpwd, d->algorithm);
-    if(!tmp)
-      return CURLE_OUT_OF_MEMORY;
-    free(*allocuserpwd);
-    *allocuserpwd = tmp;
-  }
-
-  /* append CRLF + zero (3 bytes) to the userpwd header */
-  userlen = strlen(*allocuserpwd);
-  tmp = realloc(*allocuserpwd, userlen + 3);
-  if(!tmp)
-    return CURLE_OUT_OF_MEMORY;
-  strcpy(&tmp[userlen], "\r\n"); /* append the data */
-  *allocuserpwd = tmp;
+  authp->done = TRUE;
 
   return CURLE_OK;
 }
 
-static void digest_cleanup_one(struct digestdata *d)
-{
-  Curl_safefree(d->nonce);
-  Curl_safefree(d->cnonce);
-  Curl_safefree(d->realm);
-  Curl_safefree(d->opaque);
-  Curl_safefree(d->qop);
-  Curl_safefree(d->algorithm);
-
-  d->nc = 0;
-  d->algo = CURLDIGESTALGO_MD5; /* default algorithm */
-  d->stale = FALSE; /* default means normal, not stale */
-}
-
-
 void Curl_digest_cleanup(struct SessionHandle *data)
 {
-  digest_cleanup_one(&data->state.digest);
-  digest_cleanup_one(&data->state.proxydigest);
+  Curl_sasl_digest_cleanup(&data->state.digest);
+  Curl_sasl_digest_cleanup(&data->state.proxydigest);
 }
 
 #endif