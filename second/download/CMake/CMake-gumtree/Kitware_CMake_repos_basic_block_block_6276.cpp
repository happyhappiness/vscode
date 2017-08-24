{
      Curl_sspi_free_identity(p_identity);
      free(output_token);

      return CURLE_LOGIN_DENIED;
    }