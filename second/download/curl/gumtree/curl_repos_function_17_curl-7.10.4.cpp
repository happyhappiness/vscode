void *curl_thread(void *ptr)
{
  CURL *curl;
  CURLcode res;
  FILE *outfile;
  gchar *url = ptr;
  
  curl = curl_easy_init();
  if(curl)
  {
    outfile = fopen("/tmp/test.curl", "w");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FILE, outfile);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, my_read_func);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, Bar);
    
    res = curl_easy_perform(curl);

    fclose(outfile);
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return NULL;
}