{
    /* Do we have credientials to use or are we using single sign-on? */
    if(user && *user) {
      /* Populate our identity structure */
      result = Curl_create_sspi_identity(user, password, &nego->identity);
      if(result)
        return result;

      /* Allow proper cleanup of the identity structure */
      nego->p_identity = &nego->identity;
    }
    else
      /* Use the current Windows user */
      nego->p_identity = NULL;

    /* Allocate our credentials handle */
    nego->credentials = malloc(sizeof(CredHandle));
    if(!nego->credentials)
      return CURLE_OUT_OF_MEMORY;

    memset(nego->credentials, 0, sizeof(CredHandle));

    /* Acquire our credentials handle */
    nego->status =
      s_pSecFn->AcquireCredentialsHandle(NULL,
                                         (TCHAR *)TEXT(SP_NAME_NEGOTIATE),
                                         SECPKG_CRED_OUTBOUND, NULL,
                                         nego->p_identity, NULL, NULL,
                                         nego->credentials, &expiry);
    if(nego->status != SEC_E_OK)
      return CURLE_LOGIN_DENIED;

    /* Allocate our new context handle */
    nego->context = malloc(sizeof(CtxtHandle));
    if(!nego->context)
      return CURLE_OUT_OF_MEMORY;

    memset(nego->context, 0, sizeof(CtxtHandle));
  }