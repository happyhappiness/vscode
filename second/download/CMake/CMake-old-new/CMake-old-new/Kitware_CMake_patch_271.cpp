@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -22,7 +22,7 @@
 
 #include "curl_setup.h"
 
-#ifdef USE_NTLM
+#if defined(USE_NTLM) && !defined(USE_WINDOWS_SSPI)
 
 /*
  * NTLM details:
@@ -41,21 +41,21 @@
 #include "curl_gethostname.h"
 #include "curl_multibyte.h"
 #include "warnless.h"
-#include "curl_memory.h"
-
-#ifdef USE_WINDOWS_SSPI
-#  include "curl_sspi.h"
-#endif
 
 #include "vtls/vtls.h"
 
+#ifdef USE_NSS
+#include "vtls/nssg.h" /* for Curl_nss_force_init() */
+#endif
+
 #define BUILDING_CURL_NTLM_MSGS_C
 #include "curl_ntlm_msgs.h"
+#include "curl_sasl.h"
+#include "curl_endian.h"
+#include "curl_printf.h"
 
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 /* "NTLMSSP" signature is always in ASCII regardless of the platform */
@@ -147,81 +147,53 @@ static void ntlm_print_hex(FILE *handle, const char *buf, size_t len)
 # define DEBUG_OUT(x) Curl_nop_stmt
 #endif
 
-#ifndef USE_WINDOWS_SSPI
-/*
- * This function converts from the little endian format used in the
- * incoming package to whatever endian format we're using natively.
- * Argument is a pointer to a 4 byte buffer.
- */
-static unsigned int readint_le(unsigned char *buf)
-{
-  return ((unsigned int)buf[0]) | ((unsigned int)buf[1] << 8) |
-    ((unsigned int)buf[2] << 16) | ((unsigned int)buf[3] << 24);
-}
-
-/*
- * This function converts from the little endian format used in the incoming
- * package to whatever endian format we're using natively. Argument is a
- * pointer to a 2 byte buffer.
- */
-static unsigned int readshort_le(unsigned char *buf)
-{
-  return ((unsigned int)buf[0]) | ((unsigned int)buf[1] << 8);
-}
-
 /*
- * Curl_ntlm_decode_type2_target()
+ * ntlm_decode_type2_target()
  *
  * This is used to decode the "target info" in the ntlm type-2 message
  * received.
  *
  * Parameters:
  *
- * data      [in]    - Pointer to the session handle
- * buffer    [in]    - The decoded base64 ntlm header of Type 2
- * size      [in]    - The input buffer size, atleast 32 bytes
- * ntlm      [in]    - Pointer to ntlm data struct being used and modified.
+ * data      [in]     - The session handle.
+ * buffer    [in]     - The decoded type-2 message.
+ * size      [in]     - The input buffer size, at least 32 bytes.
+ * ntlm      [in/out] - The ntlm data struct being used and modified.
  *
  * Returns CURLE_OK on success.
  */
-CURLcode Curl_ntlm_decode_type2_target(struct SessionHandle *data,
-                                       unsigned char *buffer,
-                                       size_t size,
-                                       struct ntlmdata *ntlm)
+static CURLcode ntlm_decode_type2_target(struct SessionHandle *data,
+                                         unsigned char *buffer,
+                                         size_t size,
+                                         struct ntlmdata *ntlm)
 {
-  unsigned int target_info_len = 0;
+  unsigned short target_info_len = 0;
   unsigned int target_info_offset = 0;
 
-  Curl_safefree(ntlm->target_info);
-  ntlm->target_info_len = 0;
-
   if(size >= 48) {
-    target_info_len = readshort_le(&buffer[40]);
-    target_info_offset = readint_le(&buffer[44]);
+    target_info_len = Curl_read16_le(&buffer[40]);
+    target_info_offset = Curl_read32_le(&buffer[44]);
     if(target_info_len > 0) {
       if(((target_info_offset + target_info_len) > size) ||
          (target_info_offset < 48)) {
         infof(data, "NTLM handshake failure (bad type-2 message). "
                     "Target Info Offset Len is set incorrect by the peer\n");
-        return CURLE_REMOTE_ACCESS_DENIED;
+        return CURLE_BAD_CONTENT_ENCODING;
       }
 
       ntlm->target_info = malloc(target_info_len);
       if(!ntlm->target_info)
         return CURLE_OUT_OF_MEMORY;
 
       memcpy(ntlm->target_info, &buffer[target_info_offset], target_info_len);
-      ntlm->target_info_len = target_info_len;
-
     }
-
   }
 
+  ntlm->target_info_len = target_info_len;
+
   return CURLE_OK;
 }
 
