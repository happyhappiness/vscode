{
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