int main(int argc, char **argv)
{
  CURL *curl_handle;
  char *headerfilename = "head.out";
  FILE *headerfile;
  char *bodyfilename = "body.out";
  FILE *bodyfile;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* set URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://curl.haxx.se");

  /* no progress meter please */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1);

  /* shut up completely */
  curl_easy_setopt(curl_handle, CURLOPT_MUTE, 1);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  /* open the files */
  headerfile = fopen(headerfilename,"w");
  if (headerfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
  bodyfile = fopen(bodyfilename,"w");
  if (bodyfile == NULL) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }

  /* we want the headers to this file handle */
  curl_easy_setopt(curl_handle,   CURLOPT_WRITEHEADER ,headerfile);

  /*
   * Notice here that if you want the actual data sent anywhere else but
   * stdout, you should consider using the CURLOPT_WRITEDATA option.  */

  /* get it! */
  curl_easy_perform(curl_handle);

  /* close the header file */
  fclose(headerfile);

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  return 0;
}