int main(void)
{
  CURL *curl;
  CURLcode res;
  /* Minimalistic http request */
  const char *request = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";
  curl_socket_t sockfd; /* socket */
  long sockextr;
  size_t iolen;
  curl_off_t nread;

  /* A general note of caution here: if you're using curl_easy_recv() or
     curl_easy_send() to implement HTTP or _any_ other protocol libcurl
     supports "natively", you're doing it wrong and you should stop.

     This example uses HTTP only to show how to use this API, it does not
     suggest that writing an application doing this is sensible.
  */

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    /* Do not do the transfer - only connect to host */
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    res = curl_easy_perform(curl);

    if(CURLE_OK != res) {
      printf("Error: %s\n", strerror(res));
      return 1;
    }

    /* Extract the socket from the curl handle - we'll need it for waiting.
     * Note that this API takes a pointer to a 'long' while we use
     * curl_socket_t for sockets otherwise.
     */
    res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr);

    if(CURLE_OK != res) {
      printf("Error: %s\n", curl_easy_strerror(res));
      return 1;
    }

    sockfd = (curl_socket_t)sockextr;

    /* wait for the socket to become ready for sending */
    if(!wait_on_socket(sockfd, 0, 60000L)) {
      printf("Error: timeout.\n");
      return 1;
    }

    puts("Sending request.");
    /* Send the request. Real applications should check the iolen
     * to see if all the request has been sent */
    res = curl_easy_send(curl, request, strlen(request), &iolen);

    if(CURLE_OK != res) {
      printf("Error: %s\n", curl_easy_strerror(res));
      return 1;
    }
    puts("Reading response.");

    /* read the response */
    for(;;) {
      char buf[1024];

      wait_on_socket(sockfd, 1, 60000L);
      res = curl_easy_recv(curl, buf, 1024, &iolen);

      if(CURLE_OK != res)
        break;

      nread = (curl_off_t)iolen;

      printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n", nread);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}