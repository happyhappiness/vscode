{
      CFDictionaryRef identity_and_trust = CFArrayGetValueAtIndex(items, 0L);
      const void *temp_identity = CFDictionaryGetValue(identity_and_trust,
        kSecImportItemIdentity);

      /* Retain the identity; we don't care about any other data... */
      CFRetain(temp_identity);
      *out_cert_and_key = (SecIdentityRef)temp_identity;
    }