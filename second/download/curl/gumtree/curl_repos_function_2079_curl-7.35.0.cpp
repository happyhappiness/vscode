void Curl_darwinssl_close_all(struct SessionHandle *data)
{
  /* SecureTransport doesn't separate sessions from contexts, so... */
  (void)data;
}