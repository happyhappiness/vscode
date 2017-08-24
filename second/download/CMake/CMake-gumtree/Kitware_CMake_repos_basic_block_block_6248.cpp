{
    /* Populate our identity structure */
    result = Curl_create_sspi_identity(userp, passwdp, &identity);
    if(result) {
      free(spn);
      free(output_token);
      free(input_token);

      return result;
    }

    /* Allow proper cleanup of the identity structure */
    p_identity = &identity;
  }