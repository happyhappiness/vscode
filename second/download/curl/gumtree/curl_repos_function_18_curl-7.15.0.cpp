int main(void)
{
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile={
    "curl.tar.gz", /* name to store the file as if succesful */
    NULL
  };

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    /*
     * Get curl 7.9.2 from sunet.se's FTP site. curl 7.9.2 is most likely not
     * present there by the time you read this, so you'd better replace the
     * URL with one that works!
     */
    curl_easy_setopt(curl, CURLOPT_URL,
                     "ftp://ftp.sunet.se/pub/www/utilities/curl/curl-7.9.2.tar.gz");
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    if(CURLE_OK != res) {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }
  }

  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */

  curl_global_cleanup();

  return 0;
}