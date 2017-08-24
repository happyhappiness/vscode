{
      s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      sspi_recv_token.pvBuffer = NULL;
      sspi_recv_token.cbBuffer = 0;
    }