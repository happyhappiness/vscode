static int
nss_load_cert(const char *filename, PRBool cacert)
{
#ifdef HAVE_PK11_CREATEGENERICOBJECT
  CK_SLOT_ID slotID;
  PK11SlotInfo * slot = NULL;
  PK11GenericObject *rv;
  CK_ATTRIBUTE *attrs;
  CK_ATTRIBUTE theTemplate[20];
  CK_BBOOL cktrue = CK_TRUE;
  CK_BBOOL ckfalse = CK_FALSE;
  CK_OBJECT_CLASS objClass = CKO_CERTIFICATE;
  char *slotname = NULL;
#endif
  CERTCertificate *cert;
  char *nickname = NULL;
  char *n = NULL;

  /* If there is no slash in the filename it is assumed to be a regular
   * NSS nickname.
   */
  if(is_file(filename)) {
    n = strrchr(filename, '/');
    if(n)
      n++;
    if(!mod)
      return 1;
  }
  else {
    /* A nickname from the NSS internal database */
    if(cacert)
      return 0; /* You can't specify an NSS CA nickname this way */
    nickname = strdup(filename);
    goto done;
  }

#ifdef HAVE_PK11_CREATEGENERICOBJECT
  attrs = theTemplate;

  /* All CA and trust objects go into slot 0. Other slots are used
   * for storing certificates. With each new user certificate we increment
   * the slot count. We only support 1 user certificate right now.
   */
  if(cacert)
    slotID = 0;
  else
    slotID = 1;

  slotname = (char *)malloc(SLOTSIZE);
  nickname = (char *)malloc(PATH_MAX);
  snprintf(slotname, SLOTSIZE, "PEM Token #%ld", slotID);
  snprintf(nickname, PATH_MAX, "PEM Token #%ld:%s", slotID, n);

  slot = PK11_FindSlotByName(slotname);

  if(!slot) {
    free(slotname);
    free(nickname);
    return 0;
  }

  PK11_SETATTRS(attrs, CKA_CLASS, &objClass, sizeof(objClass) ); attrs++;
  PK11_SETATTRS(attrs, CKA_TOKEN, &cktrue, sizeof(CK_BBOOL) ); attrs++;
  PK11_SETATTRS(attrs, CKA_LABEL, (unsigned char *)filename,
                strlen(filename)+1); attrs++;
  if(cacert) {
    PK11_SETATTRS(attrs, CKA_TRUST, &cktrue, sizeof(CK_BBOOL) ); attrs++;
  }
  else {
    PK11_SETATTRS(attrs, CKA_TRUST, &ckfalse, sizeof(CK_BBOOL) ); attrs++;
  }

  /* This load the certificate in our PEM module into the appropriate
   * slot.
   */
  rv = PK11_CreateGenericObject(slot, theTemplate, 4, PR_FALSE /* isPerm */);

  PK11_FreeSlot(slot);

  free(slotname);
  if(rv == NULL) {
    free(nickname);
    return 0;
  }
#else
  /* We don't have PK11_CreateGenericObject but a file-based cert was passed
   * in. We need to fail.
   */
  return 0;
#endif

done:
  /* Double-check that the certificate or nickname requested exists in
   * either the token or the NSS certificate database.
   */
  if(!cacert) {
    cert = PK11_FindCertFromNickname((char *)nickname, NULL);

    /* An invalid nickname was passed in */
    if(cert == NULL) {
      free(nickname);
      PR_SetError(SEC_ERROR_UNKNOWN_CERT, 0);
      return 0;
    }

    CERT_DestroyCertificate(cert);
  }

  free(nickname);

  return 1;
}