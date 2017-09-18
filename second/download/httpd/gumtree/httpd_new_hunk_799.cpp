
static apr_status_t receive_from_other_child(void **csd, ap_listen_rec *lr,
                                             apr_pool_t *ptrans)
{
    struct msghdr msg;
    struct cmsghdr *cmsg;
    char headers[HUGE_STRING_LEN];
    char request_body[HUGE_STRING_LEN];
    struct iovec iov[2];
    int ret, dp;
    apr_os_sock_t sd;
    apr_socket_t *unix_sd = NULL;
    apr_bucket_alloc_t *alloc = apr_bucket_alloc_create(ptrans);
    apr_bucket_brigade *bb = apr_brigade_create(ptrans, alloc);
    apr_bucket *bucket;

    apr_os_sock_get(&sd, lr->sd);

    iov[0].iov_base = headers;
    iov[0].iov_len = HUGE_STRING_LEN;
    iov[0].iov_base = request_body;
    iov[0].iov_len = HUGE_STRING_LEN;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 2;

    cmsg = apr_palloc(ptrans, sizeof(*cmsg) + sizeof(sd));
    cmsg->cmsg_len = sizeof(*cmsg) + sizeof(sd);
    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg->cmsg_len;

    ret = recvmsg(sd, &msg, 0);

    memcpy(&dp, CMSG_DATA(cmsg), sizeof(dp));

    apr_os_sock_put((apr_socket_t **)csd, &dp, ptrans);

    bucket = apr_bucket_eos_create(alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);
    bucket = apr_bucket_socket_create(*csd, alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);
    bucket = apr_bucket_heap_create(iov[1].iov_base, 
                                    iov[1].iov_len, NULL, alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);
    bucket = apr_bucket_heap_create(iov[0].iov_base, 
                                    iov[0].iov_len, NULL, alloc);
    APR_BRIGADE_INSERT_HEAD(bb, bucket);

    apr_pool_userdata_set(bb, "PERCHILD_SOCKETS", NULL, ptrans);
    return 0;
}

/* idle_thread_count should be incremented before starting a worker_thread */

static void *worker_thread(apr_thread_t *thd, void *arg)
