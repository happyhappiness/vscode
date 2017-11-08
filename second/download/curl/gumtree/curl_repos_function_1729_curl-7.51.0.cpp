void Curl_version_init(void)
{
  curl_version();
  curl_version_info(CURLVERSION_NOW);
}