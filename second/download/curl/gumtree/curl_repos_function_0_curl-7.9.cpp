int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res;

#ifdef MALLOCDEBUG
  /* this sends all memory debug messages to a specified logfile */
  curl_memdebug("memdump");
#endif

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);

    /* get the first document */
    curl_easy_setopt(curl, CURLOPT_URL, "http://curl.haxx.se/");
    res = curl_easy_perform(curl);

    /* get another document from the same server using the same
       connection */
    curl_easy_setopt(curl, CURLOPT_URL, "http://curl.haxx.se/docs/");
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  return 0;
}