    struct cmsghdr *cmsg;
    char sockname[80];
    struct iovec iov;
    int ret, dp;
    apr_os_sock_t sd;

    apr_os_sock_get(&sd, lr->sd);

    iov.iov_base = sockname;
    iov.iov_len = 80;

    msg.msg_name = NULL;
