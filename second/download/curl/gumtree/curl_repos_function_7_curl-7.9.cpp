int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res;
  FILE *ftpfile;
  
  /* local file name to store the file as */
  ftpfile = fopen("curl.tar.gz", "wb"); /* b is binary for win */

  curl = curl_easy_init();
  if(curl) {
    /* Get curl 7.7 from sunet.se's FTP site: */
    curl_easy_setopt(curl, CURLOPT_URL,
                     "ftp://ftp.sunet.se/pub/www/utilities/curl/curl-7.7.tar.gz");
    curl_easy_setopt(curl, CURLOPT_FILE, ftpfile);
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  fclose(ftpfile); /* close the local file */

  return 0;
}