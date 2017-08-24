@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -30,12 +30,14 @@
 #include <stdarg.h>
 #include <stdlib.h>
 #include <ctype.h>
+#ifdef HAVE_SYS_TYPES_H
 #include <sys/types.h>
+#endif
+#ifdef HAVE_SYS_STAT_H
 #include <sys/stat.h>
+#endif
 
-#include <errno.h>
-
-#if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
+#ifdef WIN32
 #include <time.h>
 #include <io.h>
 #else
@@ -45,7 +47,9 @@
 #ifdef HAVE_NETINET_IN_H
 #include <netinet/in.h>
 #endif
+#ifdef HAVE_SYS_TIME_H
 #include <sys/time.h>
+#endif
 
 #ifdef HAVE_TIME_H
 #ifdef TIME_WITH_SYS_TIME
@@ -70,30 +74,31 @@
 #include <sys/param.h>
 #endif
 
-#ifdef HAVE_SYS_SELECT_H
-#include <sys/select.h>
-#endif
-
 #endif
 
 #include "urldata.h"
 #include <curl/curl.h>
 #include "transfer.h"
 #include "sendf.h"
+#include "easyif.h" /* for Curl_convert_... prototypes */
 #include "formdata.h"
 #include "progress.h"
 #include "base64.h"
 #include "cookie.h"
 #include "strequal.h"
-#include "ssluse.h"
+#include "sslgen.h"
 #include "http_digest.h"
 #include "http_ntlm.h"
 #include "http_negotiate.h"
 #include "url.h"
 #include "share.h"
 #include "hostip.h"
 #include "http.h"
-#include "curl_memory.h"
+#include "memory.h"
+#include "select.h"
+#include "parsedate.h" /* for the week day and month names */
+#include "strtoofft.h"
+#include "multiif.h"
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
@@ -145,12 +150,12 @@ static CURLcode Curl_output_basic(struct connectdata *conn, bool proxy)
   }
 
   snprintf(data->state.buffer, sizeof(data->state.buffer), "%s:%s", user, pwd);
