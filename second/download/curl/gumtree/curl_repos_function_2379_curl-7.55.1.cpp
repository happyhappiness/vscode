static OSStatus CopyIdentityFromPKCS12File(const char *cPath,
                                           const char *cPassword,
                                           SecIdentityRef *out_cert_and_key)
{
  OSStatus status = errSecItemNotFound;
  CFURLRef pkcs_url = CFURLCreateFromFileSystemRepresentation(NULL,
    (const UInt8 *)cPath, strlen(cPath), false);
  CFStringRef password = cPassword ? CFStringCreateWithCString(NULL,
    cPassword, kCFStringEncodingUTF8) : NULL;
  CFDataRef pkcs_data = NULL;

  /* We can import P12 files on iOS or OS X 10.7 or later: */
  /* These constants are documented as having first appeared in 10.6 but they
     raise linker errors when used on that cat for some reason. */
#if CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS
  if(CFURLCreateDataAndPropertiesFromResource(NULL, pkcs_url, &pkcs_data,
    NULL, NULL, &status)) {
    const void *cKeys[] = {kSecImportExportPassphrase};
    const void *cValues[] = {password};
    CFDictionaryRef options = CFDictionaryCreate(NULL, cKeys, cValues,
      password ? 1L : 0L, NULL, NULL);
    CFArrayRef items = NULL;

    /* Here we go: */
    status = SecPKCS12Import(pkcs_data, options, &items);
    if(status == errSecSuccess && items && CFArrayGetCount(items)) {
      CFDictionaryRef identity_and_trust = CFArrayGetValueAtIndex(items, 0L);
      const void *temp_identity = CFDictionaryGetValue(identity_and_trust,
        kSecImportItemIdentity);

      /* Retain the identity; we don't care about any other data... */
      CFRetain(temp_identity);
      *out_cert_and_key = (SecIdentityRef)temp_identity;
    }

    if(items)
      CFRelease(items);
    CFRelease(options);
    CFRelease(pkcs_data);
  }
#endif /* CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS */
  if(password)
    CFRelease(password);
  CFRelease(pkcs_url);
  return status;
}