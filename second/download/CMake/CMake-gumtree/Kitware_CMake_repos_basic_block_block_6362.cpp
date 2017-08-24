{
    s_pSecFn->DeleteSecurityContext(ntlm->context);
    free(ntlm->context);
    ntlm->context = NULL;
  }