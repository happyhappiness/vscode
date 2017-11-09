void Curl_auth_gssapi_cleanup(struct kerberos5data *krb5)
{
  /* Free our security context */
  if(krb5->context) {
    s_pSecFn->DeleteSecurityContext(krb5->context);
    free(krb5->context);
    krb5->context = NULL;
  }

  /* Free our credentials handle */
  if(krb5->credentials) {
    s_pSecFn->FreeCredentialsHandle(krb5->credentials);
    free(krb5->credentials);
    krb5->credentials = NULL;
  }

  /* Free our identity */
  Curl_sspi_free_identity(krb5->p_identity);
  krb5->p_identity = NULL;

  /* Free the SPN and output token */
  Curl_safefree(krb5->spn);
  Curl_safefree(krb5->output_token);

  /* Reset any variables */
  krb5->token_max = 0;
}