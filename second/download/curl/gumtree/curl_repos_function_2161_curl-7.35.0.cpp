static SECStatus nss_cache_crl(SECItem *crlDER)
{
  CERTCertDBHandle *db = CERT_GetDefaultCertDB();
  CERTSignedCrl *crl = SEC_FindCrlByDERCert(db, crlDER, 0);
  if(crl) {
    /* CRL already cached */
    SEC_DestroyCrl(crl);
    SECITEM_FreeItem(crlDER, PR_FALSE);
    return SECSuccess;
  }

  /* acquire lock before call of CERT_CacheCRL() */
  PR_Lock(nss_crllock);
  if(SECSuccess != CERT_CacheCRL(db, crlDER)) {
    /* unable to cache CRL */
    PR_Unlock(nss_crllock);
    SECITEM_FreeItem(crlDER, PR_FALSE);
    return SECFailure;
  }

  /* we need to clear session cache, so that the CRL could take effect */
  SSL_ClearSessionCache();
  PR_Unlock(nss_crllock);
  return SECSuccess;
}