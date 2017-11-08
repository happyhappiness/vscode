int curl_formget(struct curl_httppost *form, void *arg,
                 curl_formget_callback append)
{
  (void) form;
  (void) arg;
  (void) append;
  return CURL_FORMADD_DISABLED;
}