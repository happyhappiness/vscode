f(userp && *userp) {
    CURLcode result;

    /* Populate our identity structure */
    result = Curl_create_sspi_identity(userp, passwdp, &ntlm->identity);
    if(result)
      return result;

    /* Allow proper cleanup of the identity structure */
    ntlm->p_identity = &ntlm->identity;
  }
  else
    /* Use the current Windows user */
    ntlm->p_identity = NULL