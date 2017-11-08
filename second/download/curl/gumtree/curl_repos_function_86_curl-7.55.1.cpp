static void setup(CURL *hnd, int num, const char *upload)
{
  FILE *out;
  char url[256];
  char filename[128];
  struct stat file_info;
  curl_off_t uploadsize;

  snprintf(filename, 128, "dl-%d", num);
  out = fopen(filename, "wb");

  snprintf(url, 256, "https://localhost:8443/upload-%d", num);

  /* get the file size of the local file */
  stat(upload, &file_info);
  uploadsize = file_info.st_size;

  indata[num].in = fopen(upload, "rb");
  indata[num].hnd = hnd;

  /* write to this file */
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, out);

  /* we want to use our own read function */
  curl_easy_setopt(hnd, CURLOPT_READFUNCTION, read_callback);
  /* read from this file */
  curl_easy_setopt(hnd, CURLOPT_READDATA, &indata[num]);
  /* provide the size of the upload */
  curl_easy_setopt(hnd, CURLOPT_INFILESIZE_LARGE, uploadsize);

  /* send in the URL to store the upload as */
  curl_easy_setopt(hnd, CURLOPT_URL, url);

  /* upload please */
  curl_easy_setopt(hnd, CURLOPT_UPLOAD, 1L);

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