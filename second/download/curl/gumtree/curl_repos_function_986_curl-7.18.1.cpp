static SECStatus nss_Init_Tokens(struct connectdata * conn)
{
  PK11SlotList *slotList;
  PK11SlotListElement *listEntry;
  SECStatus ret, status = SECSuccess;
  pphrase_arg_t *parg = NULL;

  parg = (pphrase_arg_t *) malloc(sizeof(*parg));
  parg->retryCount = 0;
  parg->data = conn->data;

  PK11_SetPasswordFunc(nss_get_password);

  slotList =
    PK11_GetAllTokens(CKM_INVALID_MECHANISM, PR_FALSE, PR_TRUE, NULL);

  for(listEntry = PK11_GetFirstSafe(slotList);
      listEntry; listEntry = listEntry->next) {
    PK11SlotInfo *slot = listEntry->slot;

    if(PK11_NeedLogin(slot) && PK11_NeedUserInit(slot)) {
      if(slot == PK11_GetInternalKeySlot()) {
        failf(conn->data, "The NSS database has not been initialized");
      }
      else {
        failf(conn->data, "The token %s has not been initialized",
              PK11_GetTokenName(slot));
      }
      PK11_FreeSlot(slot);
      continue;
    }

    ret = PK11_Authenticate(slot, PR_TRUE, parg);
    if(SECSuccess != ret) {
      if(PR_GetError() == SEC_ERROR_BAD_PASSWORD)
        infof(conn->data, "The password for token '%s' is incorrect\n",
              PK11_GetTokenName(slot));
      status = SECFailure;
      break;
    }
    parg->retryCount = 0; /* reset counter to 0 for the next token */
    PK11_FreeSlot(slot);
  }

  free(parg);

  return status;
}