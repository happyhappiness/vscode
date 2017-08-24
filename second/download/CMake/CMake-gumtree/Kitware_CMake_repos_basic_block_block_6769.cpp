{
  PK11SlotInfo *slot, *tmp;
  SECStatus status;
  CURLcode result;
  struct ssl_connect_data *ssl = conn->ssl;
  struct Curl_easy *data = conn->data;

  (void)sockindex; /* unused */

  result = nss_create_object(ssl, CKO_PRIVATE_KEY, key_file, FALSE);
  if(result) {
    PR_SetError(SEC_ERROR_BAD_KEY, 0);
    return result;
  }

  slot = nss_find_slot_by_name("PEM Token #1");
  if(!slot)
    return CURLE_SSL_CERTPROBLEM;

  /* This will force the token to be seen as re-inserted */
  tmp = SECMOD_WaitForAnyTokenEvent(pem_module, 0, 0);
  if(tmp)
    PK11_FreeSlot(tmp);
  PK11_IsPresent(slot);

  status = PK11_Authenticate(slot, PR_TRUE, SSL_SET_OPTION(key_passwd));
  PK11_FreeSlot(slot);

  return (SECSuccess == status) ? CURLE_OK : CURLE_SSL_CERTPROBLEM;
}