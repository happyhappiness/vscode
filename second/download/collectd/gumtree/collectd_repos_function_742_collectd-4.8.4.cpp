static size_t cc_curl_callback (void *buf, /* {{{ */
    size_t size, size_t nmemb, void *user_data)
{
  web_page_t *wp;
  size_t len;
  
  len = size * nmemb;
  if (len <= 0)
    return (len);

  wp = user_data;
  if (wp == NULL)
    return (0);

  if ((wp->buffer_fill + len) >= wp->buffer_size)
  {
    char *temp;
    size_t temp_size;

    temp_size = wp->buffer_fill + len + 1;
    temp = (char *) realloc (wp->buffer, temp_size);
    if (temp == NULL)
    {
      ERROR ("curl plugin: realloc failed.");
      return (0);
    }
    wp->buffer = temp;
    wp->buffer_size = temp_size;
  }

  memcpy (wp->buffer + wp->buffer_fill, (char *) buf, len);
  wp->buffer_fill += len;
  wp->buffer[wp->buffer_fill] = 0;

  return (len);
}