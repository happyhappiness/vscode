{
    SecTrustRef trust;
    OSStatus ret = SSLCopyPeerTrust(ctx, &trust);
    if(ret != noErr || trust == NULL)
      break;

    SecKeyRef keyRef = SecTrustCopyPublicKey(trust);
    CFRelease(trust);
    if(keyRef == NULL)
      break;

#ifdef DARWIN_SSL_PINNEDPUBKEY_V1

    publicKeyBits = SecKeyCopyExternalRepresentation(keyRef, NULL);
    CFRelease(keyRef);
    if(publicKeyBits == NULL)
      break;

#elif DARWIN_SSL_PINNEDPUBKEY_V2

    OSStatus success = SecItemExport(keyRef, kSecFormatOpenSSL, 0, NULL,
                                     &publicKeyBits);
    CFRelease(keyRef);
    if(success != errSecSuccess || publicKeyBits == NULL)
      break;

#endif /* DARWIN_SSL_PINNEDPUBKEY_V2 */

    pubkeylen = CFDataGetLength(publicKeyBits);
    pubkey = CFDataGetBytePtr(publicKeyBits);

    switch(pubkeylen) {
      case 526:
        /* 4096 bit RSA pubkeylen == 526 */
        spkiHeader = rsa4096SpkiHeader;
        break;
      case 270:
        /* 2048 bit RSA pubkeylen == 270 */
        spkiHeader = rsa2048SpkiHeader;
        break;
#ifdef DARWIN_SSL_PINNEDPUBKEY_V1
      case 65:
        /* ecDSA secp256r1 pubkeylen == 65 */
        spkiHeader = ecDsaSecp256r1SpkiHeader;
        spkiHeaderLength = 26;
        break;
      case 97:
        /* ecDSA secp384r1 pubkeylen == 97 */
        spkiHeader = ecDsaSecp384r1SpkiHeader;
        spkiHeaderLength = 23;
        break;
      default:
        infof(data, "SSL: unhandled public key length: %d\n", pubkeylen);
#elif DARWIN_SSL_PINNEDPUBKEY_V2
      default:
        /* ecDSA secp256r1 pubkeylen == 91 header already included?
         * ecDSA secp384r1 header already included too
         * we assume rest of algorithms do same, so do nothing
         */
        result = Curl_pin_peer_pubkey(data, pinnedpubkey, pubkey,
                                    pubkeylen);
#endif /* DARWIN_SSL_PINNEDPUBKEY_V2 */
        continue; /* break from loop */
    }

    realpubkeylen = pubkeylen + spkiHeaderLength;
    realpubkey = malloc(realpubkeylen);
    if(!realpubkey)
      break;

    memcpy(realpubkey, spkiHeader, spkiHeaderLength);
    memcpy(realpubkey + spkiHeaderLength, pubkey, pubkeylen);

    result = Curl_pin_peer_pubkey(data, pinnedpubkey, realpubkey,
                                  realpubkeylen);

  }