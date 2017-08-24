{
      s_pSecFn->FreeCredentialsHandle(&credentials);

      Curl_sspi_free_identity(p_identity);
      free(output_token);

      Curl_safefree(digest->http_context);

      return CURLE_OUT_OF_MEMORY;
    }