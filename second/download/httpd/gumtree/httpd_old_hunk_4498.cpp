    printf("Server Hostname:        %s\n", hostname);
    printf("Server Port:            %hu\n", port);
#ifdef USE_SSL
    if (is_ssl && ssl_info) {
        printf("SSL/TLS Protocol:       %s\n", ssl_info);
    }
#endif
    printf("\n");
    printf("Document Path:          %s\n", path);
    if (nolength)
        printf("Document Length:        Variable\n");
    else
