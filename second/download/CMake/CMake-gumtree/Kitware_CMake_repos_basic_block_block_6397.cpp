{
    /* Query the security package for Negotiate */
    nego->status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *)
                                                      TEXT(SP_NAME_NEGOTIATE),
                                                      &SecurityPackage);
    if(nego->status != SEC_E_OK)
      return CURLE_NOT_BUILT_IN;

    nego->token_max = SecurityPackage->cbMaxToken;

    /* Release the package buffer as it is not required anymore */
    s_pSecFn->FreeContextBuffer(SecurityPackage);

    /* Allocate our output buffer */
    nego->output_token = malloc(nego->token_max);
    if(!nego->output_token)
      return CURLE_OUT_OF_MEMORY;
 }