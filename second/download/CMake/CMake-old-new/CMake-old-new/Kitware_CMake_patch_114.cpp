@@ -197,7 +197,7 @@ static OSStatus SocketWrite(SSLConnectionRef connection,
 
   do {
     length = write(sock,
-                   (char*)dataPtr + bytesSent,
+                   (char *)dataPtr + bytesSent,
                    dataLen - bytesSent);
   } while((length > 0) &&
            ( (bytesSent += length) < dataLen) );
@@ -219,8 +219,9 @@ static OSStatus SocketWrite(SSLConnectionRef connection,
   return ortn;
 }
 
-CF_INLINE const char *SSLCipherNameForNumber(SSLCipherSuite cipher) {
-  switch (cipher) {
+CF_INLINE const char *SSLCipherNameForNumber(SSLCipherSuite cipher)
+{
+  switch(cipher) {
     /* SSL version 3.0 */
     case SSL_RSA_WITH_NULL_MD5:
       return "SSL_RSA_WITH_NULL_MD5";
@@ -364,7 +365,8 @@ CF_INLINE const char *SSLCipherNameForNumber(SSLCipherSuite cipher) {
   return "SSL_NULL_WITH_NULL_NULL";
 }
 
-CF_INLINE const char *TLSCipherNameForNumber(SSLCipherSuite cipher) {
+CF_INLINE const char *TLSCipherNameForNumber(SSLCipherSuite cipher)
+{
   switch(cipher) {
     /* TLS 1.0 with AES (RFC 3268) */
     case TLS_RSA_WITH_AES_128_CBC_SHA:
@@ -883,14 +885,18 @@ static OSStatus CopyIdentityWithLabel(char *label,
                                       SecIdentityRef *out_cert_and_key)
 {
   OSStatus status = errSecItemNotFound;
+  CFArrayRef keys_list;
+  CFIndex keys_list_count;
+  CFIndex i;
+  CFStringRef common_name;
 
 #if CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS
   /* SecItemCopyMatching() was introduced in iOS and Snow Leopard.
      kSecClassIdentity was introduced in Lion. If both exist, let's use them
      to find the certificate. */
   if(SecItemCopyMatching != NULL && kSecClassIdentity != NULL) {
-    CFTypeRef keys[4];
-    CFTypeRef values[4];
+    CFTypeRef keys[5];
+    CFTypeRef values[5];
     CFDictionaryRef query_dict;
     CFStringRef label_cf = CFStringCreateWithCString(NULL, label,
       kCFStringEncodingUTF8);
@@ -900,21 +906,53 @@ static OSStatus CopyIdentityWithLabel(char *label,
     keys[0] = kSecClass;
     values[1] = kCFBooleanTrue;    /* we want a reference */
     keys[1] = kSecReturnRef;
-    values[2] = kSecMatchLimitOne; /* one is enough, thanks */
+    values[2] = kSecMatchLimitAll; /* kSecMatchLimitOne would be better if the
+                                    * label matching below worked correctly */
     keys[2] = kSecMatchLimit;
     /* identity searches need a SecPolicyRef in order to work */
-    values[3] = SecPolicyCreateSSL(false, label_cf);
+    values[3] = SecPolicyCreateSSL(false, NULL);
     keys[3] = kSecMatchPolicy;
+    /* match the name of the certificate (doesn't work in macOS 10.12.1) */
+    values[4] = label_cf;
+    keys[4] = kSecAttrLabel;
     query_dict = CFDictionaryCreate(NULL, (const void **)keys,
-                                   (const void **)values, 4L,
-                                   &kCFCopyStringDictionaryKeyCallBacks,
-                                   &kCFTypeDictionaryValueCallBacks);
+                                    (const void **)values, 5L,
+                                    &kCFCopyStringDictionaryKeyCallBacks,
+                                    &kCFTypeDictionaryValueCallBacks);
     CFRelease(values[3]);
-    CFRelease(label_cf);
 
     /* Do we have a match? */
-    status = SecItemCopyMatching(query_dict, (CFTypeRef *)out_cert_and_key);
+    status = SecItemCopyMatching(query_dict, (CFTypeRef *) &keys_list);
+
+    /* Because kSecAttrLabel matching doesn't work with kSecClassIdentity,
+     * we need to find the correct identity ourselves */
+    if(status == noErr) {
+      keys_list_count = CFArrayGetCount(keys_list);
+      *out_cert_and_key = NULL;
+      for(i=0; i<keys_list_count; i++) {
+        OSStatus err = noErr;
+        SecCertificateRef cert = NULL;
+        *out_cert_and_key =
+          (SecIdentityRef) CFArrayGetValueAtIndex(keys_list, i);
+        err = SecIdentityCopyCertificate(*out_cert_and_key, &cert);
+        if(err == noErr) {
+          SecCertificateCopyCommonName(cert, &common_name);
+          if(CFStringCompare(common_name, label_cf, 0) == kCFCompareEqualTo) {
+            CFRelease(cert);
+            CFRelease(common_name);
+            status = noErr;
+            break;
+          }
+          CFRelease(common_name);
+        }
+        *out_cert_and_key = NULL;
+        status = 1;
+        CFRelease(cert);
+      }
+    }
+
     CFRelease(query_dict);
+    CFRelease(label_cf);
   }
   else {
 #if CURL_SUPPORT_MAC_10_6
@@ -1002,6 +1040,12 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
   struct Curl_easy *data = conn->data;
   curl_socket_t sockfd = conn->sock[sockindex];
   struct ssl_connect_data *connssl = &conn->ssl[sockindex];
+  const char * const ssl_cafile = SSL_CONN_CONFIG(CAfile);
+  const bool verifypeer = SSL_CONN_CONFIG(verifypeer);
+  char * const ssl_cert = SSL_SET_OPTION(cert);
+  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
+    conn->host.name;
+  const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
 #ifdef ENABLE_IPV6
   struct in6_addr addr;
 #else
@@ -1052,162 +1096,178 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
   /* check to see if we've been told to use an explicit SSL/TLS version */
 #if CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS
   if(SSLSetProtocolVersionMax != NULL) {
-    switch(data->set.ssl.version) {
-      default:
-      case CURL_SSLVERSION_DEFAULT:
-      case CURL_SSLVERSION_TLSv1:
-        (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol1);
-        (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol12);
-        break;
-      case CURL_SSLVERSION_TLSv1_0:
-        (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol1);
-        (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol1);
-        break;
-      case CURL_SSLVERSION_TLSv1_1:
-        (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol11);
-        (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol11);
-        break;
-      case CURL_SSLVERSION_TLSv1_2:
-        (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol12);
-        (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol12);
-        break;
-      case CURL_SSLVERSION_SSLv3:
-        err = SSLSetProtocolVersionMin(connssl->ssl_ctx, kSSLProtocol3);
-        if(err != noErr) {
-          failf(data, "Your version of the OS does not support SSLv3");
-          return CURLE_SSL_CONNECT_ERROR;
-        }
-        (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kSSLProtocol3);
-        break;
-      case CURL_SSLVERSION_SSLv2:
-        err = SSLSetProtocolVersionMin(connssl->ssl_ctx, kSSLProtocol2);
-        if(err != noErr) {
-          failf(data, "Your version of the OS does not support SSLv2");
-          return CURLE_SSL_CONNECT_ERROR;
-        }
-        (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kSSLProtocol2);
+    switch(conn->ssl_config.version) {
+    case CURL_SSLVERSION_DEFAULT:
+    case CURL_SSLVERSION_TLSv1:
+      (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol1);
+      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol12);
+      break;
+    case CURL_SSLVERSION_TLSv1_0:
+      (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol1);
+      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol1);
+      break;
+    case CURL_SSLVERSION_TLSv1_1:
+      (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol11);
+      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol11);
+      break;
+    case CURL_SSLVERSION_TLSv1_2:
+      (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, kTLSProtocol12);
+      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kTLSProtocol12);
+      break;
+    case CURL_SSLVERSION_TLSv1_3:
+      failf(data, "DarwinSSL: TLS 1.3 is not yet supported");
+      return CURLE_SSL_CONNECT_ERROR;
+    case CURL_SSLVERSION_SSLv3:
+      err = SSLSetProtocolVersionMin(connssl->ssl_ctx, kSSLProtocol3);
+      if(err != noErr) {
+        failf(data, "Your version of the OS does not support SSLv3");
+        return CURLE_SSL_CONNECT_ERROR;
+      }
+      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kSSLProtocol3);
+      break;
+    case CURL_SSLVERSION_SSLv2:
+      err = SSLSetProtocolVersionMin(connssl->ssl_ctx, kSSLProtocol2);
+      if(err != noErr) {
+        failf(data, "Your version of the OS does not support SSLv2");
+        return CURLE_SSL_CONNECT_ERROR;
+      }
+      (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, kSSLProtocol2);
+      break;
+    default:
+      failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
+      return CURLE_SSL_CONNECT_ERROR;
     }
   }
   else {
 #if CURL_SUPPORT_MAC_10_8
     (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                        kSSLProtocolAll,
                                        false);
-    switch (data->set.ssl.version) {
-      default:
-      case CURL_SSLVERSION_DEFAULT:
-      case CURL_SSLVERSION_TLSv1:
-        (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kTLSProtocol1,
-                                           true);
-        (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kTLSProtocol11,
-                                           true);
-        (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kTLSProtocol12,
-                                           true);
-        break;
-      case CURL_SSLVERSION_TLSv1_0:
-        (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kTLSProtocol1,
-                                           true);
-        break;
-      case CURL_SSLVERSION_TLSv1_1:
-        (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kTLSProtocol11,
-                                           true);
-        break;
-      case CURL_SSLVERSION_TLSv1_2:
-        (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kTLSProtocol12,
-                                           true);
-        break;
-      case CURL_SSLVERSION_SSLv3:
-        err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kSSLProtocol3,
-                                           true);
-        if(err != noErr) {
-          failf(data, "Your version of the OS does not support SSLv3");
-          return CURLE_SSL_CONNECT_ERROR;
-        }
-        break;
-      case CURL_SSLVERSION_SSLv2:
-        err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                           kSSLProtocol2,
-                                           true);
-        if(err != noErr) {
-          failf(data, "Your version of the OS does not support SSLv2");
-          return CURLE_SSL_CONNECT_ERROR;
-        }
-        break;
-    }
-#endif  /* CURL_SUPPORT_MAC_10_8 */
-  }
-#else
-  (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx, kSSLProtocolAll, false);
-  switch(data->set.ssl.version) {
-    default:
+    switch(conn->ssl_config.version) {
     case CURL_SSLVERSION_DEFAULT:
     case CURL_SSLVERSION_TLSv1:
+      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                         kTLSProtocol1,
+                                         true);
+      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                         kTLSProtocol11,
+                                         true);
+      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                         kTLSProtocol12,
+                                         true);
+      break;
     case CURL_SSLVERSION_TLSv1_0:
       (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
                                          kTLSProtocol1,
                                          true);
       break;
     case CURL_SSLVERSION_TLSv1_1:
-      failf(data, "Your version of the OS does not support TLSv1.1");
-      return CURLE_SSL_CONNECT_ERROR;
+      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                         kTLSProtocol11,
+                                         true);
+      break;
     case CURL_SSLVERSION_TLSv1_2:
-      failf(data, "Your version of the OS does not support TLSv1.2");
+      (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                         kTLSProtocol12,
+                                         true);
+      break;
+    case CURL_SSLVERSION_TLSv1_3:
+      failf(data, "DarwinSSL: TLS 1.3 is not yet supported");
       return CURLE_SSL_CONNECT_ERROR;
-    case CURL_SSLVERSION_SSLv2:
+    case CURL_SSLVERSION_SSLv3:
       err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                         kSSLProtocol2,
+                                         kSSLProtocol3,
                                          true);
       if(err != noErr) {
-        failf(data, "Your version of the OS does not support SSLv2");
+        failf(data, "Your version of the OS does not support SSLv3");
         return CURLE_SSL_CONNECT_ERROR;
       }
       break;
-    case CURL_SSLVERSION_SSLv3:
+    case CURL_SSLVERSION_SSLv2:
       err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
-                                         kSSLProtocol3,
+                                         kSSLProtocol2,
                                          true);
       if(err != noErr) {
-        failf(data, "Your version of the OS does not support SSLv3");
+        failf(data, "Your version of the OS does not support SSLv2");
         return CURLE_SSL_CONNECT_ERROR;
       }
       break;
