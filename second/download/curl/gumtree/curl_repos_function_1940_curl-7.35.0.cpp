CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen, size_t *n)
{
  curl_socket_t sfd;
  CURLcode ret;
  ssize_t n1;
  struct connectdata *c;
  struct SessionHandle *data = (struct SessionHandle *)curl;

  ret = easy_connection(data, &sfd, &c);
  if(ret)
    return ret;

  *n = 0;
  ret = Curl_read(c, sfd, buffer, buflen, &n1);

  if(ret != CURLE_OK)
    return ret;

  *n = (size_t)n1;

  return CURLE_OK;
}