static apr_status_t send_socket(apr_pool_t *p,
                                apr_socket_t *s,
                                apr_socket_t *outbound)
{
    apr_status_t rv;
    apr_os_sock_t rawsock;
    apr_os_sock_t srawsock;
    struct msghdr msg;
    struct cmsghdr *cmsg;
    struct iovec iov;
    char b = '\0';

    rv = apr_os_sock_get(&rawsock, outbound);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_os_sock_get(&srawsock, s);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    memset(&msg, 0, sizeof(msg));

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    iov.iov_base = &b;
    iov.iov_len = 1;

    cmsg = apr_palloc(p, sizeof(*cmsg) + sizeof(rawsock));
    cmsg->cmsg_len = sizeof(*cmsg) + sizeof(rawsock);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;

    memcpy(CMSG_DATA(cmsg), &rawsock, sizeof(rawsock));

    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg->cmsg_len;

    rv = sendmsg(srawsock, &msg, 0);

    if (rv == -1) {
        return errno;
    }


    return APR_SUCCESS;
}