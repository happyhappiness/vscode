  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    /* Do not do the transfer - only connect to host */
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      printf("Error: %s\n", curl_easy_strerror(res));
      return 1;
    }

    /* Extract the socket from the curl handle - we'll need it for waiting. */
    res = curl_easy_getinfo(curl, CURLINFO_ACTIVESOCKET, &sockfd);

    if(res != CURLE_OK) {
      printf("Error: %s\n", curl_easy_strerror(res));
      return 1;
    }

    printf("Sending request.\n");

    do {
      /* Warning: This example program may loop indefinitely.
       * A production-quality program must define a timeout and exit this loop
       * as soon as the timeout has expired. */
      size_t nsent;
      do {
        nsent = 0;
        res = curl_easy_send(curl, request + nsent_total,
            request_len - nsent_total, &nsent);
        nsent_total += nsent;

        if(res == CURLE_AGAIN && !wait_on_socket(sockfd, 0, 60000L)) {
          printf("Error: timeout.\n");
          return 1;
        }
      } while(res == CURLE_AGAIN);

      if(res != CURLE_OK) {
        printf("Error: %s\n", curl_easy_strerror(res));
        return 1;
      }

      printf("Sent %" CURL_FORMAT_CURL_OFF_T " bytes.\n",
        (curl_off_t)nsent);

    } while(nsent_total < request_len);

    printf("Reading response.\n");

    for(;;) {
      /* Warning: This example program may loop indefinitely (see above). */
      char buf[1024];
      size_t nread;
      do {
        nread = 0;
        res = curl_easy_recv(curl, buf, sizeof(buf), &nread);

        if(res == CURLE_AGAIN && !wait_on_socket(sockfd, 1, 60000L)) {
          printf("Error: timeout.\n");
          return 1;
        }
      } while(res == CURLE_AGAIN);

      if(res != CURLE_OK) {
        printf("Error: %s\n", curl_easy_strerror(res));
        break;
      }

      if(nread == 0) {
        /* end of the response */
        break;
      }

      printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n",
        (curl_off_t)nread);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
