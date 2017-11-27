static int wg_callback_init (struct wg_callback *cb)
{
    struct addrinfo ai_hints;
    struct addrinfo *ai_list;
    struct addrinfo *ai_ptr;
    cdtime_t now;
    int status;

    const char *node = cb->node ? cb->node : WG_DEFAULT_NODE;
    const char *service = cb->service ? cb->service : WG_DEFAULT_SERVICE;
    const char *protocol = cb->protocol ? cb->protocol : WG_DEFAULT_PROTOCOL;

    char connerr[1024] = "";

    if (cb->sock_fd > 0)
        return (0);

    /* Don't try to reconnect too often. By default, one reconnection attempt
     * is made per second. */
    now = cdtime ();
    if ((now - cb->last_connect_time) < WG_MIN_RECONNECT_INTERVAL)
        return (EAGAIN);
    cb->last_connect_time = now;

    memset (&ai_hints, 0, sizeof (ai_hints));
#ifdef AI_ADDRCONFIG
    ai_hints.ai_flags |= AI_ADDRCONFIG;
#endif
    ai_hints.ai_family = AF_UNSPEC;

    if (0 == strcasecmp ("tcp", protocol))
        ai_hints.ai_socktype = SOCK_STREAM;
    else
        ai_hints.ai_socktype = SOCK_DGRAM;

    ai_list = NULL;

    status = getaddrinfo (node, service, &ai_hints, &ai_list);
    if (status != 0)
    {
        ERROR ("write_graphite plugin: getaddrinfo (%s, %s, %s) failed: %s",
                node, service, protocol, gai_strerror (status));
        return (-1);
    }

    assert (ai_list != NULL);
    for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
    {
        cb->sock_fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype,
                ai_ptr->ai_protocol);
        if (cb->sock_fd < 0) {
            char errbuf[1024];
            snprintf (connerr, sizeof (connerr), "failed to open socket: %s",
                    sstrerror (errno, errbuf, sizeof (errbuf)));
            continue;
        }

        status = connect (cb->sock_fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
        if (status != 0)
        {
            char errbuf[1024];
            snprintf (connerr, sizeof (connerr), "failed to connect to remote "
                    "host: %s", sstrerror (errno, errbuf, sizeof (errbuf)));
            close (cb->sock_fd);
            cb->sock_fd = -1;
            continue;
        }

        break;
    }

    freeaddrinfo (ai_list);

    if (cb->sock_fd < 0)
    {
        if (connerr[0] == '\0')
            /* this should not happen but try to get a message anyway */
            sstrerror (errno, connerr, sizeof (connerr));
        c_complain (LOG_ERR, &cb->init_complaint,
                  "write_graphite plugin: Connecting to %s:%s via %s failed. "
                  "The last error was: %s", node, service, protocol, connerr);
        return (-1);
    }
    else
    {
        c_release (LOG_INFO, &cb->init_complaint,
                "write_graphite plugin: Successfully connected to %s:%s via %s.",
                node, service, protocol);
    }

    wg_reset_buffer (cb);

    return (0);
}