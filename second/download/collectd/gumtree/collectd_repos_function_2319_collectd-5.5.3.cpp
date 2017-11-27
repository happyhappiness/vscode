static int notify_systemd (void)
{
    int                  fd = -1;
    const char          *notifysocket = getenv("NOTIFY_SOCKET");
    struct sockaddr_un   su;
    struct iovec         iov;
    struct msghdr        hdr;

    if (notifysocket == NULL)
        return 0;

    if ((strchr("@/", notifysocket[0])) == NULL ||
        strlen(notifysocket) < 2)
        return 0;

    WARNING ("supervised by systemd, will signal readyness");
    if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
        WARNING ("cannot contact systemd socket %s", notifysocket);
        return 0;
    }

    bzero(&su, sizeof(su));
    su.sun_family = AF_UNIX;
    sstrncpy (su.sun_path, notifysocket, sizeof(su.sun_path));

    if (notifysocket[0] == '@')
        su.sun_path[0] = 0;

    bzero(&iov, sizeof(iov));
    iov.iov_base = "READY=1";
    iov.iov_len = strlen("READY=1");

    bzero(&hdr, sizeof(hdr));
    hdr.msg_name = &su;
    hdr.msg_namelen = offsetof(struct sockaddr_un, sun_path) +
        strlen(notifysocket);
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;

    unsetenv("NOTIFY_SOCKET");
    if (sendmsg(fd, &hdr, MSG_NOSIGNAL) < 0) {
        WARNING ("cannot send notification to systemd");
        close(fd);
        return 0;
    }
    close(fd);
    return 1;
}