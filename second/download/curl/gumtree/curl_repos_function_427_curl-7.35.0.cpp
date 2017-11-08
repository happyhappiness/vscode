static void setup_handle(char *base_url, CURLM *m, int handlenum)
{
  char urlbuf[256];

  sprintf(urlbuf, "%s%s", base_url, urlstring[handlenum]);
  curl_easy_setopt(handles[handlenum], CURLOPT_URL, urlbuf);
  curl_easy_setopt(handles[handlenum], CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(handles[handlenum], CURLOPT_FAILONERROR, 1L);
  curl_easy_setopt(handles[handlenum], CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(handles[handlenum], CURLOPT_WRITEDATA, NULL);
  curl_multi_add_handle(m, handles[handlenum]);
}