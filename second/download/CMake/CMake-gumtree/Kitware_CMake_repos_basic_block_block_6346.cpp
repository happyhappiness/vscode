{
    s_pSecFn->FreeCredentialsHandle(krb5->credentials);
    free(krb5->credentials);
    krb5->credentials = NULL;
  }