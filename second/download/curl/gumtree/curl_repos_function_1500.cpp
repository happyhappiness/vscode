static void cleanup(struct negotiatedata *neg_ctx)
{
  /* Free our security context */
  if(neg_ctx->context) {
    s_pSecFn->DeleteSecurityContext(neg_ctx->context);
    free(neg_ctx->context);
    neg_ctx->context = NULL;
  }

  /* Free our credentials handle */
  if(neg_ctx->credentials) {
    s_pSecFn->FreeCredentialsHandle(neg_ctx->credentials);
    free(neg_ctx->credentials);
    neg_ctx->credentials = NULL;
  }

  /* Free our identity */
  Curl_sspi_free_identity(neg_ctx->p_identity);
  neg_ctx->p_identity = NULL;

  /* Free the SPN and output token */
  Curl_safefree(neg_ctx->server_name);
  Curl_safefree(neg_ctx->output_token);

  /* Reset any variables */
  neg_ctx->token_max = 0;
}