static OSStatus CopyIdentityWithLabel(char *label,
                                      SecIdentityRef *out_cert_and_key)
{
  OSStatus status = errSecItemNotFound;

#if CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS
  CFArrayRef keys_list;
  CFIndex keys_list_count;
  CFIndex i;
  CFStringRef common_name;

  /* SecItemCopyMatching() was introduced in iOS and Snow Leopard.
     kSecClassIdentity was introduced in Lion. If both exist, let's use them
     to find the certificate. */
  if(SecItemCopyMatching != NULL && kSecClassIdentity != NULL) {
    CFTypeRef keys[5];
    CFTypeRef values[5];
    CFDictionaryRef query_dict;
    CFStringRef label_cf = CFStringCreateWithCString(NULL, label,
      kCFStringEncodingUTF8);

    /* Set up our search criteria and expected results: */
    values[0] = kSecClassIdentity; /* we want a certificate and a key */
    keys[0] = kSecClass;
    values[1] = kCFBooleanTrue;    /* we want a reference */
    keys[1] = kSecReturnRef;
    values[2] = kSecMatchLimitAll; /* kSecMatchLimitOne would be better if the
                                    * label matching below worked correctly */
    keys[2] = kSecMatchLimit;
    /* identity searches need a SecPolicyRef in order to work */
    values[3] = SecPolicyCreateSSL(false, NULL);
    keys[3] = kSecMatchPolicy;
    /* match the name of the certificate (doesn't work in macOS 10.12.1) */
    values[4] = label_cf;
    keys[4] = kSecAttrLabel;
    query_dict = CFDictionaryCreate(NULL, (const void **)keys,
                                    (const void **)values, 5L,
                                    &kCFCopyStringDictionaryKeyCallBacks,
                                    &kCFTypeDictionaryValueCallBacks);
    CFRelease(values[3]);

    /* Do we have a match? */
    status = SecItemCopyMatching(query_dict, (CFTypeRef *) &keys_list);

    /* Because kSecAttrLabel matching doesn't work with kSecClassIdentity,
     * we need to find the correct identity ourselves */
    if(status == noErr) {
      keys_list_count = CFArrayGetCount(keys_list);
      *out_cert_and_key = NULL;
      status = 1;
      for(i = 0; i<keys_list_count; i++) {
        OSStatus err = noErr;
        SecCertificateRef cert = NULL;
        SecIdentityRef identity =
          (SecIdentityRef) CFArrayGetValueAtIndex(keys_list, i);
        err = SecIdentityCopyCertificate(identity, &cert);
        if(err == noErr) {
#if CURL_BUILD_IOS
          common_name = SecCertificateCopySubjectSummary(cert);
#elif CURL_BUILD_MAC_10_7
          SecCertificateCopyCommonName(cert, &common_name);
#endif
          if(CFStringCompare(common_name, label_cf, 0) == kCFCompareEqualTo) {
            CFRelease(cert);
            CFRelease(common_name);
            CFRetain(identity);
            *out_cert_and_key = identity;
            status = noErr;
            break;
          }
          CFRelease(common_name);
        }
        CFRelease(cert);
      }
    }

    if(keys_list)
      CFRelease(keys_list);
    CFRelease(query_dict);
    CFRelease(label_cf);
  }
  else {
#if CURL_SUPPORT_MAC_10_6
    /* On Leopard and Snow Leopard, fall back to SecKeychainSearch. */
    status = CopyIdentityWithLabelOldSchool(label, out_cert_and_key);
#endif /* CURL_SUPPORT_MAC_10_6 */
  }
#elif CURL_SUPPORT_MAC_10_6
  /* For developers building on older cats, we have no choice but to fall back
     to SecKeychainSearch. */
  status = CopyIdentityWithLabelOldSchool(label, out_cert_and_key);
#endif /* CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS */
  return status;
}