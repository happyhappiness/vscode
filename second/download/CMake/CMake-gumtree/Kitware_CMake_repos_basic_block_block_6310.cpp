{
    gss_delete_sec_context(&minor_status, &krb5->context, GSS_C_NO_BUFFER);
    krb5->context = GSS_C_NO_CONTEXT;
  }