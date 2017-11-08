static int WriteProc(void *param, char *text, int len)
{
  struct SessionHandle *data = (struct SessionHandle *)param;
  len = 0; /* prevent compiler warning */
  Curl_client_write(data, CLIENTWRITE_BODY, text, 0);
  return 0;
}