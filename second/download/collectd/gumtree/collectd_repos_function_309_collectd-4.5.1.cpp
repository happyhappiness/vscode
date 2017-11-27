static size_t ascent_curl_callback (void *buf, size_t size, size_t nmemb, /* {{{ */
    void *stream)
{
  size_t len = size * nmemb;

  if (len <= 0)
    return (len);

  if ((ascent_buffer_fill + len) >= ascent_buffer_size)
  {
    char *temp;

    temp = (char *) realloc (ascent_buffer,
        ascent_buffer_fill + len + 1);
    if (temp == NULL)
    {
      ERROR ("ascent plugin: realloc failed.");
      return (0);
    }
    ascent_buffer = temp;
    ascent_buffer_size = ascent_buffer_fill + len + 1;
  }

  memcpy (ascent_buffer + ascent_buffer_fill, (char *) buf, len);
  ascent_buffer_fill += len;
  ascent_buffer[ascent_buffer_fill] = 0;

  return (len);
}