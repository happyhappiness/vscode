{
    s_pSecFn->FreeCredentialsHandle(ntlm->credentials);
    free(ntlm->credentials);
    ntlm->credentials = NULL;
  }