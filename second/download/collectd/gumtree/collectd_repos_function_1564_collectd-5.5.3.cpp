static int cconn_prepare(struct cconn *io, struct pollfd* fds)
{
    int ret;
    if(io->request_type == ASOK_REQ_NONE)
    {
        /* The request has already been serviced. */
        return 0;
    }
    else if((io->request_type == ASOK_REQ_DATA) && (io->d->ds_num == 0))
    {
        /* If there are no counters to report on, don't bother
         * connecting */
        return 0;
    }

    switch (io->state)
    {
        case CSTATE_UNCONNECTED:
            ret = cconn_connect(io);
            if(ret > 0)
            {
                return -ret;
            }
            else if(ret < 0)
            {
                return ret;
            }
            fds->fd = io->asok;
            fds->events = POLLOUT;
            return 1;
        case CSTATE_WRITE_REQUEST:
            fds->fd = io->asok;
            fds->events = POLLOUT;
            return 1;
        case CSTATE_READ_VERSION:
        case CSTATE_READ_AMT:
        case CSTATE_READ_JSON:
            fds->fd = io->asok;
            fds->events = POLLIN;
            return 1;
        default:
            ERROR("ceph plugin: cconn_prepare(name=%s) got to illegal state "
                "on line %d", io->d->name, __LINE__);
            return -EDOM;
    }
}