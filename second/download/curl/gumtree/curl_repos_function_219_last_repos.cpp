void *pull_one_url(void *NaN)
{
  CURL *curl;
  CURLcode res;
  gchar *http;
  FILE *outfile;

  /* Stop threads from entering unless j is incremented */
  pthread_mutex_lock(&lock);
  while(j < num_urls) {
    printf("j = %d\n", j);

    http =
      g_strdup_printf("xoap.weather.com/weather/local/%s?cc=*&dayf=5&unit=i\n",
                      urls[j]);

    printf("http %s", http);

    curl = curl_easy_init();
    if(curl) {

      outfile = fopen(urls[j], "wb");

      /* Set the URL and transfer type */
      curl_easy_setopt(curl, CURLOPT_URL, http);

      /* Write to the file */
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file);

      j++;  /* critical line */
      pthread_mutex_unlock(&lock);

      res = curl_easy_perform(curl);

      fclose(outfile);
      printf("fclose\n");

      curl_easy_cleanup(curl);
    }
    g_free(http);

    /* Adds more latency, testing the mutex.*/
    sleep(1);

  } /* end while */
  return NULL;
}