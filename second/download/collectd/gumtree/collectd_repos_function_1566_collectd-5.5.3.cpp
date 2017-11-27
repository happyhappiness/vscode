static int cconn_main_loop(uint32_t request_type)
{
    int i, ret, some_unreachable = 0;
    struct timeval end_tv;
    struct cconn io_array[g_num_daemons];

    DEBUG("ceph plugin: entering cconn_main_loop(request_type = %d)", request_type);

    /* create cconn array */
    memset(io_array, 0, sizeof(io_array));
    for(i = 0; i < g_num_daemons; ++i)
    {
        io_array[i].d = g_daemons[i];
        io_array[i].request_type = request_type;
        io_array[i].state = CSTATE_UNCONNECTED;
    }

    /** Calculate the time at which we should give up */
    gettimeofday(&end_tv, NULL);
    end_tv.tv_sec += CEPH_TIMEOUT_INTERVAL;

    while (1)
    {
        int nfds, diff;
        struct timeval tv;
        struct cconn *polled_io_array[g_num_daemons];
        struct pollfd fds[g_num_daemons];
        memset(fds, 0, sizeof(fds));
        nfds = 0;
        for(i = 0; i < g_num_daemons; ++i)
        {
            struct cconn *io = io_array + i;
            ret = cconn_prepare(io, fds + nfds);
            if(ret < 0)
            {
                WARNING("ceph plugin: cconn_prepare(name=%s,i=%d,st=%d)=%d",
                        io->d->name, i, io->state, ret);
                cconn_close(io);
                io->request_type = ASOK_REQ_NONE;
                some_unreachable = 1;
            }
            else if(ret == 1)
            {
                polled_io_array[nfds++] = io_array + i;
            }
        }
        if(nfds == 0)
        {
            /* finished */
            ret = 0;
            goto done;
        }
        gettimeofday(&tv, NULL);
        diff = milli_diff(&end_tv, &tv);
        if(diff <= 0)
        {
            /* Timed out */
            ret = -ETIMEDOUT;
            WARNING("ceph plugin: cconn_main_loop: timed out.");
            goto done;
        }
        RETRY_ON_EINTR(ret, poll(fds, nfds, diff));
        if(ret < 0)
        {
            ERROR("ceph plugin: poll(2) error: %d", ret);
            goto done;
        }
        for(i = 0; i < nfds; ++i)
        {
            struct cconn *io = polled_io_array[i];
            int revents = fds[i].revents;
            if(revents == 0)
            {
                /* do nothing */
            }
            else if(cconn_validate_revents(io, revents))
            {
                WARNING("ceph plugin: cconn(name=%s,i=%d,st=%d): "
                "revents validation error: "
                "revents=0x%08x", io->d->name, i, io->state, revents);
                cconn_close(io);
                io->request_type = ASOK_REQ_NONE;
                some_unreachable = 1;
            }
            else
            {
                ret = cconn_handle_event(io);
                if(ret)
                {
                    WARNING("ceph plugin: cconn_handle_event(name=%s,"
                    "i=%d,st=%d): error %d", io->d->name, i, io->state, ret);
                    cconn_close(io);
                    io->request_type = ASOK_REQ_NONE;
                    some_unreachable = 1;
                }
            }
        }
    }
    done: for(i = 0; i < g_num_daemons; ++i)
    {
        cconn_close(io_array + i);
    }
    if(some_unreachable)
    {
        DEBUG("ceph plugin: cconn_main_loop: some Ceph daemons were unreachable.");
    }
    else
    {
        DEBUG("ceph plugin: cconn_main_loop: reached all Ceph daemons :)");
    }
    return ret;
}