char *Curl_sasl_build_gssapi_spn(const char *service, const char *host)
{
  /* Generate and return our SPN */
  return aprintf("%s@%s", service, host);
}