+    default:
+      failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
+      return CURLE_SSL_CONNECT_ERROR;
+    }
+#endif  /* CURL_SUPPORT_MAC_10_8 */
+  }
+#else
+  (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx, kSSLProtocolAll, false);
+  switch(conn->ssl_config.version) {
+  case CURL_SSLVERSION_DEFAULT:
+  case CURL_SSLVERSION_TLSv1:
+  case CURL_SSLVERSION_TLSv1_0:
+    (void)SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                       kTLSProtocol1,
+                                       true);
+    break;
+  case CURL_SSLVERSION_TLSv1_1:
+    failf(data, "Your version of the OS does not support TLSv1.1");
+    return CURLE_SSL_CONNECT_ERROR;
+  case CURL_SSLVERSION_TLSv1_2:
+    failf(data, "Your version of the OS does not support TLSv1.2");
+    return CURLE_SSL_CONNECT_ERROR;
+  case CURL_SSLVERSION_TLSv1_3:
+    failf(data, "Your version of the OS does not support TLSv1.3");
+    return CURLE_SSL_CONNECT_ERROR;
+  case CURL_SSLVERSION_SSLv2:
+    err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                       kSSLProtocol2,
+                                       true);
+    if(err != noErr) {
+      failf(data, "Your version of the OS does not support SSLv2");
+      return CURLE_SSL_CONNECT_ERROR;
+    }
+    break;
+  case CURL_SSLVERSION_SSLv3:
+    err = SSLSetProtocolVersionEnabled(connssl->ssl_ctx,
+                                       kSSLProtocol3,
+                                       true);
+    if(err != noErr) {
+      failf(data, "Your version of the OS does not support SSLv3");
+      return CURLE_SSL_CONNECT_ERROR;
+    }
+    break;
+  default:
+    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
+    return CURLE_SSL_CONNECT_ERROR;
   }
 #endif /* CURL_BUILD_MAC_10_8 || CURL_BUILD_IOS */
 
