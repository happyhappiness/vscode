static void setup(CURL *hnd, int num)
{
  FILE *out;
  char filename[128];

  snprintf(filename, 128, "dl-%d", num);

  out = fopen(filename, "wb");

  /* write to this file */
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, out);

  /* set the same URL */
  curl_easy_setopt(hnd, CURLOPT_URL, "https://localhost:8443/index.html");

  /* please be verbose */
  curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(hnd, CURLOPT_DEBUGFUNCTION, my_trace);

  /* HTTP/2 please */
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);

  /* we use a self-signed test server, skip verification during debugging */
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);

#if (CURLPIPE_MULTIPLEX > 0)
  /* wait for pipe connection to confirm */
  curl_easy_setopt(hnd, CURLOPT_PIPEWAIT, 1L);
#endif

  curl_hnd[num] = hnd;
}