-#endif
-
 /*
   NTLM message structure notes:
 
@@ -239,29 +211,26 @@ CURLcode Curl_ntlm_decode_type2_target(struct SessionHandle *data,
 */
 
 /*
- * Curl_ntlm_decode_type2_message()
+ * Curl_sasl_decode_ntlm_type2_message()
  *
- * This is used to decode a ntlm type-2 message received from a HTTP or SASL
- * based (such as SMTP, POP3 or IMAP) server. The message is first decoded
- * from a base64 string into a raw ntlm message and checked for validity
- * before the appropriate data for creating a type-3 message is written to
- * the given ntlm data structure.
+ * This is used to decode an already encoded NTLM type-2 message. The message
+ * is first decoded from a base64 string into a raw NTLM message and checked
+ * for validity before the appropriate data for creating a type-3 message is
+ * written to the given NTLM data structure.
  *
  * Parameters:
  *
- * data    [in]     - Pointer to session handle.
- * header  [in]     - Pointer to the input buffer.
- * ntlm    [in]     - Pointer to ntlm data struct being used and modified.
+ * data     [in]     - The session handle.
+ * type2msg [in]     - The base64 encoded type-2 message.
+ * ntlm     [in/out] - The ntlm data struct being used and modified.
  *
  * Returns CURLE_OK on success.
  */
