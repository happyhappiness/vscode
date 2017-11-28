int
main(int argc, char **argv)
{
    struct sockaddr_in salocal;
    struct sockaddr_in saremote;
    struct servent *svp;
    unsigned short svc_port;
    char username[MAXPWNAM];
    char passwd[MAXPASS];
    char *ptr;
    char authstring[MAXLINE];
    const char *cfname = NULL;
    int err = 0;
    socklen_t salen;
    int c;

    while ((c = getopt(argc, argv, "h:p:f:w:i:t:")) != -1) {
        switch (c) {
        case 'f':
            cfname = optarg;
            break;
        case 'h':
            strcpy(server, optarg);
            break;
        case 'p':
            strcpy(svc_name, optarg);
            break;
        case 'w':
            strcpy(secretkey, optarg);
            break;
        case 'i':
            strcpy(identifier, optarg);
            break;
        case 't':
            retries = atoi(optarg);
            break;
        }
    }
    /* make standard output line buffered */
    if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)
        return 1;

    if (cfname) {
        if (rad_auth_config(cfname) < 0) {
            fprintf(stderr, "%s: can't open configuration file '%s'.\n", argv[0], cfname);
            exit(1);
        }
    }
    if (!*server) {
        fprintf(stderr, "%s: Server not specified\n", argv[0]);
        exit(1);
    }
    if (!*secretkey) {
        fprintf(stderr, "%s: Shared secret not specified\n", argv[0]);
        exit(1);
    }
#ifdef _SQUID_MSWIN_
    {
        WSADATA wsaData;
        WSAStartup(2, &wsaData);
        atexit(Win32SockCleanup);
    }
#endif
    /*
     *    Open a connection to the server.
     */
    svp = getservbyname(svc_name, "udp");
    if (svp != NULL)
        svc_port = ntohs((unsigned short) svp->s_port);
    else
        svc_port = atoi(svc_name);
    if (svc_port == 0)
        svc_port = PW_AUTH_UDP_PORT;

    /* Get the IP address of the authentication server */
    if ((auth_ipaddr = get_ipaddr(server)) == 0) {
        fprintf(stderr, "Couldn't find host %s\n", server);
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    memset(&saremote, 0, sizeof(saremote));
    saremote.sin_family = AF_INET;
    saremote.sin_addr.s_addr = htonl(auth_ipaddr);
    saremote.sin_port = htons(svc_port);

    if (connect(sockfd, (struct sockaddr *) &saremote, sizeof(saremote)) < 0) {
        perror("connect");
        exit(1);
    }
    salen = sizeof(salocal);
    if (getsockname(sockfd, (struct sockaddr *) &salocal, &salen) < 0) {
        perror("getsockname");
        exit(1);
    }
#ifdef O_NONBLOCK
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
#endif
    nas_ipaddr = ntohl(salocal.sin_addr.s_addr);
    while (fgets(authstring, MAXLINE, stdin) != NULL) {
        char *end;
        /* protect me form to long lines */
        if ((end = strchr(authstring, '\n')) == NULL) {
            err = 1;
            continue;
        }
        if (err) {
            printf("ERR\n");
            err = 0;
            continue;
        }
        if (strlen(authstring) > MAXLINE) {
            printf("ERR\n");
            continue;
        }
        /* Strip off the trailing newline */
        *end = '\0';

        /* Parse out the username and password */
        ptr = authstring;
        while (isspace((int)*ptr))
            ptr++;
        if ((end = strchr(ptr, ' ')) == NULL) {
            printf("ERR\n");	/* No password */
            continue;
        }
        *end = '\0';
        urldecode(username, ptr, MAXPWNAM);
        ptr = end + 1;
        while (isspace((int)*ptr))
            ptr++;
        urldecode(passwd, ptr, MAXPASS);

        if (authenticate(sockfd, username, passwd))
            printf("OK\n");
        else
            printf("ERR\n");
    }
    close(sockfd);
    exit(1);
}