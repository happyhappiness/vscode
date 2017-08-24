@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -27,11 +27,15 @@
    http://davenport.sourceforge.net/ntlm.html
    http://www.innovation.ch/java/ntlm.html
 
+   Another implementation:
+   http://lxr.mozilla.org/mozilla/source/security/manager/ssl/src/nsNTLMAuthModule.cpp
+
 */
 
 #ifndef CURL_DISABLE_HTTP
-#ifdef USE_SSLEAY
-/* We need OpenSSL for the crypto lib to provide us with MD4 and DES */
+#ifdef USE_NTLM
+
+#define DEBUG_ME 0
 
 /* -- WIN32 approved -- */
 #include <stdio.h>
@@ -40,20 +44,33 @@
 #include <stdlib.h>
 #include <ctype.h>
 
+#ifdef HAVE_UNISTD_H
+#include <unistd.h>
+#endif
+
 #include "urldata.h"
+#include "easyif.h"  /* for Curl_convert_... prototypes */
 #include "sendf.h"
 #include "strequal.h"
 #include "base64.h"
 #include "http_ntlm.h"
 #include "url.h"
-#include "curl_memory.h"
+#include "memory.h"
+#include "ssluse.h"
 
 #define _MPRINTF_REPLACE /* use our functions only */
 #include <curl/mprintf.h>
 
+/* "NTLMSSP" signature is always in ASCII regardless of the platform */
+#define NTLMSSP_SIGNATURE "\x4e\x54\x4c\x4d\x53\x53\x50"
+
+#ifndef USE_WINDOWS_SSPI
+
 #include <openssl/des.h>
 #include <openssl/md4.h>
+#include <openssl/md5.h>
 #include <openssl/ssl.h>
+#include <openssl/rand.h>
 
 #if OPENSSL_VERSION_NUMBER < 0x00907001L
 #define DES_key_schedule des_key_schedule
@@ -71,12 +88,119 @@
 #define DESKEY(x) &x
 #endif
 
+#else
+
+#include <rpc.h>
+
+/* Handle of security.dll or secur32.dll, depending on Windows version */
+static HMODULE s_hSecDll = NULL;
+/* Pointer to SSPI dispatch table */
+static PSecurityFunctionTable s_pSecFn = NULL;
+
+#endif
+
 /* The last #include file should be: */
 #include "memdebug.h"
 
 /* Define this to make the type-3 message include the NT response message */
 #define USE_NTRESPONSES 1
 
+/* Define this to make the type-3 message include the NTLM2Session response
+   message, requires USE_NTRESPONSES. */
+#define USE_NTLM2SESSION 1
+
+#ifndef USE_WINDOWS_SSPI
+/* this function converts from the little endian format used in the incoming
+   package to whatever endian format we're using natively */
+static unsigned int readint_le(unsigned char *buf) /* must point to a
+                                                      4 bytes buffer*/
+{
+  return ((unsigned int)buf[0]) | ((unsigned int)buf[1] << 8) |
+    ((unsigned int)buf[2] << 16) | ((unsigned int)buf[3] << 24);
+}
+#endif
+
+#if DEBUG_ME
+# define DEBUG_OUT(x) x
+static void print_flags(FILE *handle, unsigned long flags)
+{
+  if(flags & NTLMFLAG_NEGOTIATE_UNICODE)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_UNICODE ");
+  if(flags & NTLMFLAG_NEGOTIATE_OEM)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_OEM ");
+  if(flags & NTLMFLAG_REQUEST_TARGET)
+    fprintf(handle, "NTLMFLAG_REQUEST_TARGET ");
+  if(flags & (1<<3))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_3 ");
+  if(flags & NTLMFLAG_NEGOTIATE_SIGN)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_SIGN ");
+  if(flags & NTLMFLAG_NEGOTIATE_SEAL)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_SEAL ");
+  if(flags & NTLMFLAG_NEGOTIATE_DATAGRAM_STYLE)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_DATAGRAM_STYLE ");
+  if(flags & NTLMFLAG_NEGOTIATE_LM_KEY)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_LM_KEY ");
+  if(flags & NTLMFLAG_NEGOTIATE_NETWARE)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_NETWARE ");
+  if(flags & NTLMFLAG_NEGOTIATE_NTLM_KEY)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_NTLM_KEY ");
+  if(flags & (1<<10))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_10 ");
+  if(flags & (1<<11))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_11 ");
+  if(flags & NTLMFLAG_NEGOTIATE_DOMAIN_SUPPLIED)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_DOMAIN_SUPPLIED ");
+  if(flags & NTLMFLAG_NEGOTIATE_WORKSTATION_SUPPLIED)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_WORKSTATION_SUPPLIED ");
+  if(flags & NTLMFLAG_NEGOTIATE_LOCAL_CALL)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_LOCAL_CALL ");
+  if(flags & NTLMFLAG_NEGOTIATE_ALWAYS_SIGN)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_ALWAYS_SIGN ");
+  if(flags & NTLMFLAG_TARGET_TYPE_DOMAIN)
+    fprintf(handle, "NTLMFLAG_TARGET_TYPE_DOMAIN ");
+  if(flags & NTLMFLAG_TARGET_TYPE_SERVER)
+    fprintf(handle, "NTLMFLAG_TARGET_TYPE_SERVER ");
+  if(flags & NTLMFLAG_TARGET_TYPE_SHARE)
+    fprintf(handle, "NTLMFLAG_TARGET_TYPE_SHARE ");
+  if(flags & NTLMFLAG_NEGOTIATE_NTLM2_KEY)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_NTLM2_KEY ");
+  if(flags & NTLMFLAG_REQUEST_INIT_RESPONSE)
+    fprintf(handle, "NTLMFLAG_REQUEST_INIT_RESPONSE ");
+  if(flags & NTLMFLAG_REQUEST_ACCEPT_RESPONSE)
+    fprintf(handle, "NTLMFLAG_REQUEST_ACCEPT_RESPONSE ");
+  if(flags & NTLMFLAG_REQUEST_NONNT_SESSION_KEY)
+    fprintf(handle, "NTLMFLAG_REQUEST_NONNT_SESSION_KEY ");
+  if(flags & NTLMFLAG_NEGOTIATE_TARGET_INFO)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_TARGET_INFO ");
+  if(flags & (1<<24))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_24 ");
+  if(flags & (1<<25))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_25 ");
+  if(flags & (1<<26))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_26 ");
+  if(flags & (1<<27))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_27 ");
+  if(flags & (1<<28))
+    fprintf(handle, "NTLMFLAG_UNKNOWN_28 ");
+  if(flags & NTLMFLAG_NEGOTIATE_128)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_128 ");
+  if(flags & NTLMFLAG_NEGOTIATE_KEY_EXCHANGE)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_KEY_EXCHANGE ");
+  if(flags & NTLMFLAG_NEGOTIATE_56)
+    fprintf(handle, "NTLMFLAG_NEGOTIATE_56 ");
+}
+
+static void print_hex(FILE *handle, const char *buf, size_t len)
+{
+  const char *p = buf;
+  fprintf(stderr, "0x");
+  while (len-- > 0)
+    fprintf(stderr, "%02.2x", (unsigned int)*p++);
+}
+#else
+# define DEBUG_OUT(x)
+#endif
+
 /*
   (*) = A "security buffer" is a triplet consisting of two shorts and one
   long:
@@ -95,18 +219,20 @@ CURLntlm Curl_input_ntlm(struct connectdata *conn,
 {
   /* point to the correct struct with this */
   struct ntlmdata *ntlm;