-  if(Curl_base64_encode(data->state.buffer,
+  if(Curl_base64_encode(data, data->state.buffer,
                         strlen(data->state.buffer),
                         &authorization) > 0) {
     if(*userp)
       free(*userp);
-    *userp = aprintf( "%sAuthorization: Basic %s\015\012",
+    *userp = aprintf( "%sAuthorization: Basic %s\r\n",
                       proxy?"Proxy-":"",
                       authorization);
     free(authorization);
@@ -192,6 +197,104 @@ static bool pickoneauth(struct auth *pick)
 }
 
 /*
+ * perhapsrewind()
+ *
+ * If we are doing POST or PUT {
+ *   If we have more data to send {
+ *     If we are doing NTLM {
+ *       Keep sending since we must not disconnect
+ *     }
+ *     else {
+ *       If there is more than just a little data left to send, close
+ *       the current connection by force.
+ *     }
+ *   }
+ *   If we have sent any data {
+ *     If we don't have track of all the data {
+ *       call app to tell it to rewind
+ *     }
+ *     else {
+ *       rewind internally so that the operation can restart fine
+ *     }
+ *   }
+ * }
+ */
+static CURLcode perhapsrewind(struct connectdata *conn)
+{
+  struct SessionHandle *data = conn->data;
+  struct HTTP *http = data->reqdata.proto.http;
+  struct Curl_transfer_keeper *k = &data->reqdata.keep;
+  curl_off_t bytessent;
+  curl_off_t expectsend = -1; /* default is unknown */
+
+  if(!http)
+    /* If this is still NULL, we have not reach very far and we can
+       safely skip this rewinding stuff */
+    return CURLE_OK;
+
+  bytessent = http->writebytecount;
+
+  if(conn->bits.authneg)
+    /* This is a state where we are known to be negotiating and we don't send
+       any data then. */
+    expectsend = 0;
+  else {
+    /* figure out how much data we are expected to send */
+    switch(data->set.httpreq) {
+    case HTTPREQ_POST:
+      if(data->set.postfieldsize != -1)
+        expectsend = data->set.postfieldsize;
+      break;
+    case HTTPREQ_PUT:
+      if(data->set.infilesize != -1)
+        expectsend = data->set.infilesize;
+      break;
+    case HTTPREQ_POST_FORM:
+      expectsend = http->postsize;
+      break;
+    default:
+      break;
+    }
+  }
+
+  conn->bits.rewindaftersend = FALSE; /* default */
+
+  if((expectsend == -1) || (expectsend > bytessent)) {
+    /* There is still data left to send */
+    if((data->state.authproxy.picked == CURLAUTH_NTLM) ||
+       (data->state.authhost.picked == CURLAUTH_NTLM)) {
+      if(((expectsend - bytessent) < 2000) ||
+         (conn->ntlm.state != NTLMSTATE_NONE)) {
+        /* The NTLM-negotiation has started *OR* there is just a little (<2K)
+           data left to send, keep on sending. */
+
+        /* rewind data when completely done sending! */
+        if(!conn->bits.authneg)
+          conn->bits.rewindaftersend = TRUE;
+
+        return CURLE_OK;
+      }
+      if(conn->bits.close)
+        /* this is already marked to get closed */
+        return CURLE_OK;
+
+      infof(data, "NTLM send, close instead of sending %" FORMAT_OFF_T
+            " bytes\n", (curl_off_t)(expectsend - bytessent));
+    }
+
+    /* This is not NTLM or NTLM with many bytes left to send: close
+     */
+    conn->bits.close = TRUE;
+    k->size = 0; /* don't download any more than 0 bytes */
+  }
+
+  if(bytessent)
+    return Curl_readrewind(conn);
+
+  return CURLE_OK;
+}
+
+/*
  * Curl_http_auth_act() gets called when a all HTTP headers have been received
  * and it checks what authentication methods that are available and decides
  * which one (if any) to use. It will set 'newurl' if an auth metod was
@@ -205,43 +308,56 @@ CURLcode Curl_http_auth_act(struct connectdata *conn)
   bool pickproxy = FALSE;
   CURLcode code = CURLE_OK;
 
+  if(100 == data->reqdata.keep.httpcode)
+    /* this is a transient response code, ignore */
+    return CURLE_OK;
+
   if(data->state.authproblem)
     return data->set.http_fail_on_error?CURLE_HTTP_RETURNED_ERROR:CURLE_OK;
 
   if(conn->bits.user_passwd &&
-     ((conn->keep.httpcode == 401) ||
-      (conn->bits.authprobe && conn->keep.httpcode < 300))) {
+     ((data->reqdata.keep.httpcode == 401) ||
+      (conn->bits.authneg && data->reqdata.keep.httpcode < 300))) {
     pickhost = pickoneauth(&data->state.authhost);
     if(!pickhost)
       data->state.authproblem = TRUE;
   }
   if(conn->bits.proxy_user_passwd &&
-     ((conn->keep.httpcode == 407) ||
-      (conn->bits.authprobe && conn->keep.httpcode < 300))) {
+     ((data->reqdata.keep.httpcode == 407) ||
+      (conn->bits.authneg && data->reqdata.keep.httpcode < 300))) {
     pickproxy = pickoneauth(&data->state.authproxy);
     if(!pickproxy)
       data->state.authproblem = TRUE;
   }
 
-  if(pickhost || pickproxy)
-    conn->newurl = strdup(data->change.url); /* clone URL */
+  if(pickhost || pickproxy) {
+    data->reqdata.newurl = strdup(data->change.url); /* clone URL */
+
+    if((data->set.httpreq != HTTPREQ_GET) &&
+       (data->set.httpreq != HTTPREQ_HEAD) &&
+       !conn->bits.rewindaftersend) {
+      code = perhapsrewind(conn);
+      if(code)
+        return code;
+    }
+  }
 
-  else if((conn->keep.httpcode < 300) &&
+  else if((data->reqdata.keep.httpcode < 300) &&
           (!data->state.authhost.done) &&
-          conn->bits.authprobe) {
+          conn->bits.authneg) {
     /* no (known) authentication available,
        authentication is not "done" yet and
        no authentication seems to be required and
        we didn't try HEAD or GET */
     if((data->set.httpreq != HTTPREQ_GET) &&
        (data->set.httpreq != HTTPREQ_HEAD)) {
-      conn->newurl = strdup(data->change.url); /* clone URL */
+      data->reqdata.newurl = strdup(data->change.url); /* clone URL */
       data->state.authhost.done = TRUE;
     }
   }
   if (Curl_http_should_fail(conn)) {
     failf (data, "The requested URL returned error: %d",
-           conn->keep.httpcode);
+           data->reqdata.keep.httpcode);
     code = CURLE_HTTP_RETURNED_ERROR;
   }
 
@@ -272,50 +388,48 @@ Curl_http_output_auth(struct connectdata *conn,
   CURLcode result = CURLE_OK;
   struct SessionHandle *data = conn->data;
   char *auth=NULL;
+  struct auth *authhost;
+  struct auth *authproxy;
 
   curlassert(data);
 
+  authhost = &data->state.authhost;
+  authproxy = &data->state.authproxy;
+
   if((conn->bits.httpproxy && conn->bits.proxy_user_passwd) ||
      conn->bits.user_passwd)
     /* continue please */ ;
   else {
-    data->state.authhost.done = TRUE;
-    data->state.authproxy.done = TRUE;
+    authhost->done = TRUE;
+    authproxy->done = TRUE;
     return CURLE_OK; /* no authentication with no user or password */
   }
 
-  if(data->state.authhost.want && !data->state.authhost.picked)
+  if(authhost->want && !authhost->picked)
     /* The app has selected one or more methods, but none has been picked
        so far by a server round-trip. Then we set the picked one to the
        want one, and if this is one single bit it'll be used instantly. */
-    data->state.authhost.picked = data->state.authhost.want;
+    authhost->picked = authhost->want;
 
-  if(data->state.authproxy.want && !data->state.authproxy.picked)
+  if(authproxy->want && !authproxy->picked)
     /* The app has selected one or more methods, but none has been picked so
        far by a proxy round-trip. Then we set the picked one to the want one,
        and if this is one single bit it'll be used instantly. */
-    data->state.authproxy.picked = data->state.authproxy.want;
-
-  /* To prevent the user+password to get sent to other than the original
-     host due to a location-follow, we do some weirdo checks here */
-  if(!data->state.this_is_a_follow ||
-     !data->state.auth_host ||
-     curl_strequal(data->state.auth_host, conn->host.name) ||
-     data->set.http_disable_hostname_check_before_authentication) {
-
-    /* Send proxy authentication header if needed */
-    if (conn->bits.httpproxy &&
-        (conn->bits.tunnel_proxy == proxytunnel)) {
-#ifdef USE_SSLEAY
-      if(data->state.authproxy.want == CURLAUTH_NTLM) {
-        auth=(char *)"NTLM";
-        result = Curl_output_ntlm(conn, TRUE);
-        if(result)
-          return result;
-      }
-      else
+    authproxy->picked = authproxy->want;
+
+  /* Send proxy authentication header if needed */
+  if (conn->bits.httpproxy &&
+      (conn->bits.tunnel_proxy == proxytunnel)) {
+#ifdef USE_NTLM
+    if(authproxy->picked == CURLAUTH_NTLM) {
+      auth=(char *)"NTLM";
+      result = Curl_output_ntlm(conn, TRUE);
+      if(result)
+        return result;
+    }
+    else
 #endif
-      if(data->state.authproxy.want == CURLAUTH_BASIC) {
+      if(authproxy->picked == CURLAUTH_BASIC) {
         /* Basic */
         if(conn->bits.proxy_user_passwd &&
            !checkheaders(data, "Proxy-authorization:")) {
@@ -324,9 +438,12 @@ Curl_http_output_auth(struct connectdata *conn,
           if(result)
             return result;
         }
-        data->state.authproxy.done = TRUE;
+        /* NOTE: Curl_output_basic() should set 'done' TRUE, as the other auth
+           functions work that way */
+        authproxy->done = TRUE;
       }
-      else if(data->state.authproxy.want == CURLAUTH_DIGEST) {
+#ifndef CURL_DISABLE_CRYPTO_AUTH
+      else if(authproxy->picked == CURLAUTH_DIGEST) {
         auth=(char *)"Digest";
         result = Curl_output_digest(conn,
                                     TRUE, /* proxy */
@@ -335,32 +452,45 @@ Curl_http_output_auth(struct connectdata *conn,
         if(result)
           return result;
       }
-
-      infof(data, "Proxy auth using %s with user '%s'\n",
-            auth, conn->proxyuser?conn->proxyuser:"");
+#endif
+      if(auth) {
+        infof(data, "Proxy auth using %s with user '%s'\n",
+              auth, conn->proxyuser?conn->proxyuser:"");
+        authproxy->multi = (bool)(!authproxy->done);
+      }
+      else
+        authproxy->multi = FALSE;
     }
-    else
-      /* we have no proxy so let's pretend we're done authenticating
-         with it */
-      data->state.authproxy.done = TRUE;
+  else
+    /* we have no proxy so let's pretend we're done authenticating
+       with it */
+    authproxy->done = TRUE;
+
+  /* To prevent the user+password to get sent to other than the original
+     host due to a location-follow, we do some weirdo checks here */
+  if(!data->state.this_is_a_follow ||
+     conn->bits.netrc ||
+     !data->state.first_host ||
+     curl_strequal(data->state.first_host, conn->host.name) ||
+     data->set.http_disable_hostname_check_before_authentication) {
 
     /* Send web authentication header if needed */
     {
       auth = NULL;
 #ifdef HAVE_GSSAPI
-      if((data->state.authhost.want == CURLAUTH_GSSNEGOTIATE) &&
+      if((authhost->picked == CURLAUTH_GSSNEGOTIATE) &&
          data->state.negotiate.context &&
          !GSS_ERROR(data->state.negotiate.status)) {
         auth=(char *)"GSS-Negotiate";
         result = Curl_output_negotiate(conn);
         if (result)
           return result;
-        data->state.authhost.done = TRUE;
+        authhost->done = TRUE;
       }
       else
 #endif
-#ifdef USE_SSLEAY
-      if(data->state.authhost.picked == CURLAUTH_NTLM) {
+#ifdef USE_NTLM
+      if(authhost->picked == CURLAUTH_NTLM) {
         auth=(char *)"NTLM";
         result = Curl_output_ntlm(conn, FALSE);
         if(result)
@@ -369,16 +499,18 @@ Curl_http_output_auth(struct connectdata *conn,
       else
 #endif
       {
-        if(data->state.authhost.picked == CURLAUTH_DIGEST) {
+#ifndef CURL_DISABLE_CRYPTO_AUTH
+        if(authhost->picked == CURLAUTH_DIGEST) {
           auth=(char *)"Digest";
           result = Curl_output_digest(conn,
                                       FALSE, /* not a proxy */
                                       (unsigned char *)request,
                                       (unsigned char *)path);
           if(result)
             return result;
-        }
-        else if(data->state.authhost.picked == CURLAUTH_BASIC) {
+        } else
+#endif
+        if(authhost->picked == CURLAUTH_BASIC) {
           if(conn->bits.user_passwd &&
              !checkheaders(data, "Authorization:")) {
             auth=(char *)"Basic";
@@ -387,16 +519,21 @@ Curl_http_output_auth(struct connectdata *conn,
               return result;
           }
           /* basic is always ready */
-          data->state.authhost.done = TRUE;
+          authhost->done = TRUE;
         }
       }
-      if(auth)
+      if(auth) {
         infof(data, "Server auth using %s with user '%s'\n",
               auth, conn->user);
+
+        authhost->multi = (bool)(!authhost->done);
+      }
+      else
+        authhost->multi = FALSE;
     }
   }
   else
-    data->state.authhost.done = TRUE;
+    authhost->done = TRUE;
 
   return result;
 }
@@ -433,15 +570,15 @@ CURLcode Curl_http_input_auth(struct connectdata *conn,
   }
 
   /* pass all white spaces */
-  while(*start && isspace((int)*start))
+  while(*start && ISSPACE(*start))
     start++;
 
   /*
-   * Here we check if we want the specific single authentiction (using ==) and
+   * Here we check if we want the specific single authentication (using ==) and
    * if we do, we initiate usage of it.
    *
    * If the provided authentication is wanted as one out of several accepted
-   * types (using &), we OR this authenticaion type to the authavail
+   * types (using &), we OR this authentication type to the authavail
    * variable.
    */
 
@@ -454,8 +591,8 @@ CURLcode Curl_http_input_auth(struct connectdata *conn,
       /* if exactly this is wanted, go */
       int neg = Curl_input_negotiate(conn, start);
       if (neg == 0) {
-        conn->newurl = strdup(data->change.url);
-        data->state.authproblem = (conn->newurl == NULL);
+        data->reqdata.newurl = strdup(data->change.url);
+        data->state.authproblem = (data->reqdata.newurl == NULL);
       }
       else {
         infof(data, "Authentication problem. Ignoring this.\n");
@@ -465,7 +602,7 @@ CURLcode Curl_http_input_auth(struct connectdata *conn,
   }
   else
 #endif
-#ifdef USE_SSLEAY
+#ifdef USE_NTLM
     /* NTLM support requires the SSL crypto libs */
     if(checkprefix("NTLM", start)) {
       *availp |= CURLAUTH_NTLM;
@@ -485,22 +622,30 @@ CURLcode Curl_http_input_auth(struct connectdata *conn,
     }
     else
 #endif
+#ifndef CURL_DISABLE_CRYPTO_AUTH
       if(checkprefix("Digest", start)) {
-        CURLdigest dig;
-        *availp |= CURLAUTH_DIGEST;
-        authp->avail |= CURLAUTH_DIGEST;
-
-        /* We call this function on input Digest headers even if Digest
-         * authentication isn't activated yet, as we need to store the
-         * incoming data from this header in case we are gonna use Digest. */
-        dig = Curl_input_digest(conn, (bool)(httpcode == 407), start);
-
-        if(CURLDIGEST_FINE != dig) {
-          infof(data, "Authentication problem. Ignoring this.\n");
-          data->state.authproblem = TRUE;
+        if((authp->avail & CURLAUTH_DIGEST) != 0) {
+          infof(data, "Ignoring duplicate digest auth header.\n");
+        }
+        else {
+          CURLdigest dig;
+          *availp |= CURLAUTH_DIGEST;
+          authp->avail |= CURLAUTH_DIGEST;
+
+          /* We call this function on input Digest headers even if Digest
+           * authentication isn't activated yet, as we need to store the
+           * incoming data from this header in case we are gonna use Digest. */
+          dig = Curl_input_digest(conn, (bool)(httpcode == 407), start);
+
+          if(CURLDIGEST_FINE != dig) {
+            infof(data, "Authentication problem. Ignoring this.\n");
+            data->state.authproblem = TRUE;
+          }
         }
       }
-      else if(checkprefix("Basic", start)) {
+      else
+#endif
+      if(checkprefix("Basic", start)) {
         *availp |= CURLAUTH_BASIC;
         authp->avail |= CURLAUTH_BASIC;
         if(authp->picked == CURLAUTH_BASIC) {
@@ -538,7 +683,7 @@ int Curl_http_should_fail(struct connectdata *conn)
   /*
   ** For readability
   */
-  k = &conn->keep;
+  k = &data->reqdata.keep;
 
   /*
   ** If we haven't been asked to fail on error,
@@ -553,6 +698,14 @@ int Curl_http_should_fail(struct connectdata *conn)
   if (k->httpcode < 400)
     return 0;
 
+  if (data->reqdata.resume_from &&
+      (data->set.httpreq==HTTPREQ_GET) &&
+      (k->httpcode == 416)) {
+    /* "Requested Range Not Satisfiable", just proceed and
+       pretend this is no error */
+    return 0;
+  }
+
   /*
   ** Any code >= 400 that's not 401 or 407 is always
   ** a terminal error
@@ -585,7 +738,7 @@ int Curl_http_should_fail(struct connectdata *conn)
   infof(data,"%s: authavail = 0x%08x\n",__FUNCTION__,data->state.authavail);
   infof(data,"%s: httpcode = %d\n",__FUNCTION__,k->httpcode);
   infof(data,"%s: authdone = %d\n",__FUNCTION__,data->state.authdone);
-  infof(data,"%s: newurl = %s\n",__FUNCTION__,conn->newurl ? conn->newurl : "(null)");
+  infof(data,"%s: newurl = %s\n",__FUNCTION__,data->reqdata.newurl ? data->reqdata.newurl : "(null)");
   infof(data,"%s: authproblem = %d\n",__FUNCTION__,data->state.authproblem);
 #endif
 
@@ -615,15 +768,15 @@ static size_t readmoredata(char *buffer,
                            void *userp)
 {
   struct connectdata *conn = (struct connectdata *)userp;
-  struct HTTP *http = conn->proto.http;
+  struct HTTP *http = conn->data->reqdata.proto.http;
   size_t fullsize = size * nitems;
 
   if(0 == http->postsize)
     /* nothing to return */
     return 0;
 
   /* make sure that a HTTP request is never sent away chunked! */
-  conn->bits.forbidchunk= (http->sending == HTTPSEND_REQUEST)?TRUE:FALSE;
+  conn->bits.forbidchunk = (bool)(http->sending == HTTPSEND_REQUEST);
 
   if(http->postsize <= (curl_off_t)fullsize) {
     memcpy(buffer, http->postdata, (size_t)http->postsize);
@@ -667,6 +820,8 @@ struct send_buffer {
 };
 typedef struct send_buffer send_buffer;
 
+static CURLcode add_custom_headers(struct connectdata *conn,
+                                   send_buffer *req_buffer);
 static CURLcode
  add_buffer(send_buffer *in, const void *inptr, size_t size);
 
@@ -686,30 +841,53 @@ send_buffer *add_buffer_init(void)
 }
 
 /*
- * add_buffer_send() sends a buffer and frees all associated memory.
+ * add_buffer_send() sends a header buffer and frees all associated memory.
+ * Body data may be appended to the header data if desired.
  *
  * Returns CURLcode
  */
 static
 CURLcode add_buffer_send(send_buffer *in,
                          struct connectdata *conn,
-                         long *bytes_written) /* add the number of sent
+                         long *bytes_written, /* add the number of sent
                                                  bytes to this counter */
+                         size_t included_body_bytes, /* how much of the buffer
+                                        contains body data (for log tracing) */
+                         int socketindex)
+
 {
   ssize_t amount;
   CURLcode res;
   char *ptr;
   size_t size;
-  struct HTTP *http = conn->proto.http;
+  struct HTTP *http = conn->data->reqdata.proto.http;
   size_t sendsize;
-  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
+  curl_socket_t sockfd;
+
+  curlassert(socketindex <= SECONDARYSOCKET);
+
+  sockfd = conn->sock[socketindex];
 
   /* The looping below is required since we use non-blocking sockets, but due
      to the circumstances we will just loop and try again and again etc */
 
   ptr = in->buffer;
   size = in->size_used;
 
+#ifdef CURL_DOES_CONVERSIONS
+  if(size - included_body_bytes > 0) {
+    res = Curl_convert_to_network(conn->data, ptr, size - included_body_bytes);
+    /* Curl_convert_to_network calls failf if unsuccessful */
+    if(res != CURLE_OK) {
+      /* conversion failed, free memory and return to the caller */
+      if(in->buffer)
+        free(in->buffer);
+      free(in);
+      return res;
+    }
+  }
+#endif /* CURL_DOES_CONVERSIONS */
+
   if(conn->protocol & PROT_HTTPS) {
     /* We never send more than CURL_MAX_WRITE_SIZE bytes in one single chunk
        when we speak HTTPS, as if only a fraction of it is sent now, this data
@@ -735,41 +913,61 @@ CURLcode add_buffer_send(send_buffer *in,
 
   if(CURLE_OK == res) {
 
-    if(conn->data->set.verbose)
+    if(conn->data->set.verbose) {
       /* this data _may_ contain binary stuff */
-      Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr, amount,
-                 conn->host.dispname);
+      Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr,
+                 (size_t)(amount-included_body_bytes), conn);
+      if (included_body_bytes)
+        Curl_debug(conn->data, CURLINFO_DATA_OUT,
+                   ptr+amount-included_body_bytes,
+                   (size_t)included_body_bytes, conn);
+    }
 
     *bytes_written += amount;
 
-    if((size_t)amount != size) {
-      /* The whole request could not be sent in one system call. We must queue
-         it up and send it later when we get the chance. We must not loop here
-         and wait until it might work again. */
+    if(http) {
+      if((size_t)amount != size) {
+        /* The whole request could not be sent in one system call. We must
+           queue it up and send it later when we get the chance. We must not
+           loop here and wait until it might work again. */
 
-      size -= amount;
+        size -= amount;
 
-      ptr = in->buffer + amount;
+        ptr = in->buffer + amount;
 
-      /* backup the currently set pointers */
-      http->backup.fread = conn->fread;
-      http->backup.fread_in = conn->fread_in;
-      http->backup.postdata = http->postdata;
-      http->backup.postsize = http->postsize;
+        /* backup the currently set pointers */
+        http->backup.fread = conn->fread;
+        http->backup.fread_in = conn->fread_in;
+        http->backup.postdata = http->postdata;
+        http->backup.postsize = http->postsize;
 
-      /* set the new pointers for the request-sending */
-      conn->fread = (curl_read_callback)readmoredata;
-      conn->fread_in = (void *)conn;
-      http->postdata = ptr;
-      http->postsize = (curl_off_t)size;
+        /* set the new pointers for the request-sending */
+        conn->fread = (curl_read_callback)readmoredata;
+        conn->fread_in = (void *)conn;
+        http->postdata = ptr;
+        http->postsize = (curl_off_t)size;
 
-      http->send_buffer = in;
-      http->sending = HTTPSEND_REQUEST;
+        http->send_buffer = in;
+        http->sending = HTTPSEND_REQUEST;
 
-      return CURLE_OK;
+        return CURLE_OK;
+      }
+      http->sending = HTTPSEND_BODY;
+      /* the full buffer was sent, clean up and return */
+    }
+    else {
+      if((size_t)amount != size)
+        /* We have no continue-send mechanism now, fail. This can only happen
+           when this function is used from the CONNECT sending function. We
+           currently (stupidly) assume that the whole request is always sent
+           away in the first single chunk.
+
+           This needs FIXing.
+        */
+        return CURLE_SEND_ERROR;
+      else
+        conn->writechannel_inuse = FALSE;
     }
-    http->sending = HTTPSEND_BODY;
-    /* the full buffer was sent, clean up and return */
   }
   if(in->buffer)
     free(in->buffer);
@@ -868,7 +1066,7 @@ Curl_compareheader(char *headerline,    /* line to check */
   start = &headerline[hlen];
 
   /* pass all white spaces */
-  while(*start && isspace((int)*start))
+  while(*start && ISSPACE(*start))
     start++;
 
   /* find the end of the header line */
@@ -895,121 +1093,155 @@ Curl_compareheader(char *headerline,    /* line to check */
 }
 
 /*
- * ConnectHTTPProxyTunnel() requires that we're connected to a HTTP proxy. This
+ * Curl_proxyCONNECT() requires that we're connected to a HTTP proxy. This
  * function will issue the necessary commands to get a seamless tunnel through
  * this proxy. After that, the socket can be used just as a normal socket.
+ *
+ * This badly needs to be rewritten. CONNECT should be sent and dealt with
+ * like any ordinary HTTP request, and not specially crafted like this. This
+ * function only remains here like this for now since the rewrite is a bit too
+ * much work to do at the moment.
+ *
+ * This function is BLOCKING which is nasty for all multi interface using apps.
  */
 
-CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
-                                     int sockindex,
-                                     char *hostname,
-                                     int remote_port)
+CURLcode Curl_proxyCONNECT(struct connectdata *conn,
+                           int sockindex,
+                           char *hostname,
+                           int remote_port)
 {
   int subversion=0;
   struct SessionHandle *data=conn->data;
-  struct Curl_transfer_keeper *k = &conn->keep;
+  struct Curl_transfer_keeper *k = &data->reqdata.keep;
   CURLcode result;
   int res;
-
   size_t nread;   /* total size read */
   int perline; /* count bytes per line */
-  bool keepon=TRUE;
+  int keepon=TRUE;
   ssize_t gotbytes;
   char *ptr;
-  long timeout; /* default timeout in seconds */
-  struct timeval interval;
-  fd_set rkeepfd;
-  fd_set readfd;
+  long timeout =
+    data->set.timeout?data->set.timeout:3600; /* in seconds */
   char *line_start;
   char *host_port;
   curl_socket_t tunnelsocket = conn->sock[sockindex];
+  send_buffer *req_buffer;
+  curl_off_t cl=0;
+  bool closeConnection = FALSE;
 
 #define SELECT_OK      0
 #define SELECT_ERROR   1
 #define SELECT_TIMEOUT 2
   int error = SELECT_OK;
 
   infof(data, "Establish HTTP proxy tunnel to %s:%d\n", hostname, remote_port);
+  conn->bits.proxy_connect_closed = FALSE;
 
   do {
-    if(conn->newurl) {
+    if(data->reqdata.newurl) {
       /* This only happens if we've looped here due to authentication reasons,
          and we don't really use the newly cloned URL here then. Just free()
          it. */
-      free(conn->newurl);
-      conn->newurl = NULL;
+      free(data->reqdata.newurl);
+      data->reqdata.newurl = NULL;
     }
 
+    /* initialize a dynamic send-buffer */
+    req_buffer = add_buffer_init();
+
+    if(!req_buffer)
+      return CURLE_OUT_OF_MEMORY;
+
     host_port = aprintf("%s:%d", hostname, remote_port);
     if(!host_port)
       return CURLE_OUT_OF_MEMORY;
 
     /* Setup the proxy-authorization header, if any */
     result = Curl_http_output_auth(conn, (char *)"CONNECT", host_port, TRUE);
+
     if(CURLE_OK == result) {
+      char *host=(char *)"";
+      const char *proxyconn="";
+      const char *useragent="";
+
+      if(!checkheaders(data, "Host:")) {
+        host = aprintf("Host: %s\r\n", host_port);
+        if(!host)
+          result = CURLE_OUT_OF_MEMORY;
+      }
+      if(!checkheaders(data, "Proxy-Connection:"))
+        proxyconn = "Proxy-Connection: Keep-Alive\r\n";
 
-      /* OK, now send the connect request to the proxy */
-      result =
-        Curl_sendf(tunnelsocket, conn,
-                   "CONNECT %s:%d HTTP/1.0\015\012"
-                   "%s"
-                   "%s"
-                   "\r\n",
-                   hostname, remote_port,
-                   conn->bits.proxy_user_passwd?
-                   conn->allocptr.proxyuserpwd:"",
-                   data->set.useragent?conn->allocptr.uagent:""
-                   );
+      if(!checkheaders(data, "User-Agent:") && data->set.useragent)
+        useragent = conn->allocptr.uagent;
+
+      if(CURLE_OK == result) {
+        /* Send the connect request to the proxy */
+        /* BLOCKING */
+        result =
+          add_bufferf(req_buffer,
+                      "CONNECT %s:%d HTTP/1.0\r\n"
+                      "%s"  /* Host: */
+                      "%s"  /* Proxy-Authorization */
+                      "%s"  /* User-Agent */
+                      "%s", /* Proxy-Connection */
+                      hostname, remote_port,
+                      host,
+                      conn->allocptr.proxyuserpwd?
+                      conn->allocptr.proxyuserpwd:"",
+                      useragent,
+                      proxyconn);
+
+        if(CURLE_OK == result)
+          result = add_custom_headers(conn, req_buffer);
+
+        if(host && *host)
+          free(host);
+
+        if(CURLE_OK == result)
+          /* CRLF terminate the request */
+          result = add_bufferf(req_buffer, "\r\n");
+
+        if(CURLE_OK == result)
+          /* Now send off the request */
+          result = add_buffer_send(req_buffer, conn,
+                                   &data->info.request_size, 0, sockindex);
+      }
       if(result)
         failf(data, "Failed sending CONNECT to proxy");
     }
     free(host_port);
     if(result)
       return result;
 
-    FD_ZERO (&readfd);          /* clear it */
-    FD_SET (tunnelsocket, &readfd);     /* read socket */
-
-    /* get this in a backup variable to be able to restore it on each lap in
-       the select() loop */
-    rkeepfd = readfd;
-
     ptr=data->state.buffer;
     line_start = ptr;
 
     nread=0;
     perline=0;
+    keepon=TRUE;
 
     while((nread<BUFSIZE) && (keepon && !error)) {
-      readfd = rkeepfd;     /* set every lap */
-      interval.tv_sec = 1;  /* timeout each second and check the timeout */
-      interval.tv_usec = 0;
-
-      if(data->set.timeout) {
-        /* if timeout is requested, find out how much remaining time we have */
-        timeout = data->set.timeout - /* timeout time */
-          Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
-        if(timeout <=0 ) {
-          failf(data, "Proxy connection aborted due to timeout");
-          error = SELECT_TIMEOUT; /* already too little time */
-          break;
-        }
+
+      /* if timeout is requested, find out how much remaining time we have */
+      long check = timeout - /* timeout time */
+        Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
+      if(check <=0 ) {
+        failf(data, "Proxy CONNECT aborted due to timeout");
+        error = SELECT_TIMEOUT; /* already too little time */
+        break;
       }
 
-      switch (select (tunnelsocket+1, &readfd, NULL, NULL, &interval)) {
+      /* timeout each second and check the timeout */
+      switch (Curl_select(tunnelsocket, CURL_SOCKET_BAD, 1000)) {
       case -1: /* select() error, stop reading */
         error = SELECT_ERROR;
         failf(data, "Proxy CONNECT aborted due to select() error");
         break;
       case 0: /* timeout */
         break;
       default:
-        /*
-         * This code previously didn't use the kerberos sec_read() code
-         * to read, but when we use Curl_read() it may do so. Do confirm
-         * that this is still ok and then remove this comment!
-         */
-        res= Curl_read(conn, tunnelsocket, ptr, BUFSIZE-nread, &gotbytes);
+        res = Curl_read(conn, tunnelsocket, ptr, BUFSIZE-nread, &gotbytes);
         if(res< 0)
           /* EWOULDBLOCK */
           continue; /* go loop yourself */
@@ -1024,32 +1256,39 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
           /*
            * We got a whole chunk of data, which can be anything from one byte
            * to a set of lines and possibly just a piece of the last line.
-           *
-           * TODO: To make this code work less error-prone, we need to make
-           * sure that we read and create full lines before we compare them,
-           * as there is really nothing that stops the proxy from delivering
-           * the response lines in multiple parts, each part consisting of
-           * only a little piece of the line(s).  */
+           */
           int i;
 
           nread += gotbytes;
+
+          if(keepon > TRUE) {
+            /* This means we are currently ignoring a response-body, so we
+               simply count down our counter and make sure to break out of the
+               loop when we're done! */
+            cl -= gotbytes;
+            if(cl<=0) {
+              keepon = FALSE;
+              break;
+            }
+          }
+          else
           for(i = 0; i < gotbytes; ptr++, i++) {
             perline++; /* amount of bytes in this line so far */
             if(*ptr=='\n') {
               char letter;
               int writetype;
 
-              /* output debug output if that is requested */
+              /* output debug if that is requested */
               if(data->set.verbose)
-                Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline,
-                           conn->host.dispname);
+                Curl_debug(data, CURLINFO_HEADER_IN,
+                           line_start, (size_t)perline, conn);
 
               /* send the header to the callback */
               writetype = CLIENTWRITE_HEADER;
               if(data->set.include_header)
                 writetype |= CLIENTWRITE_BODY;
 
-              result = Curl_client_write(data, writetype, line_start, perline);
+              result = Curl_client_write(conn, writetype, line_start, perline);
               if(result)
                 return result;
 
@@ -1060,7 +1299,21 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
               if(('\r' == line_start[0]) ||
                  ('\n' == line_start[0])) {
                 /* end of response-headers from the proxy */
-                keepon=FALSE;
+                if(cl && (407 == k->httpcode) && !data->state.authproblem) {
+                  /* If we get a 407 response code with content length when we
+                   * have no auth problem, we must ignore the whole
+                   * response-body */
+                  keepon = 2;
+                  infof(data, "Ignore %" FORMAT_OFF_T
+                        " bytes of response-body\n", cl);
+                  cl -= (gotbytes - i);/* remove the remaining chunk of what
+                                          we already read */
+                  if(cl<=0)
+                    /* if the whole thing was already read, we are done! */
+                    keepon=FALSE;
+                }
+                else
+                  keepon = FALSE;
                 break; /* breaks out of for-loop, not switch() */
               }
 
@@ -1075,6 +1328,13 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
                 if(result)
                   return result;
               }
+              else if(checkprefix("Content-Length:", line_start)) {
+                cl = curlx_strtoofft(line_start + strlen("Content-Length:"),
+                                     NULL, 10);
+              }
+              else if(Curl_compareheader(line_start,
+                                         "Connection:", "close"))
+                closeConnection = TRUE;
               else if(2 == sscanf(line_start, "HTTP/1.%d %d",
                                   &subversion,
                                   &k->httpcode)) {
@@ -1101,11 +1361,21 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
          headers. 'newurl' is set to a new URL if we must loop. */
       Curl_http_auth_act(conn);
 
-  } while(conn->newurl);
+    if (closeConnection && data->reqdata.newurl) {
+      /* Connection closed by server. Don't use it anymore */
+      sclose(conn->sock[sockindex]);
+      conn->sock[sockindex] = CURL_SOCKET_BAD;
+      break;
+    }
+  } while(data->reqdata.newurl);
 
   if(200 != k->httpcode) {
     failf(data, "Received HTTP code %d from proxy after CONNECT",
           k->httpcode);
+
+    if (closeConnection && data->reqdata.newurl)
+      conn->bits.proxy_connect_closed = TRUE;
+
     return CURLE_RECV_ERROR;
   }
 
@@ -1125,7 +1395,7 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
  * Curl_http_connect() performs HTTP stuff to do at connect-time, called from
  * the generic Curl_connect().
  */
-CURLcode Curl_http_connect(struct connectdata *conn)
+CURLcode Curl_http_connect(struct connectdata *conn, bool *done)
 {
   struct SessionHandle *data;
   CURLcode result;
@@ -1135,53 +1405,117 @@ CURLcode Curl_http_connect(struct connectdata *conn)
   /* If we are not using a proxy and we want a secure connection, perform SSL
    * initialization & connection now.  If using a proxy with https, then we
    * must tell the proxy to CONNECT to the host we want to talk to.  Only
-   * after the connect has occured, can we start talking SSL
+   * after the connect has occurred, can we start talking SSL
    */
 
-  if(conn->bits.tunnel_proxy) {
+  if(conn->bits.tunnel_proxy && conn->bits.httpproxy) {
 
     /* either SSL over proxy, or explicitly asked for */
-    result = Curl_ConnectHTTPProxyTunnel(conn, FIRSTSOCKET,
-                                         conn->host.name,
-                                         conn->remote_port);
+    result = Curl_proxyCONNECT(conn, FIRSTSOCKET,
+                               conn->host.name,
+                               conn->remote_port);
     if(CURLE_OK != result)
       return result;
   }
 
+  if(!data->state.this_is_a_follow) {
+    /* this is not a followed location, get the original host name */
+    if (data->state.first_host)
+      /* Free to avoid leaking memory on multiple requests*/
+      free(data->state.first_host);
+
+    data->state.first_host = strdup(conn->host.name);
+    if(!data->state.first_host)
+      return CURLE_OUT_OF_MEMORY;
+  }
+
   if(conn->protocol & PROT_HTTPS) {
-    /* now, perform the SSL initialization for this socket */
-    result = Curl_SSLConnect(conn, FIRSTSOCKET);
-    if(result)
-      return result;
+    /* perform SSL initialization */
+    if(data->state.used_interface == Curl_if_multi) {
+      result = Curl_https_connecting(conn, done);
+      if(result)
+        return result;
+    }
+    else {
+      /* BLOCKING */
+      result = Curl_ssl_connect(conn, FIRSTSOCKET);
+      if(result)
+        return result;
+      *done = TRUE;
+    }
+  }
+  else {
+    *done = TRUE;
   }
 
-  if(conn->bits.user_passwd && !data->state.this_is_a_follow) {
-    /* Authorization: is requested, this is not a followed location, get the
-       original host name */
-    if (data->state.auth_host)
-      /* Free to avoid leaking memory on multiple requests*/
-      free(data->state.auth_host);
+  return CURLE_OK;
+}
 
-    data->state.auth_host = strdup(conn->host.name);
-  }
+CURLcode Curl_https_connecting(struct connectdata *conn, bool *done)
+{
+  CURLcode result;
+  curlassert(conn->protocol & PROT_HTTPS);
+
+  /* perform SSL initialization for this socket */
+  result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, done);
+  if(result)
+    return result;
 
   return CURLE_OK;
 }
 
+#ifdef USE_SSLEAY
+/* This function is OpenSSL-specific. It should be made to query the generic
+   SSL layer instead. */
+int Curl_https_getsock(struct connectdata *conn,
+                       curl_socket_t *socks,
+                       int numsocks)
+{
+  if (conn->protocol & PROT_HTTPS) {
+    struct ssl_connect_data *connssl = &conn->ssl[FIRSTSOCKET];
+
+    if(!numsocks)
+      return GETSOCK_BLANK;
+
+    if (connssl->connecting_state == ssl_connect_2_writing) {
+      /* write mode */
+      socks[0] = conn->sock[FIRSTSOCKET];
+      return GETSOCK_WRITESOCK(0);
+    }
+    else if (connssl->connecting_state == ssl_connect_2_reading) {
+      /* read mode */
+      socks[0] = conn->sock[FIRSTSOCKET];
+      return GETSOCK_READSOCK(0);
+    }
+  }
+  return CURLE_OK;
+}
+#else
+#ifdef USE_GNUTLS
+int Curl_https_getsock(struct connectdata *conn,
+                       curl_socket_t *socks,
+                       int numsocks)
+{
+  (void)conn;
+  (void)socks;
+  (void)numsocks;
+  return GETSOCK_BLANK;
+}
+#endif
+#endif
+
 /*
  * Curl_http_done() gets called from Curl_done() after a single HTTP request
  * has been performed.
  */
 
 CURLcode Curl_http_done(struct connectdata *conn,
-                        CURLcode status)
+                        CURLcode status, bool premature)
 {
-  struct SessionHandle *data;
-  struct HTTP *http;
-  (void)status; /* no use for us */
-
-  data=conn->data;
-  http=conn->proto.http;
+  struct SessionHandle *data = conn->data;
+  struct HTTP *http =data->reqdata.proto.http;
+  struct Curl_transfer_keeper *k = &data->reqdata.keep;
+  (void)premature; /* not used */
 
   /* set the proper values (possibly modified on POST) */
   conn->fread = data->set.fread; /* restore */
@@ -1195,16 +1529,24 @@ CURLcode Curl_http_done(struct connectdata *conn,
 
     free(buff->buffer);
     free(buff);
-    http->send_buffer = NULL; /* cleaer the pointer */
+    http->send_buffer = NULL; /* clear the pointer */
   }
 
   if(HTTPREQ_POST_FORM == data->set.httpreq) {
-    conn->bytecount = http->readbytecount + http->writebytecount;
+    k->bytecount = http->readbytecount + http->writebytecount;
 
-    Curl_formclean(http->sendit); /* Now free that whole lot */
+    Curl_formclean(&http->sendit); /* Now free that whole lot */
+    if(http->form.fp) {
+      /* a file being uploaded was left opened, close it! */
+      fclose(http->form.fp);
+      http->form.fp = NULL;
+    }
   }
   else if(HTTPREQ_PUT == data->set.httpreq)
-    conn->bytecount = http->readbytecount + http->writebytecount;
+    k->bytecount = http->readbytecount + http->writebytecount;
+
+  if (status != CURLE_OK)
+    return (status);
 
   if(!conn->bits.retry &&
      ((http->readbytecount +
@@ -1220,38 +1562,106 @@ CURLcode Curl_http_done(struct connectdata *conn,
   return CURLE_OK;
 }
 
+/* check and possibly add an Expect: header */
+static CURLcode expect100(struct SessionHandle *data,
+                          send_buffer *req_buffer)
+{
+  CURLcode result = CURLE_OK;
+  data->state.expect100header = FALSE; /* default to false unless it is set
+                                          to TRUE below */
+  if((data->set.httpversion != CURL_HTTP_VERSION_1_0) &&
+     !checkheaders(data, "Expect:")) {
+    /* if not doing HTTP 1.0 or disabled explicitly, we add a Expect:
+       100-continue to the headers which actually speeds up post
+       operations (as there is one packet coming back from the web
+       server) */
+    result = add_bufferf(req_buffer,
+                         "Expect: 100-continue\r\n");
+    if(result == CURLE_OK)
+      data->state.expect100header = TRUE;
+  }
+  return result;
+}
+
+static CURLcode add_custom_headers(struct connectdata *conn,
+                                   send_buffer *req_buffer)
+{
+  CURLcode result = CURLE_OK;
+  char *ptr;
+  struct curl_slist *headers=conn->data->set.headers;
+
+  while(headers) {
+    ptr = strchr(headers->data, ':');
+    if(ptr) {
+      /* we require a colon for this to be a true header */
+
+      ptr++; /* pass the colon */
+      while(*ptr && ISSPACE(*ptr))
+        ptr++;
+
+      if(*ptr) {
+        /* only send this if the contents was non-blank */
+
+        if(conn->allocptr.host &&
+           /* a Host: header was sent already, don't pass on any custom Host:
+              header as that will produce *two* in the same request! */
+           curl_strnequal("Host:", headers->data, 5))
+          ;
+        else if(conn->data->set.httpreq == HTTPREQ_POST_FORM &&
+                /* this header (extended by formdata.c) is sent later */
+                curl_strnequal("Content-Type:", headers->data,
+                               strlen("Content-Type:")))
+          ;
+        else {
+          result = add_bufferf(req_buffer, "%s\r\n", headers->data);
+          if(result)
+            return result;
+        }
+      }
+    }
+    headers = headers->next;
+  }
+  return result;
+}
+
 /*
  * Curl_http() gets called from the generic Curl_do() function when a HTTP
  * request is to be performed. This creates and sends a properly constructed
  * HTTP request.
  */
-CURLcode Curl_http(struct connectdata *conn)
+CURLcode Curl_http(struct connectdata *conn, bool *done)
 {
   struct SessionHandle *data=conn->data;
   char *buf = data->state.buffer; /* this is a short cut to the buffer */
-  CURLcode result;
+  CURLcode result=CURLE_OK;
   struct HTTP *http;
-  char *ppath = conn->path;
+  char *ppath = data->reqdata.path;
   char *host = conn->host.name;
-  const char *te = ""; /* tranfer-encoding */
+  const char *te = ""; /* transfer-encoding */
   char *ptr;
   char *request;
   Curl_HttpReq httpreq = data->set.httpreq;
   char *addcookies = NULL;
+  curl_off_t included_body = 0;
 
-  if(!conn->proto.http) {
+  /* Always consider the DO phase done after this function call, even if there
+     may be parts of the request that is not yet sent, since we can deal with
+     the rest of the request in the PERFORM phase. */
+  *done = TRUE;
+
+  if(!data->reqdata.proto.http) {
     /* Only allocate this struct if we don't already have it! */
 
     http = (struct HTTP *)malloc(sizeof(struct HTTP));
     if(!http)
       return CURLE_OUT_OF_MEMORY;
     memset(http, 0, sizeof(struct HTTP));
-    conn->proto.http = http;
+    data->reqdata.proto.http = http;
   }
   else
-    http = conn->proto.http;
+    http = data->reqdata.proto.http;
 
-  /* We default to persistant connections */
+  /* We default to persistent connections */
   conn->bits.close = FALSE;
 
   if ( (conn->protocol&(PROT_HTTP|PROT_FTP)) &&
@@ -1300,81 +1710,77 @@ CURLcode Curl_http(struct connectdata *conn)
   if(result)
     return result;
 
-  if((!data->state.authhost.done || !data->state.authproxy.done ) &&
-     (httpreq != HTTPREQ_GET)) {
-    /* Until we are authenticated, we switch over to HEAD. Unless its a GET
-       we want to do. The explanation for this is rather long and boring, but
-       the point is that it can't be done otherwise without risking having to
-       send the POST or PUT data multiple times. */
-    httpreq = HTTPREQ_HEAD;
-    request = (char *)"HEAD";
-    conn->bits.no_body = TRUE;
-    conn->bits.authprobe = TRUE; /* this is a request done to probe for
-                                    authentication methods */
+  if((data->state.authhost.multi || data->state.authproxy.multi) &&
+     (httpreq != HTTPREQ_GET) &&
+     (httpreq != HTTPREQ_HEAD)) {
+    /* Auth is required and we are not authenticated yet. Make a PUT or POST
+       with content-length zero as a "probe". */
+    conn->bits.authneg = TRUE;
   }
   else
-    conn->bits.authprobe = FALSE;
+    conn->bits.authneg = FALSE;
 
   Curl_safefree(conn->allocptr.ref);
   if(data->change.referer && !checkheaders(data, "Referer:"))
-    conn->allocptr.ref = aprintf("Referer: %s\015\012", data->change.referer);
+    conn->allocptr.ref = aprintf("Referer: %s\r\n", data->change.referer);
   else
     conn->allocptr.ref = NULL;
 
   if(data->set.cookie && !checkheaders(data, "Cookie:"))
     addcookies = data->set.cookie;
 
-  if(!conn->bits.upload_chunky && (httpreq != HTTPREQ_GET)) {
-    /* not a chunky transfer yet, but data is to be sent */
-    ptr = checkheaders(data, "Transfer-Encoding:");
-    if(ptr) {
-      /* Some kind of TE is requested, check if 'chunked' is chosen */
-      conn->bits.upload_chunky =
-        Curl_compareheader(ptr, "Transfer-Encoding:", "chunked");
-      te = "";
-    }
+  if(!checkheaders(data, "Accept-Encoding:") &&
+     data->set.encoding) {
+    Curl_safefree(conn->allocptr.accept_encoding);
+    conn->allocptr.accept_encoding =
+      aprintf("Accept-Encoding: %s\r\n", data->set.encoding);
+    if(!conn->allocptr.accept_encoding)
+      return CURLE_OUT_OF_MEMORY;
   }
-  else if(conn->bits.upload_chunky) {
-    /* RFC2616 section 4.4:
-       Messages MUST NOT include both a Content-Length header field and a
-       non-identity transfer-coding. If the message does include a non-
-       identity transfer-coding, the Content-Length MUST be ignored. */
 
-    if(!checkheaders(data, "Transfer-Encoding:")) {
+  ptr = checkheaders(data, "Transfer-Encoding:");
+  if(ptr) {
+    /* Some kind of TE is requested, check if 'chunked' is chosen */
+    conn->bits.upload_chunky =
+      Curl_compareheader(ptr, "Transfer-Encoding:", "chunked");
+  }
+  else {
+    if (httpreq == HTTPREQ_GET)
+      conn->bits.upload_chunky = FALSE;
+    if(conn->bits.upload_chunky)
       te = "Transfer-Encoding: chunked\r\n";
-    }
-    else {
-      te = "";
-      conn->bits.upload_chunky = FALSE; /* transfer-encoding was disabled,
-                                           so don't chunkify this! */
-    }
   }
 
   Curl_safefree(conn->allocptr.host);
 
   ptr = checkheaders(data, "Host:");
-  if(ptr && !data->state.this_is_a_follow) {
+  if(ptr && (!data->state.this_is_a_follow ||
+             curl_strequal(data->state.first_host, conn->host.name))) {
+#if !defined(CURL_DISABLE_COOKIES)
     /* If we have a given custom Host: header, we extract the host name in
        order to possibly use it for cookie reasons later on. We only allow the
        custom Host: header if this is NOT a redirect, as setting Host: in the
-       redirected request is being out on thin ice. */
+       redirected request is being out on thin ice. Except if the host name
+       is the same as the first one! */
     char *start = ptr+strlen("Host:");
-    while(*start && isspace((int)*start ))
+    while(*start && ISSPACE(*start ))
       start++;
     ptr = start; /* start host-scanning here */
 
     /* scan through the string to find the end (space or colon) */
-    while(*ptr && !isspace((int)*ptr) && !(':'==*ptr))
+    while(*ptr && !ISSPACE(*ptr) && !(':'==*ptr))
       ptr++;
 
     if(ptr != start) {
       size_t len=ptr-start;
+      Curl_safefree(conn->allocptr.cookiehost);
       conn->allocptr.cookiehost = malloc(len+1);
       if(!conn->allocptr.cookiehost)
         return CURLE_OUT_OF_MEMORY;
       memcpy(conn->allocptr.cookiehost, start, len);
       conn->allocptr.cookiehost[len]=0;
     }
+#endif
 
     conn->allocptr.host = NULL;
   }
@@ -1410,8 +1816,8 @@ CURLcode Curl_http(struct connectdata *conn)
        uses the encoded host name! */
     if(conn->host.dispname != conn->host.name) {
       char *url = data->change.url;
-      char *iPtr = strstr(url, conn->host.dispname);
-      if(iPtr) {
+      ptr = strstr(url, conn->host.dispname);
+      if(ptr) {
         /* This is where the display name starts in the URL, now replace this
            part with the encoded name. TODO: This method of replacing the host
            name is rather crude as I believe there's a slight risk that the
@@ -1426,13 +1832,13 @@ CURLcode Curl_http(struct connectdata *conn)
         newurl = malloc(urllen + newlen - currlen + 1);
         if(newurl) {
           /* copy the part before the host name */
-          memcpy(newurl, url, iPtr - url);
+          memcpy(newurl, url, ptr - url);
           /* append the new host name instead of the old */
-          memcpy(newurl + (iPtr - url), conn->host.name, newlen);
+          memcpy(newurl + (ptr - url), conn->host.name, newlen);
           /* append the piece after the host name */
-          memcpy(newurl + newlen + (iPtr - url),
-                 iPtr + currlen, /* copy the trailing zero byte too */
-                 urllen - (iPtr-url) - currlen + 1);
+          memcpy(newurl + newlen + (ptr - url),
+                 ptr + currlen, /* copy the trailing zero byte too */
+                 urllen - (ptr-url) - currlen + 1);
           if(data->change.url_alloc)
             free(data->change.url);
           data->change.url = newurl;
@@ -1448,6 +1854,7 @@ CURLcode Curl_http(struct connectdata *conn)
     /* we must build the whole darned post sequence first, so that we have
        a size of the whole shebang before we start to send it */
      result = Curl_getFormData(&http->sendit, data->set.httppost,
+                               checkheaders(data, "Content-Type:"),
                                &http->postsize);
      if(CURLE_OK != result) {
        /* Curl_getFormData() doesn't use failf() */
@@ -1457,16 +1864,18 @@ CURLcode Curl_http(struct connectdata *conn)
   }
 
 
-  if(!checkheaders(data, "Pragma:"))
-    http->p_pragma = "Pragma: no-cache\r\n";
+  http->p_pragma =
+    (!checkheaders(data, "Pragma:") &&
+     (conn->bits.httpproxy && !conn->bits.tunnel_proxy) )?
+    "Pragma: no-cache\r\n":NULL;
 
   if(!checkheaders(data, "Accept:"))
     http->p_accept = "Accept: */*\r\n";
 
   if(( (HTTPREQ_POST == httpreq) ||
        (HTTPREQ_POST_FORM == httpreq) ||
        (HTTPREQ_PUT == httpreq) ) &&
-     conn->resume_from) {
+     data->reqdata.resume_from) {
     /**********************************************************************
      * Resuming upload in HTTP means that we PUT or POST and that we have
      * got a resume_from value set. The resume value has already created
@@ -1475,23 +1884,23 @@ CURLcode Curl_http(struct connectdata *conn)
      * file size before we continue this venture in the dark lands of HTTP.
      *********************************************************************/
 
-    if(conn->resume_from < 0 ) {
+    if(data->reqdata.resume_from < 0 ) {
       /*
        * This is meant to get the size of the present remote-file by itself.
        * We don't support this now. Bail out!
        */
-       conn->resume_from = 0;
+       data->reqdata.resume_from = 0;
     }
 
-    if(conn->resume_from) {
+    if(data->reqdata.resume_from) {
       /* do we still game? */
       curl_off_t passed=0;
 
       /* Now, let's read off the proper amount of bytes from the
          input. If we knew it was a proper file we could've just
          fseek()ed but we only have a stream here */
       do {
-        size_t readthisamountnow = (size_t)(conn->resume_from - passed);
+        size_t readthisamountnow = (size_t)(data->reqdata.resume_from - passed);
         size_t actuallyread;
 
         if(readthisamountnow > BUFSIZE)
@@ -1508,11 +1917,11 @@ CURLcode Curl_http(struct connectdata *conn)
                 passed);
           return CURLE_READ_ERROR;
         }
-      } while(passed != conn->resume_from); /* loop until done */
+      } while(passed != data->reqdata.resume_from); /* loop until done */
 
       /* now, decrease the size of the read */
       if(data->set.infilesize>0) {
-        data->set.infilesize -= conn->resume_from;
+        data->set.infilesize -= data->reqdata.resume_from;
 
         if(data->set.infilesize <= 0) {
           failf(data, "File already completely uploaded");
@@ -1522,7 +1931,7 @@ CURLcode Curl_http(struct connectdata *conn)
       /* we've passed, proceed as normal */
     }
   }
-  if(conn->bits.use_range) {
+  if(data->reqdata.use_range) {
     /*
      * A range is selected. We use different headers whether we're downloading
      * or uploading and we always let customized headers override our internal
@@ -1533,27 +1942,27 @@ CURLcode Curl_http(struct connectdata *conn)
       /* if a line like this was already allocated, free the previous one */
       if(conn->allocptr.rangeline)
         free(conn->allocptr.rangeline);
-      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", conn->range);
+      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", data->reqdata.range);
     }
     else if((httpreq != HTTPREQ_GET) &&
             !checkheaders(data, "Content-Range:")) {
 
-      if(conn->resume_from) {
+      if(data->reqdata.resume_from) {
         /* This is because "resume" was selected */
         curl_off_t total_expected_size=
-          conn->resume_from + data->set.infilesize;
+          data->reqdata.resume_from + data->set.infilesize;
         conn->allocptr.rangeline =
             aprintf("Content-Range: bytes %s%" FORMAT_OFF_T
                     "/%" FORMAT_OFF_T "\r\n",
-                    conn->range, total_expected_size-1,
+                    data->reqdata.range, total_expected_size-1,
                     total_expected_size);
       }
       else {
         /* Range was selected and then we just pass the incoming range and
            append total size */
         conn->allocptr.rangeline =
             aprintf("Content-Range: bytes %s/%" FORMAT_OFF_T "\r\n",
-                    conn->range, data->set.infilesize);
+                    data->reqdata.range, data->set.infilesize);
       }
     }
   }
@@ -1564,7 +1973,6 @@ CURLcode Curl_http(struct connectdata *conn)
       data->set.httpversion==CURL_HTTP_VERSION_1_0?"1.0":"1.1";
 
     send_buffer *req_buffer;
-    struct curl_slist *headers=data->set.headers;
     curl_off_t postsize; /* off_t type to be able to hold a large file size */
 
     /* initialize a dynamic send-buffer */
@@ -1587,6 +1995,7 @@ CURLcode Curl_http(struct connectdata *conn)
                   "%s" /* accept */
                   "%s" /* accept-encoding */
                   "%s" /* referer */
+                  "%s" /* Proxy-Connection */
                   "%s",/* transfer-encoding */
 
                 request,
@@ -1595,7 +2004,7 @@ CURLcode Curl_http(struct connectdata *conn)
                 conn->allocptr.proxyuserpwd?
                 conn->allocptr.proxyuserpwd:"",
                 conn->allocptr.userpwd?conn->allocptr.userpwd:"",
-                (conn->bits.use_range && conn->allocptr.rangeline)?
+                (data->reqdata.use_range && conn->allocptr.rangeline)?
                 conn->allocptr.rangeline:"",
                 (data->set.useragent && *data->set.useragent && conn->allocptr.uagent)?
                 conn->allocptr.uagent:"",
@@ -1605,12 +2014,17 @@ CURLcode Curl_http(struct connectdata *conn)
                 (data->set.encoding && *data->set.encoding && conn->allocptr.accept_encoding)?
                 conn->allocptr.accept_encoding:"",
                 (data->change.referer && conn->allocptr.ref)?conn->allocptr.ref:"" /* Referer: <data> */,
+                (conn->bits.httpproxy &&
+                 !conn->bits.tunnel_proxy &&
+                 !checkheaders(data, "Proxy-Connection:"))?
+                  "Proxy-Connection: Keep-Alive\r\n":"",
                 te
                 );
 
     if(result)
       return result;
 
+#if !defined(CURL_DISABLE_COOKIES)
     if(data->cookies || addcookies) {
       struct Cookie *co=NULL; /* no cookies from start */
       int count=0;
@@ -1619,7 +2033,7 @@ CURLcode Curl_http(struct connectdata *conn)
         Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
         co = Curl_cookie_getlist(data->cookies,
                                  conn->allocptr.cookiehost?
-                                 conn->allocptr.cookiehost:host, ppath,
+                                 conn->allocptr.cookiehost:host, data->reqdata.path,
                                  (bool)(conn->protocol&PROT_HTTPS?TRUE:FALSE));
         Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
       }
@@ -1660,9 +2074,10 @@ CURLcode Curl_http(struct connectdata *conn)
       if(result)
         return result;
     }
+#endif
 
     if(data->set.timecondition) {
-      struct tm *thistime;
+      struct tm *tm;
 
       /* Phil Karn (Fri, 13 Apr 2001) pointed out that the If-Modified-Since
        * header family should have their times set in GMT as RFC2616 defines:
@@ -1674,18 +2089,22 @@ CURLcode Curl_http(struct connectdata *conn)
 #ifdef HAVE_GMTIME_R
       /* thread-safe version */
       struct tm keeptime;
-      thistime = (struct tm *)gmtime_r(&data->set.timevalue, &keeptime);
+      tm = (struct tm *)gmtime_r(&data->set.timevalue, &keeptime);
 #else
-      thistime = gmtime(&data->set.timevalue);
+      tm = gmtime(&data->set.timevalue);
 #endif
 
-#ifdef HAVE_STRFTIME
       /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-      strftime(buf, BUFSIZE-1, "%a, %d %b %Y %H:%M:%S GMT", thistime);
-#else
-      /* TODO: Right, we *could* write a replacement here */
-      strcpy(buf, "no strftime() support");
-#endif
+      snprintf(buf, BUFSIZE-1,
+               "%s, %02d %s %4d %02d:%02d:%02d GMT",
+               Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
+               tm->tm_mday,
+               Curl_month[tm->tm_mon],
+               tm->tm_year + 1900,
+               tm->tm_hour,
+               tm->tm_min,
+               tm->tm_sec);
+
       switch(data->set.timecondition) {
       case CURL_TIMECOND_IFMODSINCE:
       default:
@@ -1705,25 +2124,9 @@ CURLcode Curl_http(struct connectdata *conn)
         return result;
     }
 
-    while(headers) {
-      ptr = strchr(headers->data, ':');
-      if(ptr) {
-        /* we require a colon for this to be a true header */
-
-        ptr++; /* pass the colon */
-        while(*ptr && isspace((int)*ptr))
-          ptr++;
-
-        if(*ptr) {
-          /* only send this if the contents was non-blank */
-
-          result = add_bufferf(req_buffer, "%s\r\n", headers->data);
-          if(result)
-            return result;
-        }
-      }
-      headers = headers->next;
-    }
+    result = add_custom_headers(conn, req_buffer);
+    if(result)
+      return result;
 
     http->postdata = NULL;  /* nothing to post at this point */
     Curl_pgrsSetUploadSize(data, 0); /* upload size is 0 atm */
@@ -1735,6 +2138,24 @@ CURLcode Curl_http(struct connectdata *conn)
     switch(httpreq) {
 
     case HTTPREQ_POST_FORM:
+      if(!http->sendit || conn->bits.authneg) {
+        /* nothing to post! */
+        result = add_bufferf(req_buffer, "Content-Length: 0\r\n\r\n");
+        if(result)
+          return result;
+
+        result = add_buffer_send(req_buffer, conn,
+                                 &data->info.request_size, 0, FIRSTSOCKET);
+        if(result)
+          failf(data, "Failed sending POST request");
+        else
+          /* setup variables for the upcoming transfer */
+          result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
+                                       &http->readbytecount,
+                                       -1, NULL);
+        break;
+      }
+
       if(Curl_FormInit(&http->form, http->sendit)) {
         failf(data, "Internal HTTP POST error!");
         return CURLE_HTTP_POST_ERROR;
@@ -1755,23 +2176,13 @@ CURLcode Curl_http(struct connectdata *conn)
           return result;
       }
 
-      if(!checkheaders(data, "Expect:")) {
-        /* if not disabled explicitly we add a Expect: 100-continue
-           to the headers which actually speeds up post operations (as
-           there is one packet coming back from the web server) */
-        result = add_bufferf(req_buffer,
-                             "Expect: 100-continue\r\n");
-        if(result)
-          return result;
-        data->set.expect100header = TRUE;
-      }
+      result = expect100(data, req_buffer);
+      if(result)
+        return result;
 
-      if(!checkheaders(data, "Content-Type:")) {
-        /* Get Content-Type: line from Curl_formpostheader.
+      {
 
-           The Content-Type header line also contains the MIME boundary
-           string etc why disabling this header is likely to not make things
-           work, but we support disabling it anyway.
+        /* Get Content-Type: line from Curl_formpostheader.
         */
         char *contentType;
         size_t linelength=0;
@@ -1781,6 +2192,7 @@ CURLcode Curl_http(struct connectdata *conn)
           failf(data, "Could not get Content-Type header line!");
           return CURLE_HTTP_POST_ERROR;
         }
+
         result = add_buffer(req_buffer, contentType, linelength);
         if(result)
           return result;
@@ -1796,72 +2208,82 @@ CURLcode Curl_http(struct connectdata *conn)
 
       /* fire away the whole request to the server */
       result = add_buffer_send(req_buffer, conn,
-                               &data->info.request_size);
+                               &data->info.request_size, 0, FIRSTSOCKET);
       if(result)
         failf(data, "Failed sending POST request");
       else
         /* setup variables for the upcoming transfer */
-        result = Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
-                               &http->readbytecount,
-                               FIRSTSOCKET,
-                               &http->writebytecount);
+        result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
+                                     &http->readbytecount,
+                                     FIRSTSOCKET,
+                                     &http->writebytecount);
+
       if(result) {
-        Curl_formclean(http->sendit); /* free that whole lot */
+        Curl_formclean(&http->sendit); /* free that whole lot */
         return result;
       }
+#ifdef CURL_DOES_CONVERSIONS
+/* time to convert the form data... */
+      result = Curl_formconvert(data, http->sendit);
+      if(result) {
+        Curl_formclean(&http->sendit); /* free that whole lot */
+        return result;
+      }
+#endif /* CURL_DOES_CONVERSIONS */
       break;
 
     case HTTPREQ_PUT: /* Let's PUT the data to the server! */
 
-      if((data->set.infilesize>0) && !conn->bits.upload_chunky) {
+      if(conn->bits.authneg)
+        postsize = 0;
+      else
+        postsize = data->set.infilesize;
+
+      if((postsize != -1) && !conn->bits.upload_chunky) {
         /* only add Content-Length if not uploading chunked */
         result = add_bufferf(req_buffer,
-                             "Content-Length: %" FORMAT_OFF_T "\r\n", /* size */
-                             data->set.infilesize );
+                             "Content-Length: %" FORMAT_OFF_T "\r\n",
+                             postsize );
         if(result)
           return result;
       }
 
-      if(!checkheaders(data, "Expect:")) {
-        /* if not disabled explicitly we add a Expect: 100-continue
-           to the headers which actually speeds up post operations (as
-           there is one packet coming back from the web server) */
-        result = add_bufferf(req_buffer,
-                             "Expect: 100-continue\r\n");
-        if(result)
-          return result;
-        data->set.expect100header = TRUE;
-      }
+      result = expect100(data, req_buffer);
+      if(result)
+        return result;
 
       result = add_buffer(req_buffer, "\r\n", 2); /* end of headers */
       if(result)
         return result;
 
       /* set the upload size to the progress meter */
-      Curl_pgrsSetUploadSize(data, data->set.infilesize);
+      Curl_pgrsSetUploadSize(data, postsize);
 
       /* this sends the buffer and frees all the buffer resources */
       result = add_buffer_send(req_buffer, conn,
-                               &data->info.request_size);
+                               &data->info.request_size, 0, FIRSTSOCKET);
       if(result)
-        failf(data, "Failed sending POST request");
+        failf(data, "Failed sending PUT request");
       else
         /* prepare for transfer */
-        result = Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
-                               &http->readbytecount,
-                               FIRSTSOCKET,
-                               &http->writebytecount);
+        result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
+                                     &http->readbytecount,
+                                     postsize?FIRSTSOCKET:-1,
+                                     postsize?&http->writebytecount:NULL);
       if(result)
         return result;
       break;
 
     case HTTPREQ_POST:
       /* this is the simple POST, using x-www-form-urlencoded style */
 
-      /* store the size of the postfields */
-      postsize = data->set.postfieldsize?
-        data->set.postfieldsize:
-        (data->set.postfields?(curl_off_t)strlen(data->set.postfields):0);
+      if(conn->bits.authneg)
+        postsize = 0;
+      else
+        /* figure out the size of the postfields */
+        postsize = (data->set.postfieldsize != -1)?
+          data->set.postfieldsize:
+          (data->set.postfields?(curl_off_t)strlen(data->set.postfields):0);
 
       if(!conn->bits.upload_chunky) {
         /* We only set Content-Length and allow a custom Content-Length if
@@ -1888,15 +2310,24 @@ CURLcode Curl_http(struct connectdata *conn)
 
       if(data->set.postfields) {
 
-        if((data->state.authhost.done || data->state.authproxy.done )
-           && (postsize < (100*1024))) {
-          /* If we're not done with the authentication phase, we don't expect
-             to actually send off any data yet. Hence, we delay the sending of
-             the body until we receive that friendly 100-continue response */
+        /* for really small posts we don't use Expect: headers at all, and for
+           the somewhat bigger ones we allow the app to disable it */
+        if(postsize > TINY_INITIAL_POST_SIZE) {
+          result = expect100(data, req_buffer);
+          if(result)
+            return result;
+        }
+        else
+          data->state.expect100header = FALSE;
 
-          /* The post data is less than 100K, then append it to the header.
-             This limit is no magic limit but only set to prevent really huge
-             POSTs to get the data duplicated with malloc() and family. */
+        if(!data->state.expect100header &&
+           (postsize < MAX_INITIAL_POST_SIZE))  {
+          /* if we don't use expect:-100  AND
+             postsize is less than MAX_INITIAL_POST_SIZE
+
+             then append the post data to the HTTP request header. This limit
+             is no magic limit but only set to prevent really huge POSTs to
+             get the data duplicated with malloc() and family. */
 
           result = add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
           if(result)
@@ -1907,6 +2338,7 @@ CURLcode Curl_http(struct connectdata *conn)
                already now to reduce the number if send() calls */
             result = add_buffer(req_buffer, data->set.postfields,
                                 (size_t)postsize);
+            included_body = postsize;
           }
           else {
             /* Append the POST data chunky-style */
@@ -1916,8 +2348,9 @@ CURLcode Curl_http(struct connectdata *conn)
                                   (size_t)postsize);
             if(CURLE_OK == result)
               result = add_buffer(req_buffer,
-                                  "\r\n0\r\n\r\n", 7); /* end of a chunked
-                                                          transfer stream */
+                                  "\x0d\x0a\x30\x0d\x0a\x0d\x0a", 7);
+                                  /* CR  LF   0  CR  LF  CR  LF */
+            included_body = postsize + 7;
           }
           if(result)
             return result;
@@ -1935,37 +2368,30 @@ CURLcode Curl_http(struct connectdata *conn)
           /* set the upload size to the progress meter */
           Curl_pgrsSetUploadSize(data, http->postsize);
 
-          if(!checkheaders(data, "Expect:")) {
-            /* if not disabled explicitly we add a Expect: 100-continue to the
-               headers which actually speeds up post operations (as there is
-               one packet coming back from the web server) */
-            add_bufferf(req_buffer,
-                        "Expect: 100-continue\r\n");
-            data->set.expect100header = TRUE;
-          }
-
           add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
         }
       }
       else {
         add_buffer(req_buffer, "\r\n", 2); /* end of headers! */
 
-        /* set the upload size to the progress meter */
-        Curl_pgrsSetUploadSize(data, data->set.infilesize);
+        if(data->set.postfieldsize) {
+          /* set the upload size to the progress meter */
+          Curl_pgrsSetUploadSize(data, postsize?postsize:-1);
 
-        /* set the pointer to mark that we will send the post body using
-           the read callback */
-        http->postdata = (char *)&http->postdata;
+          /* set the pointer to mark that we will send the post body using
+             the read callback */
+          http->postdata = (char *)&http->postdata;
+        }
       }
       /* issue the request */
-      result = add_buffer_send(req_buffer, conn,
-                               &data->info.request_size);
+      result = add_buffer_send(req_buffer, conn, &data->info.request_size,
+                               (size_t)included_body, FIRSTSOCKET);
 
       if(result)
         failf(data, "Failed sending HTTP POST request");
       else
         result =
-          Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
+          Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                         &http->readbytecount,
                         http->postdata?FIRSTSOCKET:-1,
                         http->postdata?&http->writebytecount:NULL);
@@ -1976,13 +2402,13 @@ CURLcode Curl_http(struct connectdata *conn)
 
       /* issue the request */
       result = add_buffer_send(req_buffer, conn,
-                               &data->info.request_size);
+                               &data->info.request_size, 0, FIRSTSOCKET);
 
       if(result)
         failf(data, "Failed sending HTTP request");
       else
         /* HTTP GET/HEAD download: */
-        result = Curl_Transfer(conn, FIRSTSOCKET, -1, TRUE,
+        result = Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                                &http->readbytecount,
                                http->postdata?FIRSTSOCKET:-1,
                                http->postdata?&http->writebytecount:NULL);