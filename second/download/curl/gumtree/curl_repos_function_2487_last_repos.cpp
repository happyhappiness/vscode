static OSStatus CopyIdentityWithLabelOldSchool(char *label,
                                               SecIdentityRef *out_c_a_k)
{
  OSStatus status = errSecItemNotFound;
  SecKeychainAttributeList attr_list;
  SecKeychainAttribute attr;
  SecKeychainSearchRef search = NULL;
  SecCertificateRef cert = NULL;

  /* Set up the attribute list: */
  attr_list.count = 1L;
  attr_list.attr = &attr;

  /* Set up our lone search criterion: */
  attr.tag = kSecLabelItemAttr;
  attr.data = label;
  attr.length = (UInt32)strlen(label);

  /* Start searching: */
  status = SecKeychainSearchCreateFromAttributes(NULL,
                                                 kSecCertificateItemClass,
                                                 &attr_list,
                                                 &search);
  if(status == noErr) {
    status = SecKeychainSearchCopyNext(search,
                                       (SecKeychainItemRef *)&cert);
    if(status == noErr && cert) {
      /* If we found a certificate, does it have a private key? */
      status = SecIdentityCreateWithCertificate(NULL, cert, out_c_a_k);
      CFRelease(cert);
    }
  }

  if(search)
    CFRelease(search);
  return status;
}