+#ifndef USE_WINDOWS_SSPI
+  static const char type2_marker[] = { 0x02, 0x00, 0x00, 0x00 };
+#endif
 
   ntlm = proxy?&conn->proxyntlm:&conn->ntlm;
 
   /* skip initial whitespaces */
-  while(*header && isspace((int)*header))
+  while(*header && ISSPACE(*header))
     header++;
 
   if(checkprefix("NTLM", header)) {
-    unsigned char buffer[256];
     header += strlen("NTLM");
 
-    while(*header && isspace((int)*header))
+    while(*header && ISSPACE(*header))
       header++;
 
     if(*header) {
@@ -123,17 +249,47 @@ CURLntlm Curl_input_ntlm(struct connectdata *conn,
          (40)    Target Information  (optional) security buffer(*)
          32 (48) start of data block
       */
-
-      size_t size = Curl_base64_decode(header, (char *)buffer);
+      size_t size;
+      unsigned char *buffer;
+      size = Curl_base64_decode(header, &buffer);
+      if(!buffer)
+        return CURLNTLM_BAD;
 
       ntlm->state = NTLMSTATE_TYPE2; /* we got a type-2 */
 
-      if(size >= 48)
-        /* the nonce of interest is index [24 .. 31], 8 bytes */
-        memcpy(ntlm->nonce, &buffer[24], 8);
+#ifdef USE_WINDOWS_SSPI
+      ntlm->type_2 = malloc(size+1);
+      if (ntlm->type_2 == NULL) {
+        free(buffer);
+        return CURLE_OUT_OF_MEMORY;
+      }
+      ntlm->n_type_2 = size;
+      memcpy(ntlm->type_2, buffer, size);
+#else
+      ntlm->flags = 0;
+
+      if((size < 32) ||
+         (memcmp(buffer, NTLMSSP_SIGNATURE, 8) != 0) ||
+         (memcmp(buffer+8, type2_marker, sizeof(type2_marker)) != 0)) {
+        /* This was not a good enough type-2 message */
+        free(buffer);
+        return CURLNTLM_BAD;
+      }
 
-      /* at index decimal 20, there's a 32bit NTLM flag field */
+      ntlm->flags = readint_le(&buffer[20]);
+      memcpy(ntlm->nonce, &buffer[24], 8);
 
+      DEBUG_OUT({
+        fprintf(stderr, "**** TYPE2 header flags=0x%08.8lx ", ntlm->flags);
+        print_flags(stderr, ntlm->flags);
+        fprintf(stderr, "\n                  nonce=");
+        print_hex(stderr, (char *)ntlm->nonce, 8);
+        fprintf(stderr, "\n****\n");
+        fprintf(stderr, "**** Header %s\n ", header);
+      });
+
+      free(buffer);
+#endif
     }
     else {
       if(ntlm->state >= NTLMSTATE_TYPE1)
@@ -145,6 +301,8 @@ CURLntlm Curl_input_ntlm(struct connectdata *conn,
   return CURLNTLM_FINE;
 }
 
+#ifndef USE_WINDOWS_SSPI
+
 /*
  * Turns a 56 bit key into the 64 bit, odd parity key and sets the key.  The
  * key schedule ks is also set.
@@ -155,13 +313,13 @@ static void setup_des_key(unsigned char *key_56,
   DES_cblock key;
 
   key[0] = key_56[0];
-  key[1] = ((key_56[0] << 7) & 0xFF) | (key_56[1] >> 1);
-  key[2] = ((key_56[1] << 6) & 0xFF) | (key_56[2] >> 2);
-  key[3] = ((key_56[2] << 5) & 0xFF) | (key_56[3] >> 3);
-  key[4] = ((key_56[3] << 4) & 0xFF) | (key_56[4] >> 4);
-  key[5] = ((key_56[4] << 3) & 0xFF) | (key_56[5] >> 5);
-  key[6] = ((key_56[5] << 2) & 0xFF) | (key_56[6] >> 6);
-  key[7] =  (key_56[6] << 1) & 0xFF;
+  key[1] = (unsigned char)(((key_56[0] << 7) & 0xFF) | (key_56[1] >> 1));
+  key[2] = (unsigned char)(((key_56[1] << 6) & 0xFF) | (key_56[2] >> 2));
+  key[3] = (unsigned char)(((key_56[2] << 5) & 0xFF) | (key_56[3] >> 3));
+  key[4] = (unsigned char)(((key_56[3] << 4) & 0xFF) | (key_56[4] >> 4));
+  key[5] = (unsigned char)(((key_56[4] << 3) & 0xFF) | (key_56[5] >> 5));
+  key[6] = (unsigned char)(((key_56[5] << 2) & 0xFF) | (key_56[6] >> 6));
+  key[7] = (unsigned char) ((key_56[6] << 1) & 0xFF);
 
   DES_set_odd_parity(&key);
   DES_set_key(&key, ks);
@@ -172,7 +330,7 @@ static void setup_des_key(unsigned char *key_56,
   * 8 byte plaintext is encrypted with each key and the resulting 24
   * bytes are stored in the results array.
   */
-static void calc_resp(unsigned char *keys,
+static void lm_resp(unsigned char *keys,
                       unsigned char *plaintext,
                       unsigned char *results)
 {
@@ -191,44 +349,44 @@ static void calc_resp(unsigned char *keys,
                   DESKEY(ks), DES_ENCRYPT);
 }
 
+
 /*
- * Set up lanmanager and nt hashed passwords
+ * Set up lanmanager hashed password
  */
-static void mkhash(char *password,
-                   unsigned char *nonce,  /* 8 bytes */
-                   unsigned char *lmresp  /* must fit 0x18 bytes */
-#ifdef USE_NTRESPONSES
-                   , unsigned char *ntresp  /* must fit 0x18 bytes */
-#endif
-  )
+static void mk_lm_hash(struct SessionHandle *data,
+                       char *password, 
+                       unsigned char *lmbuffer /* 21 bytes */)
 {
-  unsigned char lmbuffer[21];
-#ifdef USE_NTRESPONSES
-  unsigned char ntbuffer[21];
-#endif
-  unsigned char *pw;
+  unsigned char pw[14];
   static const unsigned char magic[] = {
-    0x4B, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25
+    0x4B, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25 /* i.e. KGS!@#$% */
   };
   unsigned int i;
   size_t len = strlen(password);
 
-  /* make it fit at least 14 bytes */
-  pw = malloc(len<7?14:len*2);
-  if(!pw)
-    return; /* this will lead to a badly generated package */
-
   if (len > 14)
     len = 14;
 
   for (i=0; i<len; i++)
-    pw[i] = toupper(password[i]);
+    pw[i] = (unsigned char)toupper(password[i]);
 
   for (; i<14; i++)
     pw[i] = 0;
 
+#ifdef CURL_DOES_CONVERSIONS
+  /*
+   * The LanManager hashed password needs to be created using the
+   * password in the network encoding not the host encoding.
+   */
+  if(data)
+    Curl_convert_to_network(data, (char *)pw, 14);
+#else
+  (void)data;
+#endif
+
   {
-    /* create LanManager hashed password */
+    /* Create LanManager hashed password. */
+
     DES_key_schedule ks;
 
     setup_des_key(pw, DESKEY(ks));
@@ -239,53 +397,108 @@ static void mkhash(char *password,
     DES_ecb_encrypt((DES_cblock *)magic, (DES_cblock *)(lmbuffer+8),
                     DESKEY(ks), DES_ENCRYPT);
 
-    memset(lmbuffer+16, 0, 5);
+    memset(lmbuffer + 16, 0, 21 - 16);
+  }
+  }
+
+#if USE_NTRESPONSES
+static void utf8_to_unicode_le(unsigned char *dest, const char *src,
+                               size_t srclen)
+{
+  size_t i;
+  for (i=0; i<srclen; i++) {
+    dest[2*i]   = (unsigned char)src[i];
+    dest[2*i+1] =   '\0';
   }
-  /* create LM responses */
-  calc_resp(lmbuffer, nonce, lmresp);
+}
 
-#ifdef USE_NTRESPONSES
-  {
-    /* create NT hashed password */
-    MD4_CTX MD4;
+/*
+ * Set up nt hashed passwords
+ */
+static void mk_nt_hash(struct SessionHandle *data,
+                       char *password,
+                       unsigned char *ntbuffer /* 21 bytes */)
+{
+  size_t len = strlen(password);
+  unsigned char *pw = malloc(len*2);
 
-    len = strlen(password);
+  utf8_to_unicode_le(pw, password, len);
 
-    for (i=0; i<len; i++) {
-      pw[2*i]   = password[i];
-      pw[2*i+1] = 0;
-    }
+#ifdef CURL_DOES_CONVERSIONS
+  /*
+   * The NT hashed password needs to be created using the
+   * password in the network encoding not the host encoding.
+   */
+  if(data)
+    Curl_convert_to_network(data, (char *)pw, len*2);
+#else
+  (void)data;
+#endif
+
+  {
+    /* Create NT hashed password. */
+    MD4_CTX MD4;
 
     MD4_Init(&MD4);
     MD4_Update(&MD4, pw, 2*len);
     MD4_Final(ntbuffer, &MD4);
 
-    memset(ntbuffer+16, 0, 8);
+    memset(ntbuffer + 16, 0, 21 - 16);
   }
 
-  calc_resp(ntbuffer, nonce, ntresp);
+  free(pw);
+}
 #endif
 
-  free(pw);
+
+#endif
+
+#ifdef USE_WINDOWS_SSPI
+
+static void
+ntlm_sspi_cleanup(struct ntlmdata *ntlm)
+{
+  if (ntlm->type_2) {
+    free(ntlm->type_2);
+    ntlm->type_2 = NULL;
+  }
+  if (ntlm->has_handles) {
+    s_pSecFn->DeleteSecurityContext(&ntlm->c_handle);
+    s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
+    ntlm->has_handles = 0;
+  }
+  if (ntlm->p_identity) {
+    if (ntlm->identity.User) free(ntlm->identity.User);
+    if (ntlm->identity.Password) free(ntlm->identity.Password);
+    if (ntlm->identity.Domain) free(ntlm->identity.Domain);
+    ntlm->p_identity = NULL;
+  }
 }
 
-#define SHORTPAIR(x) ((x) & 0xff), ((x) >> 8)
+#endif
+
+#define SHORTPAIR(x) ((x) & 0xff), (((x) >> 8) & 0xff)
 #define LONGQUARTET(x) ((x) & 0xff), (((x) >> 8)&0xff), \
-  (((x) >>16)&0xff), ((x)>>24)
+  (((x) >>16)&0xff), (((x)>>24) & 0xff)
+
+#define HOSTNAME_MAX 1024
 
 /* this is for creating ntlm header output */
 CURLcode Curl_output_ntlm(struct connectdata *conn,
                           bool proxy)
 {
   const char *domain=""; /* empty */
-  const char *host=""; /* empty */
-  int domlen=(int)strlen(domain);
-  int hostlen = (int)strlen(host);
-  int hostoff; /* host name offset */
-  int domoff;  /* domain name offset */
+  char host [HOSTNAME_MAX+ 1] = ""; /* empty */
+#ifndef USE_WINDOWS_SSPI
+  size_t domlen = strlen(domain);
+  size_t hostlen = strlen(host);
+  size_t hostoff; /* host name offset */
+  size_t domoff;  /* domain name offset */
+#endif
   size_t size;
   char *base64=NULL;
-  unsigned char ntlmbuf[256]; /* enough, unless the host/domain is very long */
+  unsigned char ntlmbuf[1024]; /* enough, unless the user+host+domain is very
+                                  long */
 
   /* point to the address of the pointer that holds the string to sent to the
      server, which is for a plain host or for a HTTP proxy */
@@ -324,11 +537,128 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
   if(!passwdp)
     passwdp=(char *)"";
 
+#ifdef USE_WINDOWS_SSPI
+  /* If security interface is not yet initialized try to do this */
+  if (s_hSecDll == NULL) {
+    /* Determine Windows version. Security functions are located in
+     * security.dll on WinNT 4.0 and in secur32.dll on Win9x. Win2K and XP
+     * contain both these DLLs (security.dll just forwards calls to
+     * secur32.dll)
+     */
+    OSVERSIONINFO osver;
+    osver.dwOSVersionInfoSize = sizeof(osver);
+    GetVersionEx(&osver);
+    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT
+      && osver.dwMajorVersion == 4)
+      s_hSecDll = LoadLibrary("security.dll");
+    else
+      s_hSecDll = LoadLibrary("secur32.dll");
+    if (s_hSecDll != NULL) {
+      INIT_SECURITY_INTERFACE pInitSecurityInterface;
+      pInitSecurityInterface =
+        (INIT_SECURITY_INTERFACE)GetProcAddress(s_hSecDll,
+                                                "InitSecurityInterfaceA");
+      if (pInitSecurityInterface != NULL)
+        s_pSecFn = pInitSecurityInterface();
+    }
+  }
+  if (s_pSecFn == NULL)
+    return CURLE_RECV_ERROR;
+#endif
+
   switch(ntlm->state) {
   case NTLMSTATE_TYPE1:
   default: /* for the weird cases we (re)start here */
-    hostoff = 32;
-    domoff = hostoff + hostlen;
+#ifdef USE_WINDOWS_SSPI
+  {
+    SecBuffer buf;
+    SecBufferDesc desc;
+    SECURITY_STATUS status;
+    ULONG attrs;
+    const char *user;
+    int domlen;
+    TimeStamp tsDummy; /* For Windows 9x compatibility of SPPI calls */
+
+    ntlm_sspi_cleanup(ntlm);
+
+    user = strchr(userp, '\\');
+    if (!user)
+      user = strchr(userp, '/');
+
+    if (user) {
+      domain = userp;
+      domlen = user - userp;
+      user++;
+    }
+    else {
+      user = userp;
+      domain = "";
+      domlen = 0;
+    }
+
+    if (user && *user) {
+      /* note: initialize all of this before doing the mallocs so that
+       * it can be cleaned up later without leaking memory.
+       */
+      ntlm->p_identity = &ntlm->identity;
+      memset(ntlm->p_identity, 0, sizeof(*ntlm->p_identity));
+      if ((ntlm->identity.User = (unsigned char *)strdup(user)) == NULL)
+        return CURLE_OUT_OF_MEMORY;
+      ntlm->identity.UserLength = strlen(user);
+      if ((ntlm->identity.Password = (unsigned char *)strdup(passwdp)) == NULL)
+        return CURLE_OUT_OF_MEMORY;
+      ntlm->identity.PasswordLength = strlen(passwdp);
+      if ((ntlm->identity.Domain = malloc(domlen+1)) == NULL)
+        return CURLE_OUT_OF_MEMORY;
+      strncpy((char *)ntlm->identity.Domain, domain, domlen);
+      ntlm->identity.Domain[domlen] = '\0';
+      ntlm->identity.DomainLength = domlen;
+      ntlm->identity.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
+    }
+    else {
+      ntlm->p_identity = NULL;
+    }
+
+    if (s_pSecFn->AcquireCredentialsHandle(
+          NULL, (char *)"NTLM", SECPKG_CRED_OUTBOUND, NULL, ntlm->p_identity,
+          NULL, NULL, &ntlm->handle, &tsDummy
+          ) != SEC_E_OK) {
+      return CURLE_OUT_OF_MEMORY;
+    }
+
+    desc.ulVersion = SECBUFFER_VERSION;
+    desc.cBuffers  = 1;
+    desc.pBuffers  = &buf;
+    buf.cbBuffer   = sizeof(ntlmbuf);
+    buf.BufferType = SECBUFFER_TOKEN;
+    buf.pvBuffer   = ntlmbuf;
+
+    status = s_pSecFn->InitializeSecurityContext(&ntlm->handle, NULL,
+                                                 (char *) host,
+                                                 ISC_REQ_CONFIDENTIALITY |
+                                                 ISC_REQ_REPLAY_DETECT |
+                                                 ISC_REQ_CONNECTION,
+                                                 0, SECURITY_NETWORK_DREP,
+                                                 NULL, 0,
+                                                 &ntlm->c_handle, &desc,
+                                                 &attrs, &tsDummy);
+
+    if (status == SEC_I_COMPLETE_AND_CONTINUE ||
+        status == SEC_I_CONTINUE_NEEDED) {
+      s_pSecFn->CompleteAuthToken(&ntlm->c_handle, &desc);
+    }
+    else if (status != SEC_E_OK) {
+      s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
+      return CURLE_RECV_ERROR;
+    }
+
+    ntlm->has_handles = 1;
+    size = buf.cbBuffer;
+  }
+#else
+    hostoff = 0;
+    domoff = hostoff + hostlen; /* This is 0: remember that host and domain
+                                   are empty */
 
     /* Create and send a type-1 message:
 
@@ -342,8 +672,12 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
     32    start of data block
 
     */
-
-    snprintf((char *)ntlmbuf, sizeof(ntlmbuf), "NTLMSSP%c"
+#if USE_NTLM2SESSION
+#define NTLM2FLAG NTLMFLAG_NEGOTIATE_NTLM2_KEY
+#else
+#define NTLM2FLAG 0
+#endif
+    snprintf((char *)ntlmbuf, sizeof(ntlmbuf), NTLMSSP_SIGNATURE "%c"
              "\x01%c%c%c" /* 32-bit type = 1 */
              "%c%c%c%c"   /* 32-bit NTLM flag field */
              "%c%c"  /* domain length */
@@ -360,9 +694,11 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
              0,0,0, /* part of type-1 long */
 
              LONGQUARTET(
-               NTLMFLAG_NEGOTIATE_OEM|      /*   2 */
-               NTLMFLAG_NEGOTIATE_NTLM_KEY  /* 200 */
-               /* equals 0x0202 */
+               NTLMFLAG_NEGOTIATE_OEM|
+               NTLMFLAG_REQUEST_TARGET|
+               NTLMFLAG_NEGOTIATE_NTLM_KEY|
+               NTLM2FLAG|
+               NTLMFLAG_NEGOTIATE_ALWAYS_SIGN
                ),
              SHORTPAIR(domlen),
              SHORTPAIR(domlen),
@@ -372,19 +708,42 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
              SHORTPAIR(hostlen),
              SHORTPAIR(hostoff),
              0,0,
-             host, domain);
+             host /* this is empty */, domain /* this is empty */);
 
     /* initial packet length */
     size = 32 + hostlen + domlen;
+#endif
 
-    /* now keeper of the base64 encoded package size */
-    size = Curl_base64_encode((char *)ntlmbuf, size, &base64);
+    DEBUG_OUT({
+      fprintf(stderr, "**** TYPE1 header flags=0x%02.2x%02.2x%02.2x%02.2x 0x%08.8x ",
+              LONGQUARTET(NTLMFLAG_NEGOTIATE_OEM|
+                          NTLMFLAG_REQUEST_TARGET|
+                          NTLMFLAG_NEGOTIATE_NTLM_KEY|
+                          NTLM2FLAG|
+                          NTLMFLAG_NEGOTIATE_ALWAYS_SIGN),
+              NTLMFLAG_NEGOTIATE_OEM|
+              NTLMFLAG_REQUEST_TARGET|
+              NTLMFLAG_NEGOTIATE_NTLM_KEY|
+              NTLM2FLAG|
+              NTLMFLAG_NEGOTIATE_ALWAYS_SIGN);
+      print_flags(stderr,
+                  NTLMFLAG_NEGOTIATE_OEM|
+                  NTLMFLAG_REQUEST_TARGET|
+                  NTLMFLAG_NEGOTIATE_NTLM_KEY|
+                  NTLM2FLAG|
+                  NTLMFLAG_NEGOTIATE_ALWAYS_SIGN);
+      fprintf(stderr, "\n****\n");
+    });
+
+    /* now size is the size of the base64 encoded package size */
+    size = Curl_base64_encode(NULL, (char *)ntlmbuf, size, &base64);
 
     if(size >0 ) {
       Curl_safefree(*allocuserpwd);
       *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                               proxy?"Proxy-":"",
                               base64);
+      DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));
       free(base64);
     }
     else
@@ -393,7 +752,7 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
     break;
 
   case NTLMSTATE_TYPE2:
-    /* We received the type-2 already, create a type-3 message:
+    /* We received the type-2 message already, create a type-3 message:
 
     Index   Description            Content
     0       NTLMSSP Signature      Null-terminated ASCII "NTLMSSP"
@@ -411,47 +770,151 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
     */
 
   {
+#ifdef USE_WINDOWS_SSPI
+    SecBuffer type_2, type_3;
+    SecBufferDesc type_2_desc, type_3_desc;
+    SECURITY_STATUS status;
+    ULONG attrs;
+    TimeStamp tsDummy; /* For Windows 9x compatibility of SPPI calls */
+
+    type_2_desc.ulVersion  = type_3_desc.ulVersion  = SECBUFFER_VERSION;
+    type_2_desc.cBuffers   = type_3_desc.cBuffers   = 1;
+    type_2_desc.pBuffers   = &type_2;
+    type_3_desc.pBuffers   = &type_3;
+
+    type_2.BufferType = SECBUFFER_TOKEN;
+    type_2.pvBuffer   = ntlm->type_2;
+    type_2.cbBuffer   = ntlm->n_type_2;
+    type_3.BufferType = SECBUFFER_TOKEN;
+    type_3.pvBuffer   = ntlmbuf;
+    type_3.cbBuffer   = sizeof(ntlmbuf);
+
+    status = s_pSecFn->InitializeSecurityContext(&ntlm->handle, &ntlm->c_handle,
+                                       (char *) host,
+                                       ISC_REQ_CONFIDENTIALITY |
+                                       ISC_REQ_REPLAY_DETECT |
+                                       ISC_REQ_CONNECTION,
+                                       0, SECURITY_NETWORK_DREP, &type_2_desc,
+                                       0, &ntlm->c_handle, &type_3_desc,
+                                       &attrs, &tsDummy);
+
+    if (status != SEC_E_OK)
+      return CURLE_RECV_ERROR;
+
+    size = type_3.cbBuffer;
+
+    ntlm_sspi_cleanup(ntlm);
+
+#else
     int lmrespoff;
+    unsigned char lmresp[24]; /* fixed-size */
+#if USE_NTRESPONSES
     int ntrespoff;
-    int useroff;
-    unsigned char lmresp[0x18]; /* fixed-size */
-#ifdef USE_NTRESPONSES
-    unsigned char ntresp[0x18]; /* fixed-size */
+    unsigned char ntresp[24]; /* fixed-size */
 #endif
+    size_t useroff;
     const char *user;
-    int userlen;
+    size_t userlen;
 
     user = strchr(userp, '\\');
     if(!user)
       user = strchr(userp, '/');
 
     if (user) {
       domain = userp;
-      domlen = (int)(user - domain);
+      domlen = (user - domain);
       user++;
     }
     else
       user = userp;
-    userlen = (int)strlen(user);
+    userlen = strlen(user);
+
+    if (gethostname(host, HOSTNAME_MAX)) {
+      infof(conn->data, "gethostname() failed, continuing without!");
+      hostlen = 0;
+    }
+    else {
+      /* If the workstation if configured with a full DNS name (i.e.
+       * workstation.somewhere.net) gethostname() returns the fully qualified
+       * name, which NTLM doesn't like.
+       */
+      char *dot = strchr(host, '.');
+      if (dot)
+        *dot = '\0';
+      hostlen = strlen(host);
+    }
+
+#if USE_NTLM2SESSION
+    /* We don't support NTLM2 if we don't have USE_NTRESPONSES */
+    if (ntlm->flags & NTLMFLAG_NEGOTIATE_NTLM2_KEY) {
+      unsigned char ntbuffer[0x18];
+      unsigned char tmp[0x18];
+      unsigned char md5sum[MD5_DIGEST_LENGTH];
+      MD5_CTX MD5;
+      unsigned char random[8];
+
+      /* Need to create 8 bytes random data */
+      Curl_ossl_seed(conn->data); /* Initiate the seed if not already done */
+      RAND_bytes(random,8);
+
+      /* 8 bytes random data as challenge in lmresp */
+      memcpy(lmresp,random,8);
+      /* Pad with zeros */
+      memset(lmresp+8,0,0x10);
+
+      /* Fill tmp with challenge(nonce?) + random */
+      memcpy(tmp,&ntlm->nonce[0],8);
+      memcpy(tmp+8,random,8);
+
+      MD5_Init(&MD5);
+      MD5_Update(&MD5, tmp, 16);
+      MD5_Final(md5sum, &MD5);
+      /* We shall only use the first 8 bytes of md5sum,
+         but the des code in lm_resp only encrypt the first 8 bytes */
+      mk_nt_hash(conn->data, passwdp, ntbuffer);
+      lm_resp(ntbuffer, md5sum, ntresp);
+
+      /* End of NTLM2 Session code */
+    }
+    else {
+#endif
 
-    mkhash(passwdp, &ntlm->nonce[0], lmresp
-#ifdef USE_NTRESPONSES
-           , ntresp
+#if USE_NTRESPONSES
+      unsigned char ntbuffer[0x18];
 #endif
-      );
+      unsigned char lmbuffer[0x18];
 
-    domoff = 64; /* always */
+#if USE_NTRESPONSES
+      mk_nt_hash(conn->data, passwdp, ntbuffer);
+      lm_resp(ntbuffer, &ntlm->nonce[0], ntresp);
+#endif
+
+      mk_lm_hash(conn->data, passwdp, lmbuffer);
+      lm_resp(lmbuffer, &ntlm->nonce[0], lmresp);
+      /* A safer but less compatible alternative is:
+       *   lm_resp(ntbuffer, &ntlm->nonce[0], lmresp);
+       * See http://davenport.sourceforge.net/ntlm.html#ntlmVersion2 */
+#if USE_NTLM2SESSION
+    }
+#endif
+
+    lmrespoff = 64; /* size of the message header */
+#if USE_NTRESPONSES
+    ntrespoff = lmrespoff + 0x18;
+    domoff = ntrespoff + 0x18;
+#else
+    domoff = lmrespoff + 0x18;
+#endif
     useroff = domoff + domlen;
     hostoff = useroff + userlen;
-    lmrespoff = hostoff + hostlen;
-    ntrespoff = lmrespoff + 0x18;
 
     /* Create the big type-3 message binary blob */
     size = snprintf((char *)ntlmbuf, sizeof(ntlmbuf),
-                    "NTLMSSP%c"
+                    NTLMSSP_SIGNATURE "%c"
                     "\x03%c%c%c" /* type-3, 32 bits */
 
-                    "%c%c%c%c" /* LanManager length + allocated space */
+                    "%c%c" /* LanManager length */
+                    "%c%c" /* LanManager allocated space */
                     "%c%c" /* LanManager offset */
                     "%c%c" /* 2 zeroes */
 
@@ -473,14 +936,15 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
                     "%c%c"  /* host length */
                     "%c%c"  /* host allocated space */
                     "%c%c"  /* host offset */
-                    "%c%c%c%c%c%c"  /* 6 zeroes */
-
-                    "\xff\xff"  /* message length */
                     "%c%c"  /* 2 zeroes */
 
-                    "\x01\x82" /* flags */
+                    "%c%c"  /* session key length (unknown purpose) */
+                    "%c%c"  /* session key allocated space (unknown purpose) */
+                    "%c%c"  /* session key offset (unknown purpose) */
                     "%c%c"  /* 2 zeroes */
 
+                    "%c%c%c%c" /* flags */
+
                     /* domain string */
                     /* user string */
                     /* host string */
@@ -495,16 +959,17 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
                     SHORTPAIR(lmrespoff),
                     0x0, 0x0,
 
-#ifdef USE_NTRESPONSES
+#if USE_NTRESPONSES
                     SHORTPAIR(0x18),  /* NT-response length, twice */
                     SHORTPAIR(0x18),
+                    SHORTPAIR(ntrespoff),
+                    0x0, 0x0,
 #else
                     0x0, 0x0,
                     0x0, 0x0,
-#endif
-                    SHORTPAIR(ntrespoff),
                     0x0, 0x0,
-
+                    0x0, 0x0,
+#endif
                     SHORTPAIR(domlen),
                     SHORTPAIR(domlen),
                     SHORTPAIR(domoff),
@@ -518,46 +983,89 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
                     SHORTPAIR(hostlen),
                     SHORTPAIR(hostlen),
                     SHORTPAIR(hostoff),
-                    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
+                    0x0, 0x0,
 
                     0x0, 0x0,
+                    0x0, 0x0,
+                    0x0, 0x0,
+                    0x0, 0x0,
+
+                    LONGQUARTET(ntlm->flags));
+    DEBUG_OUT(assert(size==64));
+
+    DEBUG_OUT(assert(size == lmrespoff));
+    /* We append the binary hashes */
+    if(size < (sizeof(ntlmbuf) - 0x18)) {
+      memcpy(&ntlmbuf[size], lmresp, 0x18);
+      size += 0x18;
+    }
+
+    DEBUG_OUT({
+        fprintf(stderr, "**** TYPE3 header lmresp=");
+        print_hex(stderr, (char *)&ntlmbuf[lmrespoff], 0x18);
+    });
+
+#if USE_NTRESPONSES
+    if(size < (sizeof(ntlmbuf) - 0x18)) {
+      DEBUG_OUT(assert(size == ntrespoff));
+      memcpy(&ntlmbuf[size], ntresp, 0x18);
+      size += 0x18;
+    }
+
+    DEBUG_OUT({
+        fprintf(stderr, "\n                  ntresp=");
+        print_hex(stderr, (char *)&ntlmbuf[ntrespoff], 0x18);
+    });
+
+#endif
+
+    DEBUG_OUT({
+        fprintf(stderr, "\n                  flags=0x%02.2x%02.2x%02.2x%02.2x 0x%08.8x ",
+                LONGQUARTET(ntlm->flags), ntlm->flags);
+        print_flags(stderr, ntlm->flags);
+        fprintf(stderr, "\n****\n");
+    });
 
-                    0x0, 0x0);
 
-    /* size is now 64 */
-    size=64;
-    ntlmbuf[62]=ntlmbuf[63]=0;
+    /* Make sure that the domain, user and host strings fit in the target
+       buffer before we copy them there. */
+    if(size + userlen + domlen + hostlen >= sizeof(ntlmbuf)) {
+      failf(conn->data, "user + domain + host name too big");
+      return CURLE_OUT_OF_MEMORY;
+    }
 
+    curlassert(size == domoff);
     memcpy(&ntlmbuf[size], domain, domlen);
     size += domlen;
 
+    curlassert(size == useroff);
     memcpy(&ntlmbuf[size], user, userlen);
     size += userlen;
 
-    /* we append the binary hashes to the end of the blob */
-    if(size < ((int)sizeof(ntlmbuf) - 0x18)) {
-      memcpy(&ntlmbuf[size], lmresp, 0x18);
-      size += 0x18;
-    }
+    curlassert(size == hostoff);
+    memcpy(&ntlmbuf[size], host, hostlen);
+    size += hostlen;
 
-#ifdef USE_NTRESPONSES
-    if(size < ((int)sizeof(ntlmbuf) - 0x18)) {
-      memcpy(&ntlmbuf[size], ntresp, 0x18);
-      size += 0x18;
+#ifdef CURL_DOES_CONVERSIONS
+    /* convert domain, user, and host to ASCII but leave the rest as-is */
+    if(CURLE_OK != Curl_convert_to_network(conn->data, 
+                                           (char *)&ntlmbuf[domoff],
+                                           size-domoff)) {
+      return CURLE_CONV_FAILED;
     }
-#endif
+#endif /* CURL_DOES_CONVERSIONS */
 
-    ntlmbuf[56] = (unsigned char)(size & 0xff);
-    ntlmbuf[57] = (unsigned char)(size >> 8);
+#endif
 
     /* convert the binary blob into base64 */
-    size = Curl_base64_encode((char *)ntlmbuf, size, &base64);
+    size = Curl_base64_encode(NULL, (char *)ntlmbuf, size, &base64);
 
     if(size >0 ) {
       Curl_safefree(*allocuserpwd);
       *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                               proxy?"Proxy-":"",
                               base64);
+      DEBUG_OUT(fprintf(stderr, "**** %s\n ", *allocuserpwd));
       free(base64);
     }
     else
@@ -581,5 +1089,23 @@ CURLcode Curl_output_ntlm(struct connectdata *conn,
 
   return CURLE_OK;
 }
-#endif /* USE_SSLEAY */
+
+
+void
+Curl_ntlm_cleanup(struct connectdata *conn)
+{
+#ifdef USE_WINDOWS_SSPI
+  ntlm_sspi_cleanup(&conn->ntlm);
+  ntlm_sspi_cleanup(&conn->proxyntlm);
+  if (s_hSecDll != NULL) {
+    FreeLibrary(s_hSecDll);
+    s_hSecDll = NULL;
+    s_pSecFn = NULL;
+  }
+#else
+  (void)conn;
+#endif
+}
+
+#endif /* USE_NTLM */
 #endif /* !CURL_DISABLE_HTTP */