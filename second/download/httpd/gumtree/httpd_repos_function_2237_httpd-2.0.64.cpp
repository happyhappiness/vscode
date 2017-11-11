static apr_status_t receive_from_other_child(void **csd, ap_listen_rec *lr,
                                             apr_pool_t *ptrans)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;
    char buffer[HUGE_STRING_LEN * 2], *headers, *body;
    int headerslen, bodylen;
    struct iovec iov;
    int ret, dp;
    apr_os_sock_t sd;
    apr_bucket_alloc_t *alloc = apr_bucket_alloc_create(ptrans);
    apr_bucket_brigade *bb = apr_brigade_create(ptrans, alloc);
    apr_bucket *bucket;

    apr_os_sock_get(&sd, lr->sd);

    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    cmsg = apr_palloc(ptrans, sizeof(*cmsg) + sizeof(sd));
    cmsg->cmsg_len = sizeof(*cmsg) + sizeof(sd);
    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg->cmsg_len;

    ret = recvmsg(sd, &msg, 0);

    memcpy(&dp, CMSG_DATA(cmsg), sizeof(dp));

    *csd = NULL; /* tell apr_os_sock_put() to allocate new apr_socket_t */
    apr_os_sock_put((apr_socket_t **)csd, &dp, ptrans);

    bucket = apr_bucket_eos_create(alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);
    bucket = apr_bucket_socket_create(*csd, alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);

    body = strchr(iov.iov_base, 0);
    if (!body) {
        return 1;
    }

    body++;
    bodylen = strlen(body);

    headers = iov.iov_base;
    headerslen = body - headers;

    bucket = apr_bucket_heap_create(body, bodylen, NULL, alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);
    bucket = apr_bucket_heap_create(headers, headerslen, NULL, alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);

    apr_pool_userdata_set(bb, "PERCHILD_SOCKETS", NULL, ptrans);

    return 0;
}