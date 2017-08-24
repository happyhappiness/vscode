f(status == SEC_I_COMPLETE_NEEDED ||
       status == SEC_I_COMPLETE_AND_CONTINUE)
      s_pSecFn->CompleteAuthToken(&credentials, &resp_desc);
    else if(status != SEC_E_OK && status != SEC_I_CONTINUE_NEEDED) {
      s_pSecFn->FreeCredentialsHandle(&credentials);

      Curl_sspi_free_identity(p_identity);
      free(output_token);

      Curl_safefree(digest->http_context);

      return CURLE_OUT_OF_MEMORY;
    }