int main(void)
{
  CURL *curl_handle;
  static const char *headerfilename = "head.out";
  FILE *headerfile;
  static const char *bodyfilename = "body.out";
  FILE *bodyfile;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* set URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://example.com");

  /* no progress meter please */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  /* open the files */
  headerfile = fopen(headerfilename,"wb");
  if (headerfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
  bodyfile = fopen(bodyfilename,"wb");
  if (bodyfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }

  /* we want the headers be written to this file handle */
  curl_easy_setopt(curl_handle,   CURLOPT_WRITEHEADER, headerfile);

  /* we want the body be written to this file handle instead of stdout */
  curl_easy_setopt(curl_handle,   CURLOPT_WRITEDATA, bodyfile);

  /* get it! */
  curl_easy_perform(curl_handle);

  /* close the header file */
  fclose(headerfile);

  /* close the body file */
  fclose(bodyfile);

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  return 0;
}