    if (is_ssl && ssl_info) {
        printf("SSL/TLS Protocol:       %s\n", ssl_info);
    }
#endif
    printf("\n");
    printf("Document Path:          %s\n", path);
    if (nolength)
        printf("Document Length:        Variable\n");
    else
        printf("Document Length:        %" APR_SIZE_T_FMT " bytes\n", doclen);
    printf("\n");
    printf("Concurrency Level:      %d\n", concurrency);
    printf("Time taken for tests:   %.3f seconds\n", timetaken);
    printf("Complete requests:      %d\n", done);
    printf("Failed requests:        %d\n", bad);
    if (bad)
        printf("   (Connect: %d, Receive: %d, Length: %d, Exceptions: %d)\n",
            err_conn, err_recv, err_length, err_except);
    if (epipe)
        printf("Write errors:           %d\n", epipe);
    if (err_response)
        printf("Non-2xx responses:      %d\n", err_response);
    if (keepalive)
        printf("Keep-Alive requests:    %d\n", doneka);
    printf("Total transferred:      %" APR_INT64_T_FMT " bytes\n", totalread);
    if (send_body)
