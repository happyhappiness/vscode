
static apr_status_t receive_from_other_child(void **csd, ap_listen_rec *lr,
                                             apr_pool_t *ptrans)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;
    char sockname[80];
    struct iovec iov;
    int ret, dp;
    apr_os_sock_t sd;

    ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, ptrans,
                 "trying to receive request from other child");

    apr_os_sock_get(&sd, lr->sd);

    iov.iov_base = sockname;
    iov.iov_len = 80;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    cmsg = apr_palloc(ptrans, sizeof(*cmsg) + sizeof(sd));
    cmsg->cmsg_len = sizeof(*cmsg) + sizeof(sd);
    msg.msg_control = (caddr_t)cmsg;
    msg.msg_controllen = cmsg->cmsg_len;
    msg.msg_flags = 0;
    
    ret = recvmsg(sd, &msg, 0);

    memcpy(&dp, CMSG_DATA(cmsg), sizeof(dp));

    apr_os_sock_put((apr_socket_t **)csd, &dp, ptrans);
    return 0;
}

/* idle_thread_count should be incremented before starting a worker_thread */

static void *worker_thread(apr_thread_t *thd, void *arg)