-CURLcode Curl_ntlm_decode_type2_message(struct SessionHandle *data,
-                                        const char *header,
-                                        struct ntlmdata *ntlm)
+CURLcode Curl_sasl_decode_ntlm_type2_message(struct SessionHandle *data,
+                                             const char *type2msg,
+                                             struct ntlmdata *ntlm)
 {
-#ifndef USE_WINDOWS_SSPI
   static const char type2_marker[] = { 0x02, 0x00, 0x00, 0x00 };
-#endif
 
   /* NTLM type-2 message structure:
 
@@ -279,52 +248,52 @@ CURLcode Curl_ntlm_decode_type2_message(struct SessionHandle *data,
                                         (*) -> Optional
   */
 
-  size_t size = 0;
-  unsigned char *buffer = NULL;
-  CURLcode error;
-
-#if defined(CURL_DISABLE_VERBOSE_STRINGS) || defined(USE_WINDOWS_SSPI)
+  CURLcode result = CURLE_OK;
+  unsigned char *type2 = NULL;
+  size_t type2_len = 0;
+
+#if defined(USE_NSS)
+  /* Make sure the crypto backend is initialized */
+  result = Curl_nss_force_init(data);
+  if(result)
+    return result;
+#elif defined(CURL_DISABLE_VERBOSE_STRINGS)
   (void)data;
 #endif
 
-  error = Curl_base64_decode(header, &buffer, &size);
-  if(error)
-    return error;
-
-  if(!buffer) {
-    infof(data, "NTLM handshake failure (unhandled condition)\n");
-    return CURLE_REMOTE_ACCESS_DENIED;
+  /* Decode the base-64 encoded type-2 message */
+  if(strlen(type2msg) && *type2msg != '=') {
+    result = Curl_base64_decode(type2msg, &type2, &type2_len);
+    if(result)
+      return result;
   }
 
-#ifdef USE_WINDOWS_SSPI
-  ntlm->type_2 = malloc(size + 1);
-  if(ntlm->type_2 == NULL) {
-    free(buffer);
-    return CURLE_OUT_OF_MEMORY;
+  /* Ensure we have a valid type-2 message */
+  if(!type2) {
+    infof(data, "NTLM handshake failure (empty type-2 message)\n");
+    return CURLE_BAD_CONTENT_ENCODING;
   }
-  ntlm->n_type_2 = curlx_uztoul(size);
-  memcpy(ntlm->type_2, buffer, size);
-#else
+
   ntlm->flags = 0;
 
-  if((size < 32) ||
-     (memcmp(buffer, NTLMSSP_SIGNATURE, 8) != 0) ||
-     (memcmp(buffer + 8, type2_marker, sizeof(type2_marker)) != 0)) {
+  if((type2_len < 32) ||
+     (memcmp(type2, NTLMSSP_SIGNATURE, 8) != 0) ||
+     (memcmp(type2 + 8, type2_marker, sizeof(type2_marker)) != 0)) {
     /* This was not a good enough type-2 message */
-    free(buffer);
+    free(type2);
     infof(data, "NTLM handshake failure (bad type-2 message)\n");
-    return CURLE_REMOTE_ACCESS_DENIED;
+    return CURLE_BAD_CONTENT_ENCODING;
   }
 
-  ntlm->flags = readint_le(&buffer[20]);
-  memcpy(ntlm->nonce, &buffer[24], 8);
+  ntlm->flags = Curl_read32_le(&type2[20]);
+  memcpy(ntlm->nonce, &type2[24], 8);
 
   if(ntlm->flags & NTLMFLAG_NEGOTIATE_TARGET_INFO) {
-    error = Curl_ntlm_decode_type2_target(data, buffer, size, ntlm);
-    if(error) {
-      free(buffer);
+    result = ntlm_decode_type2_target(data, type2, type2_len, ntlm);
+    if(result) {
+      free(type2);
       infof(data, "NTLM handshake failure (bad type-2 message)\n");
-      return error;
+      return result;
     }
   }
 
@@ -336,32 +305,12 @@ CURLcode Curl_ntlm_decode_type2_message(struct SessionHandle *data,
     fprintf(stderr, "\n****\n");
     fprintf(stderr, "**** Header %s\n ", header);
   });
-#endif
-  free(buffer);
-
-  return CURLE_OK;
-}
 
-#ifdef USE_WINDOWS_SSPI
-void Curl_ntlm_sspi_cleanup(struct ntlmdata *ntlm)
-{
-  Curl_safefree(ntlm->type_2);
+  free(type2);
 
-  if(ntlm->has_handles) {
-    s_pSecFn->DeleteSecurityContext(&ntlm->c_handle);
-    s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
-    ntlm->has_handles = 0;
-  }
-
-  ntlm->max_token_length = 0;
-  Curl_safefree(ntlm->output_token);
-
-  Curl_sspi_free_identity(ntlm->p_identity);
-  ntlm->p_identity = NULL;
+  return result;
 }
-#endif
 
-#ifndef USE_WINDOWS_SSPI
 /* copy the source to the destination and fill in zeroes in every
    other destination byte! */
 static void unicodecpy(unsigned char *dest, const char *src, size_t length)
@@ -372,14 +321,12 @@ static void unicodecpy(unsigned char *dest, const char *src, size_t length)
     dest[2 * i + 1] = '\0';
   }
 }
-#endif
 
 /*
- * Curl_ntlm_create_type1_message()
+ * Curl_sasl_create_ntlm_type1_message()
  *
  * This is used to generate an already encoded NTLM type-1 message ready for
- * sending to the recipient, be it a HTTP or SASL based (such as SMTP, POP3
- * or IMAP) server, using the appropriate compile time crypo API.
+ * sending to the recipient using the appropriate compile time crypto API.
  *
  * Parameters:
  *
@@ -392,11 +339,10 @@ static void unicodecpy(unsigned char *dest, const char *src, size_t length)
  *
  * Returns CURLE_OK on success.
  */
-CURLcode Curl_ntlm_create_type1_message(const char *userp,
-                                        const char *passwdp,
-                                        struct ntlmdata *ntlm,
-                                        char **outptr,
-                                        size_t *outlen)
+CURLcode Curl_sasl_create_ntlm_type1_message(const char *userp,
+                                             const char *passwdp,
+                                             struct ntlmdata *ntlm,
+                                             char **outptr, size_t *outlen)
 {
   /* NTLM type-1 message structure:
 
@@ -414,89 +360,6 @@ CURLcode Curl_ntlm_create_type1_message(const char *userp,
 
   size_t size;
 
-#ifdef USE_WINDOWS_SSPI
-
-  PSecPkgInfo SecurityPackage;
-  SecBuffer type_1_buf;
-  SecBufferDesc type_1_desc;
-  SECURITY_STATUS status;
-  unsigned long attrs;
-  TimeStamp tsDummy; /* For Windows 9x compatibility of SSPI calls */
-
-  Curl_ntlm_sspi_cleanup(ntlm);
-
-  /* Query the security package for NTLM */
-  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT("NTLM"),
-                                              &SecurityPackage);
-  if(status != SEC_E_OK)
-    return CURLE_NOT_BUILT_IN;
-
-  ntlm->max_token_length = SecurityPackage->cbMaxToken;
-
-  /* Release the package buffer as it is not required anymore */
-  s_pSecFn->FreeContextBuffer(SecurityPackage);
-
-  /* Allocate our output buffer */
-  ntlm->output_token = malloc(ntlm->max_token_length);
-  if(!ntlm->output_token)
-    return CURLE_OUT_OF_MEMORY;
-
-  if(userp && *userp) {
-    CURLcode result;
-
-    /* Populate our identity structure */
-    result = Curl_create_sspi_identity(userp, passwdp, &ntlm->identity);
-    if(result)
-      return result;
-
-    /* Allow proper cleanup of the identity structure */
-    ntlm->p_identity = &ntlm->identity;
-  }
-  else
-    /* Use the current Windows user */
-    ntlm->p_identity = NULL;
-
-  /* Acquire our credientials handle */
-  status = s_pSecFn->AcquireCredentialsHandle(NULL,
-                                              (TCHAR *) TEXT("NTLM"),
-                                              SECPKG_CRED_OUTBOUND, NULL,
-                                              ntlm->p_identity, NULL, NULL,
-                                              &ntlm->handle, &tsDummy);
-  if(status != SEC_E_OK)
-    return CURLE_OUT_OF_MEMORY;
-
-  /* Setup the type-1 "output" security buffer */
-  type_1_desc.ulVersion = SECBUFFER_VERSION;
-  type_1_desc.cBuffers  = 1;
-  type_1_desc.pBuffers  = &type_1_buf;
-  type_1_buf.BufferType = SECBUFFER_TOKEN;
-  type_1_buf.pvBuffer   = ntlm->output_token;
-  type_1_buf.cbBuffer   = curlx_uztoul(ntlm->max_token_length);
-
-  /* Generate our type-1 message */
-  status = s_pSecFn->InitializeSecurityContext(&ntlm->handle, NULL,
-                                               (TCHAR *) TEXT(""),
-                                               ISC_REQ_CONFIDENTIALITY |
-                                               ISC_REQ_REPLAY_DETECT |
-                                               ISC_REQ_CONNECTION,
-                                               0, SECURITY_NETWORK_DREP,
-                                               NULL, 0,
-                                               &ntlm->c_handle, &type_1_desc,
-                                               &attrs, &tsDummy);
-
-  if(status == SEC_I_COMPLETE_AND_CONTINUE ||
-     status == SEC_I_CONTINUE_NEEDED)
-    s_pSecFn->CompleteAuthToken(&ntlm->c_handle, &type_1_desc);
-  else if(status != SEC_E_OK) {
-    s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
-    return CURLE_RECV_ERROR;
-  }
-
-  ntlm->has_handles = 1;
-  size = type_1_buf.cbBuffer;
-
-#else
-
   unsigned char ntlmbuf[NTLM_BUFSIZE];
   const char *host = "";              /* empty */
   const char *domain = "";            /* empty */
@@ -507,9 +370,11 @@ CURLcode Curl_ntlm_create_type1_message(const char *userp,
                                          domain are empty */
   (void)userp;
   (void)passwdp;
-  (void)ntlm;
 
-#if USE_NTLM2SESSION
+  /* Clean up any former leftovers and initialise to defaults */
+  Curl_sasl_ntlm_cleanup(ntlm);
+
+#if USE_NTRESPONSES && USE_NTLM2SESSION
 #define NTLM2FLAG NTLMFLAG_NEGOTIATE_NTLM2_KEY
 #else
 #define NTLM2FLAG 0
@@ -550,8 +415,6 @@ CURLcode Curl_ntlm_create_type1_message(const char *userp,
   /* Initial packet length */
   size = 32 + hostlen + domlen;
 
-#endif
-
   DEBUG_OUT({
     fprintf(stderr, "* TYPE1 header flags=0x%02.2x%02.2x%02.2x%02.2x "
             "0x%08.8x ",
@@ -575,20 +438,14 @@ CURLcode Curl_ntlm_create_type1_message(const char *userp,
   });
 
   /* Return with binary blob encoded into base64 */
-#ifdef USE_WINDOWS_SSPI
-  return Curl_base64_encode(NULL, (char *)ntlm->output_token, size,
-                            outptr, outlen);
-#else
   return Curl_base64_encode(NULL, (char *)ntlmbuf, size, outptr, outlen);
-#endif
 }
 
 /*
- * Curl_ntlm_create_type3_message()
+ * Curl_sasl_create_ntlm_type3_message()
  *
  * This is used to generate an already encoded NTLM type-3 message ready for
- * sending to the recipient, be it a HTTP or SASL based (such as SMTP, POP3
- * or IMAP) server, using the appropriate compile time crypo API.
+ * sending to the recipient using the appropriate compile time crypto API.
  *
  * Parameters:
  *
@@ -602,12 +459,12 @@ CURLcode Curl_ntlm_create_type1_message(const char *userp,
  *
  * Returns CURLE_OK on success.
  */
-CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
-                                        const char *userp,
-                                        const char *passwdp,
-                                        struct ntlmdata *ntlm,
-                                        char **outptr,
-                                        size_t *outlen)
+CURLcode Curl_sasl_create_ntlm_type3_message(struct SessionHandle *data,
+                                             const char *userp,
+                                             const char *passwdp,
+                                             struct ntlmdata *ntlm,
+                                             char **outptr, size_t *outlen)
+
 {
   /* NTLM type-3 message structure:
 
@@ -627,65 +484,8 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
                                           (*) -> Optional
   */
 
-  size_t size;
-
-#ifdef USE_WINDOWS_SSPI
   CURLcode result = CURLE_OK;
-  SecBuffer type_2_buf;
-  SecBuffer type_3_buf;
-  SecBufferDesc type_2_desc;
-  SecBufferDesc type_3_desc;
-  SECURITY_STATUS status;
-  unsigned long attrs;
-  TimeStamp tsDummy; /* For Windows 9x compatibility of SSPI calls */
-
-  (void)passwdp;
-  (void)userp;
-  (void)data;
-
-  /* Setup the type-2 "input" security buffer */
-  type_2_desc.ulVersion = SECBUFFER_VERSION;
-  type_2_desc.cBuffers  = 1;
-  type_2_desc.pBuffers  = &type_2_buf;
-  type_2_buf.BufferType = SECBUFFER_TOKEN;
-  type_2_buf.pvBuffer   = ntlm->type_2;
-  type_2_buf.cbBuffer   = ntlm->n_type_2;
-
-  /* Setup the type-3 "output" security buffer */
-  type_3_desc.ulVersion = SECBUFFER_VERSION;
-  type_3_desc.cBuffers  = 1;
-  type_3_desc.pBuffers  = &type_3_buf;
-  type_3_buf.BufferType = SECBUFFER_TOKEN;
-  type_3_buf.pvBuffer   = ntlm->output_token;
-  type_3_buf.cbBuffer   = curlx_uztoul(ntlm->max_token_length);
-
-  /* Generate our type-3 message */
-  status = s_pSecFn->InitializeSecurityContext(&ntlm->handle,
-                                               &ntlm->c_handle,
-                                               (TCHAR *) TEXT(""),
-                                               ISC_REQ_CONFIDENTIALITY |
-                                               ISC_REQ_REPLAY_DETECT |
-                                               ISC_REQ_CONNECTION,
-                                               0, SECURITY_NETWORK_DREP,
-                                               &type_2_desc,
-                                               0, &ntlm->c_handle,
-                                               &type_3_desc,
-                                               &attrs, &tsDummy);
-  if(status != SEC_E_OK)
-    return CURLE_RECV_ERROR;
-
-  size = type_3_buf.cbBuffer;
-
-  /* Return with binary blob encoded into base64 */
-  result = Curl_base64_encode(NULL, (char *)ntlm->output_token, size,
-                              outptr, outlen);
-
-  Curl_ntlm_sspi_cleanup(ntlm);
-
-  return result;
-
-#else
-
+  size_t size;
   unsigned char ntlmbuf[NTLM_BUFSIZE];
   int lmrespoff;
   unsigned char lmresp[24]; /* fixed-size */
@@ -706,7 +506,6 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
   size_t hostlen = 0;
   size_t userlen = 0;
   size_t domlen = 0;
-  CURLcode res = CURLE_OK;
 
   user = strchr(userp, '\\');
   if(!user)
@@ -733,7 +532,7 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
     hostlen = strlen(host);
   }
 
-#if USE_NTRESPONSES
+#if USE_NTRESPONSES && USE_NTLM_V2
   if(ntlm->target_info_len) {
     unsigned char ntbuffer[0x18];
     unsigned int entropy[2];
@@ -742,35 +541,35 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
     entropy[0] = Curl_rand(data);
     entropy[1] = Curl_rand(data);
 
-    res = Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer);
-    if(res)
-      return res;
+    result = Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer);
+    if(result)
+      return result;
 
-    res = Curl_ntlm_core_mk_ntlmv2_hash(user, userlen, domain, domlen,
-                                        ntbuffer, ntlmv2hash);
-    if(res)
-      return res;
+    result = Curl_ntlm_core_mk_ntlmv2_hash(user, userlen, domain, domlen,
+                                           ntbuffer, ntlmv2hash);
+    if(result)
+      return result;
 
     /* LMv2 response */
-    res = Curl_ntlm_core_mk_lmv2_resp(ntlmv2hash,
-                                      (unsigned char *)&entropy[0],
-                                      &ntlm->nonce[0], lmresp);
-    if(res)
-      return res;
+    result = Curl_ntlm_core_mk_lmv2_resp(ntlmv2hash,
+                                         (unsigned char *)&entropy[0],
+                                         &ntlm->nonce[0], lmresp);
+    if(result)
+      return result;
 
     /* NTLMv2 response */
-    res = Curl_ntlm_core_mk_ntlmv2_resp(ntlmv2hash,
-                                        (unsigned char *)&entropy[0],
-                                        ntlm, &ntlmv2resp, &ntresplen);
-    if(res)
-      return res;
+    result = Curl_ntlm_core_mk_ntlmv2_resp(ntlmv2hash,
+                                           (unsigned char *)&entropy[0],
+                                           ntlm, &ntlmv2resp, &ntresplen);
+    if(result)
+      return result;
 
     ptr_ntresp = ntlmv2resp;
   }
   else
 #endif
 
-#if USE_NTLM2SESSION
+#if USE_NTRESPONSES && USE_NTLM2SESSION
   /* We don't support NTLM2 if we don't have USE_NTRESPONSES */
   if(ntlm->flags & NTLMFLAG_NEGOTIATE_NTLM2_KEY) {
     unsigned char ntbuffer[0x18];
@@ -792,13 +591,13 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
     memcpy(tmp, &ntlm->nonce[0], 8);
     memcpy(tmp + 8, entropy, 8);
 
-    Curl_ssl_md5sum(tmp, 16, md5sum, MD5_DIGEST_LENGTH);
-
-    /* We shall only use the first 8 bytes of md5sum, but the des
-       code in Curl_ntlm_core_lm_resp only encrypt the first 8 bytes */
-    if(CURLE_OUT_OF_MEMORY ==
-       Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer))
-      return CURLE_OUT_OF_MEMORY;
+    result = Curl_ssl_md5sum(tmp, 16, md5sum, MD5_DIGEST_LENGTH);
+    if(!result)
+      /* We shall only use the first 8 bytes of md5sum, but the des code in
+         Curl_ntlm_core_lm_resp only encrypt the first 8 bytes */
+      result = Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer);
+    if(result)
+      return result;
 
     Curl_ntlm_core_lm_resp(ntbuffer, md5sum, ntresp);
 
