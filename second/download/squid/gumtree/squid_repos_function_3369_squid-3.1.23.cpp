int
main(int argc, char *argv[])
{
    char buf[RECV_BUF_SIZE];

    struct sockaddr_in R;
    socklen_t len;

    struct hostent *hp = NULL;
    const char *logfile;
    char ip[4];

    for (len = 0; len < 32; len++) {
        signal(len, sig_handle);
    }


    if (argc > 1)
        logfile = argv[1];
    else
        logfile = "/tmp/recv-announce.log";

    close(1);

    if (open(logfile, O_WRONLY | O_CREAT | O_APPEND, 0660) < 0) {
        perror(logfile);
        exit(1);
    }

    close(2);
    dup(1);


    IPAddress ipa;
    chat tmp[MAX_HOSTNAMELEN];
    for (;;) {
        memset(buf, '\0', RECV_BUF_SIZE);
        memset(&R, '\0', len = sizeof(R));

        if (recvfrom(0, buf, RECV_BUF_SIZE, 0, (sockaddr *)&R, &len) < 0) {
            perror("recv");
            exit(2);
        }

        xmemcpy(ip, &R.sin_addr.s_addr, 4);
        hp = gethostbyaddr(ip, 4, AF_INET);
        ipa = R.sin_addr;
        printf("==============================================================================\n");
        printf("Received from %s [%s]\n",
               ipa.NtoA(tmp,MAX_HOSTNAMELEN),
               (hp && hp->h_name) ? hp->h_name : "Unknown");
        fputs(buf, stdout);
        fflush(stdout);
    }

    return 0;
}