static int ascent_read(void) /* {{{ */
{
  int status;

  if (curl == NULL) {
    ERROR("ascent plugin: I don't have a CURL object.");
    return (-1);
  }

  if (url == NULL) {
    ERROR("ascent plugin: No URL has been configured.");
    return (-1);
  }

  ascent_buffer_fill = 0;

  curl_easy_setopt(curl, CURLOPT_URL, url);

  if (curl_easy_perform(curl) != CURLE_OK) {
    ERROR("ascent plugin: curl_easy_perform failed: %s", ascent_curl_error);
    return (-1);
  }

  status = ascent_xml(ascent_buffer);
  if (status != 0)
    return (-1);
  else
    return (0);
}