@@ -815,14 +614,19 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
     unsigned char lmbuffer[0x18];
 
 #if USE_NTRESPONSES
-    if(CURLE_OUT_OF_MEMORY ==
-       Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer))
-      return CURLE_OUT_OF_MEMORY;
+    result = Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer);
+    if(result)
+      return result;
+
     Curl_ntlm_core_lm_resp(ntbuffer, &ntlm->nonce[0], ntresp);
 #endif
 
-    Curl_ntlm_core_mk_lm_hash(data, passwdp, lmbuffer);
+    result = Curl_ntlm_core_mk_lm_hash(data, passwdp, lmbuffer);
+    if(result)
+      return result;
+
     Curl_ntlm_core_lm_resp(lmbuffer, &ntlm->nonce[0], lmresp);
+
     /* A safer but less compatible alternative is:
      *   Curl_ntlm_core_lm_resp(ntbuffer, &ntlm->nonce[0], lmresp);
      * See http://davenport.sourceforge.net/ntlm.html#ntlmVersion2 */
@@ -954,7 +758,7 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
     ntlm_print_hex(stderr, (char *)&ntlmbuf[ntrespoff], ntresplen);
   });
 
-  Curl_safefree(ntlmv2resp);/* Free the dynamic buffer allocated for NTLMv2 */
+  free(ntlmv2resp);/* Free the dynamic buffer allocated for NTLMv2 */
 
 #endif
 
@@ -997,14 +801,17 @@ CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
   size += hostlen;
 
   /* Convert domain, user, and host to ASCII but leave the rest as-is */
-  res = Curl_convert_to_network(data, (char *)&ntlmbuf[domoff],
-                                size - domoff);
-  if(res)
+  result = Curl_convert_to_network(data, (char *)&ntlmbuf[domoff],
+                                   size - domoff);
+  if(result)
     return CURLE_CONV_FAILED;
 
   /* Return with binary blob encoded into base64 */
-  return Curl_base64_encode(NULL, (char *)ntlmbuf, size, outptr, outlen);
-#endif
+  result = Curl_base64_encode(NULL, (char *)ntlmbuf, size, outptr, outlen);
+
+  Curl_sasl_ntlm_cleanup(ntlm);
+
+  return result;
 }
 
-#endif /* USE_NTLM */
+#endif /* USE_NTLM && !USE_WINDOWS_SSPI */