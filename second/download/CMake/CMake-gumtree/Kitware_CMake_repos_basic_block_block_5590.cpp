f(sspi_send_token.pvBuffer) {
      s_pSecFn->FreeContextBuffer(sspi_send_token.pvBuffer);
      sspi_send_token.pvBuffer = NULL;
    }