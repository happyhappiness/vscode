static int bind_shutdown(void) /* {{{ */
{
  if (curl != NULL) {
    curl_easy_cleanup(curl);
    curl = NULL;
  }

  return 0;
}