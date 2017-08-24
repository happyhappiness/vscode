{
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