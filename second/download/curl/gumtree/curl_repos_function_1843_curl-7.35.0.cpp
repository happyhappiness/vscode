CURLcode Curl_sasl_decode_ntlm_type2_message(struct SessionHandle *data,
                                             const char *type2msg,
                                             struct ntlmdata *ntlm)
{
#ifdef USE_NSS
  CURLcode result;

  /* make sure the crypto backend is initialized */
  result = Curl_nss_force_init(data);
  if(result)
    return result;
#endif

  return Curl_ntlm_decode_type2_message(data, type2msg, ntlm);
}