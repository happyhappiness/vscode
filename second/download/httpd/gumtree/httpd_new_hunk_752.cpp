{
    apr_interval_time_t timetakenusec;
    float timetaken;

    endtime = apr_time_now();
    timetakenusec = endtime - start;
    timetaken = ((float)apr_time_sec(timetakenusec)) +
        ((float)apr_time_usec(timetakenusec)) / 1000000.0F;
    
    printf("\n\n");
    printf("Server Software:        %s\n", servername);
    printf("Server Hostname:        %s\n", hostname);
    printf("Server Port:            %hd\n", port);
    printf("\n");
    printf("Document Path:          %s\n", path);
    printf("Document Length:        %" APR_SIZE_T_FMT " bytes\n", doclen);
    printf("\n");
    printf("Concurrency Level:      %d\n", concurrency);
    printf("Time taken for tests:   %ld.%03ld seconds\n",
           (long) apr_time_sec(timetakenusec),
           (long) apr_time_usec(timetakenusec));
    printf("Complete requests:      %ld\n", done);
    printf("Failed requests:        %ld\n", bad);
    if (bad)
	printf("   (Connect: %d, Length: %d, Exceptions: %d)\n",
	       err_conn, err_length, err_except);
    printf("Write errors:           %ld\n", epipe);
