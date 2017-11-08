static void cleanup(struct negotiatedata *neg_ctx)
{
  if(neg_ctx->context) {
    s_pSecFn->DeleteSecurityContext(neg_ctx->context);
    free(neg_ctx->context);
    neg_ctx->context = 0;
  }

  if(neg_ctx->credentials) {
    s_pSecFn->FreeCredentialsHandle(neg_ctx->credentials);
    free(neg_ctx->credentials);
    neg_ctx->credentials = 0;
  }

  if(neg_ctx->output_token) {
    free(neg_ctx->output_token);
    neg_ctx->output_token = 0;
  }

  neg_ctx->max_token_length = 0;
}