CURLcode Curl_sasl_create_ntlm_type3_message(struct SessionHandle *data,
                                             const char *userp,
                                             const char *passwdp,
                                             struct ntlmdata *ntlm,
                                             char **outptr, size_t *outlen)
{
  return Curl_ntlm_create_type3_message(data, userp, passwdp, ntlm, outptr,
                                        outlen);
}