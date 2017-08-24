{
      s_pSecFn->FreeContextBuffer(sspi_w_token[0].pvBuffer);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_OUT_OF_MEMORY;
    }