void Curl_auth_spnego_cleanup(struct negotiatedata *nego)
{
  /* Free our security context */
  if(nego->context) {
    s_pSecFn->DeleteSecurityContext(nego->context);
    free(nego->context);
    nego->context = NULL;
  }

  /* Free our credentials handle */
  if(nego->credentials) {
    s_pSecFn->FreeCredentialsHandle(nego->credentials);
    free(nego->credentials);
    nego->credentials = NULL;
  }

  /* Free our identity */
  Curl_sspi_free_identity(nego->p_identity);
  nego->p_identity = NULL;

  /* Free the SPN and output token */
  Curl_safefree(nego->spn);
  Curl_safefree(nego->output_token);

  /* Reset any variables */
  nego->status = 0;
  nego->token_max = 0;
}