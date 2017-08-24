f(userp && *userp) {
      /* Populate our identity structure */
      result = Curl_create_sspi_identity(userp, passwdp, &krb5->identity);
      if(result)
        return result;

      /* Allow proper cleanup of the identity structure */
      krb5->p_identity = &krb5->identity;
    }
    else
      /* Use the current Windows user */
      krb5->p_identity = NULL