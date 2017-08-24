{
    s_pSecFn->DeleteSecurityContext(&sspi_context);
    s_pSecFn->FreeContextBuffer(names.sUserName);
    failf(data, "Failed to determine user name.");
    return CURLE_COULDNT_CONNECT;
  }