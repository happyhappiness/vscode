{
    s_pSecFn->DeleteSecurityContext(krb5->context);

    memcpy(krb5->context, &context, sizeof(context));
  }