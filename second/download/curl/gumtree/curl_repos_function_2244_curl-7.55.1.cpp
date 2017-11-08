void Curl_auth_digest_cleanup(struct digestdata *digest)
{
  /* Free the input token */
  Curl_safefree(digest->input_token);

  /* Reset any variables */
  digest->input_token_len = 0;

  /* Delete security context */
  if(digest->http_context) {
    s_pSecFn->DeleteSecurityContext(digest->http_context);
    Curl_safefree(digest->http_context);
  }

  /* Free the copy of user/passwd used to make the identity for http_context */
  Curl_safefree(digest->user);
  Curl_safefree(digest->passwd);
}