    stats = malloc(requests * sizeof(struct data));

    FD_ZERO(&readbits);
    FD_ZERO(&writebits);

    /* setup request */
    sprintf(request, "GET %s HTTP/1.0\r\n"
                     "User-Agent: ApacheBench/%s\r\n"
                     "%s"
                     "Host: %s\r\n"
                     "Accept: */*\r\n"
                     "\r\n", 
                     path, 
                     VERSION,
                     keepalive ? "Connection: Keep-Alive\r\n" : "", 
                     hostname);

    reqlen = strlen(request);

    /* ok - lets start */
    gettimeofday(&start, 0);

    /* initialise lots of requests */
    for (i = 0; i < concurrency; i++)
        start_connect(&con[i]);
