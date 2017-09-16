    printf("Server Hostname:        %s\n", hostname);

    printf("Server Port:            %d\n", port);

    printf("\n");

    printf("Document Path:          %s\n", path);

    printf("Document Length:        %d bytes\n", doclen);

    printf("\n");

    printf("Concurency Level:       %d\n", concurrency);

    printf("Time taken for tests:   %d.%03d seconds\n",

           timetaken / 1000, timetaken % 1000);

    printf("Complete requests:      %d\n", done);

    printf("Failed requests:        %d\n", bad);

    if (bad)

        printf("   (Connect: %d, Length: %d, Exceptions: %d)\n",

               err_conn, err_length, err_except);

    if (keepalive)

        printf("Keep-Alive requests:    %d\n", doneka);

    printf("Total transfered:       %d bytes\n", totalread);

    printf("HTML transfered:        %d bytes\n", totalbread);



    /* avoid divide by zero */

    if (timetaken) {

        printf("Requests per seconds:   %.2f\n", 1000 * (float) (done) / timetaken);

        printf("Transfer rate:          %.2f kb/s\n",

               (float) (totalread) / timetaken);

    }



    {

        /* work out connection times */

