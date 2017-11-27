static int bind_read (void) /* {{{ */
{
  int status;

  if (curl == NULL)
  {
    ERROR ("bind plugin: I don't have a CURL object.");
    return (-1);
  }

  bind_buffer_fill = 0;
  if (curl_easy_perform (curl) != 0)
  {
    ERROR ("bind plugin: curl_easy_perform failed: %s",
        bind_curl_error);
    return (-1);
  }

  status = bind_xml (bind_buffer);
  if (status != 0)
    return (-1);
  else
    return (0);
}