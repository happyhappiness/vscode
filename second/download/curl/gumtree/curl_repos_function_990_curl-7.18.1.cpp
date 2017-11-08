static SECStatus SelectClientCert(void *arg, PRFileDesc *sock,
                                  struct CERTDistNamesStr *caNames,
                                  struct CERTCertificateStr **pRetCert,
                                  struct SECKEYPrivateKeyStr **pRetKey)
{
  CERTCertificate *cert;
  SECKEYPrivateKey *privKey;
  char *nickname = (char *)arg;
  void *proto_win = NULL;
  SECStatus secStatus = SECFailure;
  PK11SlotInfo *slot;
  (void)caNames;

  proto_win = SSL_RevealPinArg(sock);

  if(!nickname)
    return secStatus;

  cert = PK11_FindCertFromNickname(nickname, proto_win);
  if(cert) {

    if(!strncmp(nickname, "PEM Token", 9)) {
      CK_SLOT_ID slotID = 1; /* hardcoded for now */
      char * slotname = (char *)malloc(SLOTSIZE);
      snprintf(slotname, SLOTSIZE, "PEM Token #%ld", slotID);
      slot = PK11_FindSlotByName(slotname);
      privKey = PK11_FindPrivateKeyFromCert(slot, cert, NULL);
      PK11_FreeSlot(slot);
      free(slotname);
      if(privKey) {
        secStatus = SECSuccess;
      }
    }
    else {
      privKey = PK11_FindKeyByAnyCert(cert, proto_win);
      if(privKey)
        secStatus = SECSuccess;
    }
  }

  if(secStatus == SECSuccess) {
    *pRetCert = cert;
    *pRetKey = privKey;
  }
  else {
    if(cert)
      CERT_DestroyCertificate(cert);
  }

  return secStatus;
}