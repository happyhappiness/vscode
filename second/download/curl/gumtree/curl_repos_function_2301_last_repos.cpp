void Curl_auth_spnego_cleanup(struct negotiatedata *nego)
{
  OM_uint32 minor_status;

  /* Free our security context */
  if(nego->context != GSS_C_NO_CONTEXT) {
    gss_delete_sec_context(&minor_status, &nego->context, GSS_C_NO_BUFFER);
    nego->context = GSS_C_NO_CONTEXT;
  }

  /* Free the output token */
  if(nego->output_token.value) {
    gss_release_buffer(&minor_status, &nego->output_token);
    nego->output_token.value = NULL;
    nego->output_token.length = 0;

  }

  /* Free the SPN */
  if(nego->spn != GSS_C_NO_NAME) {
    gss_release_name(&minor_status, &nego->spn);
    nego->spn = GSS_C_NO_NAME;
  }

  /* Reset any variables */
  nego->status = 0;
}