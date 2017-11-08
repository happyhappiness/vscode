static void unit_stop(void)
{
  Curl_safefree(password);
  Curl_safefree(login);
}