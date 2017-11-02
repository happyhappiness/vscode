static CURLcode unit_setup(void)
{
  password = strdup("");
  login = strdup("");
  if (!password || !login) {
	  Curl_safefree(password);
	  Curl_safefree(login);
	  return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}