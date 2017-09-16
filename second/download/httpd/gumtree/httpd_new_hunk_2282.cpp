           timetaken / 1000, timetaken % 1000);

    printf("Complete requests:      %d\n", done);

    printf("Failed requests:        %d\n", bad);

    if (bad)

        printf("   (Connect: %d, Length: %d, Exceptions: %d)\n",

               err_conn, err_length, err_except);

    if (err_response)

        printf("Non-2xx responses:      %d\n", err_response);

    if (keepalive)

        printf("Keep-Alive requests:    %d\n", doneka);

    printf("Total transferred:      %d bytes\n", totalread);

    if (posting)

        printf("Total POSTed:           %d\n", totalposted);

    printf("HTML transferred:       %d bytes\n", totalbread);



    /* avoid divide by zero */

    if (timetaken) {

        printf("Requests per second:    %.2f\n", 1000 * (float) (done) / timetaken);

        printf("Transfer rate:          %.2f kb/s received\n",

               (float) (totalread) / timetaken);

        if (posting) {

            printf("                        %.2f kb/s sent\n", 

       		    (float)(totalposted)/timetaken);

            printf("                        %.2f kb/s total\n", 

           	    (float)(totalread + totalposted)/timetaken);

        }

    }



    {

        /* work out connection times */

        int i;

        int totalcon = 0, total = 0;

