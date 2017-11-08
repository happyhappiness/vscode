CURLcode curl_easy_send(CURL *curl, const void *buffer, size_t buflen,
                        size_t *n)
{
  curl_socket_t sfd;
  CURLcode ret;
  ssize_t n1;
  struct connectdata *c = NULL;
  struct SessionHandle *data = (struct SessionHandle *)curl;

  ret = easy_connection(data, &sfd, &c);
  if(ret)
    return ret;

  *n = 0;
  ret = Curl_write(c, sfd, buffer, buflen, &n1);

  if(n1 == -1)
    return CURLE_SEND_ERROR;

  /* detect EAGAIN */
  if((CURLE_OK == ret) && (0 == n1))
    return CURLE_AGAIN;

  *n = (size_t)n1;

  return ret;
}