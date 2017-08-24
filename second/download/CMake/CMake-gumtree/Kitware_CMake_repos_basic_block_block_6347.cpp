{
    s_pSecFn->DeleteSecurityContext(krb5->context);
    free(krb5->context);
    krb5->context = NULL;
  }