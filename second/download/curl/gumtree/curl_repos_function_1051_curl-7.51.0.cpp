void Curl_cleanup_negotiate(struct Curl_easy *data)
{
  Curl_auth_spnego_cleanup(&data->state.negotiate);
  Curl_auth_spnego_cleanup(&data->state.proxyneg);
}