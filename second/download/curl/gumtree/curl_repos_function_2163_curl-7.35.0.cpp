static CURLcode nss_load_key(struct connectdata *conn, int sockindex,
                             char *key_file)
{
  PK11SlotInfo *slot;
  SECStatus status;
  CURLcode rv;
  struct ssl_connect_data *ssl = conn->ssl;
  (void)sockindex; /* unused */

  rv = nss_create_object(ssl, CKO_PRIVATE_KEY, key_file, FALSE);
  if(CURLE_OK != rv) {
    PR_SetError(SEC_ERROR_BAD_KEY, 0);
    return rv;
  }

  slot = PK11_FindSlotByName("PEM Token #1");
  if(!slot)
    return CURLE_SSL_CERTPROBLEM;

  /* This will force the token to be seen as re-inserted */
  SECMOD_WaitForAnyTokenEvent(mod, 0, 0);
  PK11_IsPresent(slot);

  status = PK11_Authenticate(slot, PR_TRUE,
                             conn->data->set.str[STRING_KEY_PASSWD]);
  PK11_FreeSlot(slot);
  return (SECSuccess == status)
    ? CURLE_OK
    : CURLE_SSL_CERTPROBLEM;
}