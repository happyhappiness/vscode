static size_t nginx_curl_callback (void *buf, size_t size, size_t nmemb, void *stream)
{
  size_t len = size * nmemb;

  if ((nginx_buffer_len + len) >= ABUFFER_SIZE)
  {
    len = (ABUFFER_SIZE - 1) - nginx_buffer_len;
  }

  if (len <= 0)
    return (len);

  memcpy (nginx_buffer + nginx_buffer_len, (char *) buf, len);
  nginx_buffer_len += len;
  nginx_buffer[nginx_buffer_len] = '\0';

  return (len);
}