{
  curl_socket_t sfd;
  CURLcode result;
  ssize_t n1;
  struct connectdata *c = NULL;

  result = easy_connection(data, &sfd, &c);
  if(result)
    return result;

  *n = 0;
  result = Curl_write(c, sfd, buffer, buflen, &n1);

  if(n1 == -1)
    return CURLE_SEND_ERROR;

  /* detect EAGAIN */
  if(!result && !n1)
    return CURLE_AGAIN;

  *n = (size_t)n1;

  return result;
}