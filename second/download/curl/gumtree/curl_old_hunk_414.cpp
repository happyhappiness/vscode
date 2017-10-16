    /* Send the request. Real applications should check the iolen
     * to see if all the request has been sent */
    res = curl_easy_send(curl, request, strlen(request), &iolen);

    if(CURLE_OK != res)
    {
      printf("Error: %s\n", strerror(res));
      return 1;
    }
    puts("Reading response.");

    /* read the response */
    for(;;)
