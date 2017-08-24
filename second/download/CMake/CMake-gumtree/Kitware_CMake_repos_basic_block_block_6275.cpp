{
      s_pSecFn->FreeCredentialsHandle(&credentials);

      Curl_sspi_free_identity(p_identity);
      free(output_token);

      return CURLE_OUT_OF_MEMORY;
    }