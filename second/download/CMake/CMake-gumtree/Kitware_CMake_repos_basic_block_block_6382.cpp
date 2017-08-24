{
    gss_delete_sec_context(&minor_status, &nego->context, GSS_C_NO_BUFFER);
    nego->context = GSS_C_NO_CONTEXT;
  }