-  if(data->set.str[STRING_KEY]) {
+  if(SSL_SET_OPTION(key)) {
     infof(data, "WARNING: SSL: CURLOPT_SSLKEY is ignored by Secure "
-                "Transport. The private key must be in the Keychain.\n");
+          "Transport. The private key must be in the Keychain.\n");
   }
 
-  if(data->set.str[STRING_CERT]) {
+  if(ssl_cert) {
     SecIdentityRef cert_and_key = NULL;
-    bool is_cert_file = is_file(data->set.str[STRING_CERT]);
+    bool is_cert_file = is_file(ssl_cert);
 
     /* User wants to authenticate with a client cert. Look for it:
        If we detect that this is a file on disk, then let's load it.
        Otherwise, assume that the user wants to use an identity loaded
        from the Keychain. */
     if(is_cert_file) {
-      if(!data->set.str[STRING_CERT_TYPE])
+      if(!SSL_SET_OPTION(cert_type))
         infof(data, "WARNING: SSL: Certificate type not set, assuming "
                     "PKCS#12 format.\n");
-      else if(strncmp(data->set.str[STRING_CERT_TYPE], "P12",
-        strlen(data->set.str[STRING_CERT_TYPE])) != 0)
+      else if(strncmp(SSL_SET_OPTION(cert_type), "P12",
+        strlen(SSL_SET_OPTION(cert_type))) != 0)
         infof(data, "WARNING: SSL: The Security framework only supports "
                     "loading identities that are in PKCS#12 format.\n");
 
-      err = CopyIdentityFromPKCS12File(data->set.str[STRING_CERT],
-        data->set.str[STRING_KEY_PASSWD], &cert_and_key);
+      err = CopyIdentityFromPKCS12File(ssl_cert,
+        SSL_SET_OPTION(key_passwd), &cert_and_key);
     }
     else
-      err = CopyIdentityWithLabel(data->set.str[STRING_CERT], &cert_and_key);
+      err = CopyIdentityWithLabel(ssl_cert, &cert_and_key);
 
     if(err == noErr) {
       SecCertificateRef cert = NULL;
@@ -1246,27 +1306,27 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
     }
     else {
       switch(err) {
-        case errSecAuthFailed: case -25264: /* errSecPkcs12VerifyFailure */
-          failf(data, "SSL: Incorrect password for the certificate \"%s\" "
-                      "and its private key.", data->set.str[STRING_CERT]);
-          break;
-        case -26275: /* errSecDecode */ case -25257: /* errSecUnknownFormat */
-          failf(data, "SSL: Couldn't make sense of the data in the "
-                      "certificate \"%s\" and its private key.",
-                      data->set.str[STRING_CERT]);
-          break;
-        case -25260: /* errSecPassphraseRequired */
-          failf(data, "SSL The certificate \"%s\" requires a password.",
-                      data->set.str[STRING_CERT]);
-          break;
-        case errSecItemNotFound:
-          failf(data, "SSL: Can't find the certificate \"%s\" and its private "
-                      "key in the Keychain.", data->set.str[STRING_CERT]);
-          break;
-        default:
-          failf(data, "SSL: Can't load the certificate \"%s\" and its private "
-                      "key: OSStatus %d", data->set.str[STRING_CERT], err);
-          break;
+      case errSecAuthFailed: case -25264: /* errSecPkcs12VerifyFailure */
+        failf(data, "SSL: Incorrect password for the certificate \"%s\" "
+                    "and its private key.", ssl_cert);
+        break;
+      case -26275: /* errSecDecode */ case -25257: /* errSecUnknownFormat */
+        failf(data, "SSL: Couldn't make sense of the data in the "
+                    "certificate \"%s\" and its private key.",
+                    ssl_cert);
+        break;
+      case -25260: /* errSecPassphraseRequired */
+        failf(data, "SSL The certificate \"%s\" requires a password.",
+                    ssl_cert);
+        break;
+      case errSecItemNotFound:
+        failf(data, "SSL: Can't find the certificate \"%s\" and its private "
+                    "key in the Keychain.", ssl_cert);
+        break;
+      default:
+        failf(data, "SSL: Can't load the certificate \"%s\" and its private "
+                    "key: OSStatus %d", ssl_cert, err);
+        break;
       }
       return CURLE_SSL_CERTPROBLEM;
     }
@@ -1297,8 +1357,7 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
 #else
   if(SSLSetSessionOption != NULL) {
 #endif /* CURL_BUILD_MAC */
-    bool break_on_auth = !data->set.ssl.verifypeer ||
-      data->set.str[STRING_SSL_CAFILE];
+    bool break_on_auth = !conn->ssl_config.verifypeer || ssl_cafile;
     err = SSLSetSessionOption(connssl->ssl_ctx,
                               kSSLSessionOptionBreakOnServerAuth,
                               break_on_auth);
@@ -1310,7 +1369,7 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
   else {
 #if CURL_SUPPORT_MAC_10_8
     err = SSLSetEnableCertVerify(connssl->ssl_ctx,
-                                 data->set.ssl.verifypeer?true:false);
+                                 conn->ssl_config.verifypeer?true:false);
     if(err != noErr) {
       failf(data, "SSL: SSLSetEnableCertVerify() failed: OSStatus %d", err);
       return CURLE_SSL_CONNECT_ERROR;
@@ -1319,22 +1378,21 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
   }
 #else
   err = SSLSetEnableCertVerify(connssl->ssl_ctx,
-                               data->set.ssl.verifypeer?true:false);
+                               conn->ssl_config.verifypeer?true:false);
   if(err != noErr) {
     failf(data, "SSL: SSLSetEnableCertVerify() failed: OSStatus %d", err);
     return CURLE_SSL_CONNECT_ERROR;
   }
 #endif /* CURL_BUILD_MAC_10_6 || CURL_BUILD_IOS */
 
-  if(data->set.str[STRING_SSL_CAFILE]) {
-    bool is_cert_file = is_file(data->set.str[STRING_SSL_CAFILE]);
+  if(ssl_cafile) {
+    bool is_cert_file = is_file(ssl_cafile);
 
     if(!is_cert_file) {
-      failf(data, "SSL: can't load CA certificate file %s",
-            data->set.str[STRING_SSL_CAFILE]);
+      failf(data, "SSL: can't load CA certificate file %s", ssl_cafile);
       return CURLE_SSL_CACERT_BADFILE;
     }
-    if(!data->set.ssl.verifypeer) {
+    if(!verifypeer) {
       failf(data, "SSL: CA certificate set, but certificate verification "
             "is disabled");
       return CURLE_SSL_CONNECT_ERROR;
@@ -1344,22 +1402,22 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
   /* Configure hostname check. SNI is used if available.
    * Both hostname check and SNI require SSLSetPeerDomainName().
    * Also: the verifyhost setting influences SNI usage */
-  if(data->set.ssl.verifyhost) {
-    err = SSLSetPeerDomainName(connssl->ssl_ctx, conn->host.name,
-    strlen(conn->host.name));
+  if(conn->ssl_config.verifyhost) {
+    err = SSLSetPeerDomainName(connssl->ssl_ctx, hostname,
+    strlen(hostname));
 
     if(err != noErr) {
       infof(data, "WARNING: SSL: SSLSetPeerDomainName() failed: OSStatus %d\n",
             err);
     }
 
-    if((Curl_inet_pton(AF_INET, conn->host.name, &addr))
+    if((Curl_inet_pton(AF_INET, hostname, &addr))
   #ifdef ENABLE_IPV6
-    || (Curl_inet_pton(AF_INET6, conn->host.name, &addr))
+    || (Curl_inet_pton(AF_INET6, hostname, &addr))
   #endif
        ) {
-         infof(data, "WARNING: using IP address, SNI is being disabled by "
-         "the OS.\n");
+      infof(data, "WARNING: using IP address, SNI is being disabled by "
+            "the OS.\n");
     }
   }
 
@@ -1382,7 +1440,7 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
         running in an affected version of OS X. */
       if(darwinver_maj == 12 && darwinver_min <= 3 &&
          all_ciphers[i] >= 0xC001 && all_ciphers[i] <= 0xC032) {
-           continue;
+        continue;
       }
 #endif /* CURL_BUILD_MAC */
       switch(all_ciphers[i]) {
@@ -1474,21 +1532,22 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
   /* We want to enable 1/n-1 when using a CBC cipher unless the user
      specifically doesn't want us doing that: */
   if(SSLSetSessionOption != NULL) {
+    /* TODO s/data->set.ssl.enable_beast/SSL_SET_OPTION(enable_beast)/g */
     SSLSetSessionOption(connssl->ssl_ctx, kSSLSessionOptionSendOneByteRecord,
-                      !data->set.ssl_enable_beast);
+                      !data->set.ssl.enable_beast);
     SSLSetSessionOption(connssl->ssl_ctx, kSSLSessionOptionFalseStart,
                       data->set.ssl.falsestart); /* false start support */
   }
 #endif /* CURL_BUILD_MAC_10_9 || CURL_BUILD_IOS_7 */
 
   /* Check if there's a cached ID we can/should use here! */
-  if(conn->ssl_config.sessionid) {
+  if(data->set.general_ssl.sessionid) {
     char *ssl_sessionid;
     size_t ssl_sessionid_len;
 
     Curl_ssl_sessionid_lock(conn);
     if(!Curl_ssl_getsessionid(conn, (void **)&ssl_sessionid,
-                              &ssl_sessionid_len)) {
+                              &ssl_sessionid_len, sockindex)) {
       /* we got a session id, use it! */
       err = SSLSetPeerID(connssl->ssl_ctx, ssl_sessionid, ssl_sessionid_len);
       Curl_ssl_sessionid_unlock(conn);
@@ -1504,9 +1563,8 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
     else {
       CURLcode result;
       ssl_sessionid =
-        aprintf("%s:%d:%d:%s:%hu", data->set.str[STRING_SSL_CAFILE],
-                data->set.ssl.verifypeer, data->set.ssl.verifyhost,
-                conn->host.name, conn->remote_port);
+        aprintf("%s:%d:%d:%s:%hu", ssl_cafile,
+                verifypeer, SSL_CONN_CONFIG(verifyhost), hostname, port);
       ssl_sessionid_len = strlen(ssl_sessionid);
 
       err = SSLSetPeerID(connssl->ssl_ctx, ssl_sessionid, ssl_sessionid_len);
@@ -1516,7 +1574,8 @@ static CURLcode darwinssl_connect_step1(struct connectdata *conn,
         return CURLE_SSL_CONNECT_ERROR;
       }
 
-      result = Curl_ssl_addsessionid(conn, ssl_sessionid, ssl_sessionid_len);
+      result = Curl_ssl_addsessionid(conn, ssl_sessionid, ssl_sessionid_len,
+                                     sockindex);
       Curl_ssl_sessionid_unlock(conn);
       if(result) {
         failf(data, "failed to store ssl session");
@@ -1820,7 +1879,7 @@ static int verify_cert(const char *cafile, struct Curl_easy *data,
     return sslerr_to_curlerr(data, ret);
   }
 
-  switch (trust_eval) {
+  switch(trust_eval) {
     case kSecTrustResultUnspecified:
     case kSecTrustResultProceed:
       return CURLE_OK;
@@ -1842,6 +1901,8 @@ darwinssl_connect_step2(struct connectdata *conn, int sockindex)
   OSStatus err;
   SSLCipherSuite cipher;
   SSLProtocol protocol = 0;
+  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
+    conn->host.name;
 
   DEBUGASSERT(ssl_connect_2 == connssl->connecting_state
               || ssl_connect_2_reading == connssl->connecting_state
@@ -1851,7 +1912,7 @@ darwinssl_connect_step2(struct connectdata *conn, int sockindex)
   err = SSLHandshake(connssl->ssl_ctx);
 
   if(err != noErr) {
-    switch (err) {
+    switch(err) {
       case errSSLWouldBlock:  /* they're not done with us yet */
         connssl->connecting_state = connssl->ssl_direction ?
             ssl_connect_2_writing : ssl_connect_2_reading;
@@ -1860,8 +1921,8 @@ darwinssl_connect_step2(struct connectdata *conn, int sockindex)
       /* The below is errSSLServerAuthCompleted; it's not defined in
         Leopard's headers */
       case -9841:
-        if(data->set.str[STRING_SSL_CAFILE]) {
-          int res = verify_cert(data->set.str[STRING_SSL_CAFILE], data,
+        if(SSL_CONN_CONFIG(CAfile)) {
+          int res = verify_cert(SSL_CONN_CONFIG(CAfile), data,
                                 connssl->ssl_ctx);
           if(res != CURLE_OK)
             return res;
@@ -1930,7 +1991,7 @@ darwinssl_connect_step2(struct connectdata *conn, int sockindex)
         return CURLE_SSL_CONNECT_ERROR;
       default:
         failf(data, "Unknown SSL protocol error in connection to %s:%d",
-              conn->host.name, err);
+              hostname, err);
         return CURLE_SSL_CONNECT_ERROR;
     }
   }
@@ -1941,7 +2002,7 @@ darwinssl_connect_step2(struct connectdata *conn, int sockindex)
     /* Informational message */
     (void)SSLGetNegotiatedCipher(connssl->ssl_ctx, &cipher);
     (void)SSLGetNegotiatedProtocolVersion(connssl->ssl_ctx, &protocol);
-    switch (protocol) {
+    switch(protocol) {
       case kSSLProtocol2:
         infof(data, "SSL 2.0 connection using %s\n",
               SSLCipherNameForNumber(cipher));
@@ -2390,7 +2451,8 @@ void Curl_darwinssl_md5sum(unsigned char *tmp, /* input */
   (void)CC_MD5(tmp, (CC_LONG)tmplen, md5sum);
 }
 
-bool Curl_darwinssl_false_start(void) {
+bool Curl_darwinssl_false_start(void)
+{
 #if CURL_BUILD_MAC_10_9 || CURL_BUILD_IOS_7
   if(SSLSetSessionOption != NULL)
     return TRUE;
@@ -2427,7 +2489,7 @@ static ssize_t darwinssl_send(struct connectdata *conn,
   if(connssl->ssl_write_buffered_length) {
     /* Write the buffered data: */
     err = SSLWrite(connssl->ssl_ctx, NULL, 0UL, &processed);
-    switch (err) {
+    switch(err) {
       case noErr:
         /* processed is always going to be 0 because we didn't write to
            the buffer, so return how much was written to the socket */
@@ -2447,7 +2509,7 @@ static ssize_t darwinssl_send(struct connectdata *conn,
     /* We've got new data to write: */
     err = SSLWrite(connssl->ssl_ctx, mem, len, &processed);
     if(err != noErr) {
-      switch (err) {
+      switch(err) {
         case errSSLWouldBlock:
           /* Data was buffered but not sent, we have to tell the caller
              to try sending again, and remember how much was buffered */
@@ -2476,7 +2538,7 @@ static ssize_t darwinssl_recv(struct connectdata *conn,
   OSStatus err = SSLRead(connssl->ssl_ctx, buf, buffersize, &processed);
 
   if(err != noErr) {
-    switch (err) {
+    switch(err) {
       case errSSLWouldBlock:  /* return how much we read (if anything) */
         if(processed)
           return (ssize_t)processed;