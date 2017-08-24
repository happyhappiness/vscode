f(user && *user) {
      /* Populate our identity structure */
      result = Curl_create_sspi_identity(user, password, &nego->identity);
      if(result)
        return result;

      /* Allow proper cleanup of the identity structure */
      nego->p_identity = &nego->identity;
    }
    else
      /* Use the current Windows user */
      nego->p_identity = NULL