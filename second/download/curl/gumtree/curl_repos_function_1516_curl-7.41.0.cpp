void Curl_sasl_digest_cleanup(struct digestdata *digest)
{
  /* Free the input token */
  Curl_safefree(digest->input_token);

  /* Reset any variables */
  digest->input_token_len = 0;
}