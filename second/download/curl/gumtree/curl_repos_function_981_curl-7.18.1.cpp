static int nss_load_key(struct connectdata *conn, char *key_file)
{
#ifdef HAVE_PK11_CREATEGENERICOBJECT
  PK11SlotInfo * slot = NULL;
  PK11GenericObject *rv;
  CK_ATTRIBUTE *attrs;
  CK_ATTRIBUTE theTemplate[20];
  CK_BBOOL cktrue = CK_TRUE;
  CK_OBJECT_CLASS objClass = CKO_PRIVATE_KEY;
  CK_SLOT_ID slotID;
  char *slotname = NULL;
  pphrase_arg_t *parg = NULL;

  attrs = theTemplate;

  /* FIXME: grok the various file types */

  slotID = 1; /* hardcoded for now */

  slotname = (char *)malloc(SLOTSIZE);
  snprintf(slotname, SLOTSIZE, "PEM Token #%ld", slotID);

  slot = PK11_FindSlotByName(slotname);
  free(slotname);

  if(!slot)
    return 0;

  PK11_SETATTRS(attrs, CKA_CLASS, &objClass, sizeof(objClass) ); attrs++;
  PK11_SETATTRS(attrs, CKA_TOKEN, &cktrue, sizeof(CK_BBOOL) ); attrs++;
  PK11_SETATTRS(attrs, CKA_LABEL, (unsigned char *)key_file,
                strlen(key_file)+1); attrs++;

  /* When adding an encrypted key the PKCS#11 will be set as removed */
  rv = PK11_CreateGenericObject(slot, theTemplate, 3, PR_FALSE /* isPerm */);
  if(rv == NULL) {
    PR_SetError(SEC_ERROR_BAD_KEY, 0);
    return 0;
  }

  /* This will force the token to be seen as re-inserted */
  SECMOD_WaitForAnyTokenEvent(mod, 0, 0);
  PK11_IsPresent(slot);

  parg = (pphrase_arg_t *) malloc(sizeof(*parg));
  parg->retryCount = 0;
  parg->data = conn->data;
  /* parg is initialized in nss_Init_Tokens() */
  if(PK11_Authenticate(slot, PR_TRUE, parg) != SECSuccess) {
    free(parg);
    return 0;
  }
  free(parg);

  return 1;
#else
  /* If we don't have PK11_CreateGenericObject then we can't load a file-based
   * key.
   */
  (void)conn; /* unused */
  (void)key_file; /* unused */
  return 0;
#endif
}