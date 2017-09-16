    stats = malloc(requests * sizeof(struct data));



    FD_ZERO(&readbits);

    FD_ZERO(&writebits);



    /* setup request */

    if (!posting) {

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

    }

    else {

	sprintf(request, "POST %s HTTP/1.0\r\n"

                     "User-Agent: ApacheBench/%s\r\n"

                     "%s"

                     "Host: %s\r\n"

                     "Accept: */*\r\n"

                     "Content-length: %d\r\n"

                     "Content-type: %s\r\n"

                     "\r\n", 

                     path, 

                     VERSION,

                     keepalive ? "Connection: Keep-Alive\r\n" : "", 

                     hostname, postlen, 

                     (content_type[0]) ? content_type : "text/plain");

    }



    if (verbosity >= 2) printf("INFO: POST header == \n---\n%s\n---\n", request);



    reqlen = strlen(request);



#ifdef CHARSET_EBCDIC

    ebcdic2ascii(request, request, reqlen);

#endif /*CHARSET_EBCDIC*/



    /* ok - lets start */

    gettimeofday(&start, 0);



    /* initialise lots of requests */

    for (i = 0; i < concurrency; i++)

        start_connect(&con[i]);

