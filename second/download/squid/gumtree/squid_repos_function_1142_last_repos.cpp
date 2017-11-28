static unsigned int __stdcall
ipc_thread_2(void *in_params)
{
    int x;

    struct thread_params *params = (struct thread_params *) in_params;
    int type = params->type;
    int rfd = params->rfd;
    int send_fd = params->send_fd;
    char *prog = xstrdup(params->prog);
    pid_t pid = params->pid;
    const size_t bufSz = 8192;
    char *buf2 = (char *)xcalloc(1, bufSz);

    for (;;) {
        if (type == IPC_TCP_SOCKET)
            x = read(rfd, buf2, bufSz-1);
        else
            x = recv(rfd, (void *)buf2, bufSz-1, 0);

        if ((x <= 0 && type == IPC_TCP_SOCKET) ||
                (x < 0 && type == IPC_UDP_SOCKET)) {
            debugs(54, 3, "ipc(" << prog << "," << pid << "): " << x << " bytes read from " << prog << ". Exiting...");

            break;
        }

        buf2[x] = '\0';

        if (type == IPC_UDP_SOCKET && !strcmp(buf2, shutdown_string)) {
            debugs(54, 3, "ipc(" << prog << "," << pid << "): request for shutdown received. Exiting...");
            break;
        }

        if (x >= 2) {
            if ((buf2[x - 1] == '\n') && (buf2[x - 2] == '\r')) {
                buf2[x - 2] = '\n';
                buf2[x - 1] = '\0';
                --x;
            }
        }

        debugs(54, 5, "ipc(" << prog << "," << pid << "): received from child : " << rfc1738_escape_unescaped(buf2));

        x = send(send_fd, (const void *)buf2, x, 0);

        if ((x <= 0 && type == IPC_TCP_SOCKET) ||
                (x < 0 && type == IPC_UDP_SOCKET)) {
            debugs(54, 3, "ipc(" << prog << "," << pid << "): " << x << " bytes sent to parent. Exiting...");

            break;
        }
    }

    xfree(prog);
    xfree(buf2);
    return 0;
}