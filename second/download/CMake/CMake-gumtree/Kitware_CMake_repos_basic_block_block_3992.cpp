{
  curl_socket_t sfd;
  CURLcode result;
  ssize_t n1;
  struct connectdata *c;

  result = easy_connection(data, &sfd, &c);
  if(result)
    return result;

  *n = 0;
  result = Curl_read(c, sfd, buffer, buflen, &n1);

  if(result)
    return result;

  *n = (size_t)n1;

  return CURLE_OK;
}