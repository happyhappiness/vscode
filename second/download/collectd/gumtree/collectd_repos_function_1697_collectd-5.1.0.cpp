static int wg_callback_init (struct wg_callback *cb)
{
    struct addrinfo ai_hints;
    struct addrinfo *ai_list;
    struct addrinfo *ai_ptr;
    int status;

    const char *node = cb->node ? cb->node : WG_DEFAULT_NODE;
    const char *service = cb->service ? cb->service : WG_DEFAULT_SERVICE;

    if (cb->sock_fd > 0)
        return (0);

    memset (&ai_hints, 0, sizeof (ai_hints));
#ifdef AI_ADDRCONFIG
    ai_hints.ai_flags |= AI_ADDRCONFIG;
#endif
    ai_hints.ai_family = AF_UNSPEC;
    ai_hints.ai_socktype = SOCK_STREAM;

    ai_list = NULL;

    status = getaddrinfo (node, service, &ai_hints, &ai_list);
    if (status != 0)
    {
        ERROR ("write_graphite plugin: getaddrinfo (%s, %s) failed: %s",
                node, service, gai_strerror (status));
        return (-1);
    }

    assert (ai_list != NULL);
    for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
    {
        cb->sock_fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype,
                ai_ptr->ai_protocol);
        if (cb->sock_fd < 0)
            continue;

        status = connect (cb->sock_fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
        if (status != 0)
        {
            close (cb->sock_fd);
            cb->sock_fd = -1;
            continue;
        }

        break;
    }

    freeaddrinfo (ai_list);

    if (cb->sock_fd < 0)
    {
        char errbuf[1024];
        ERROR ("write_graphite plugin: Connecting to %s:%s failed. "
                "The last error was: %s", node, service,
                sstrerror (errno, errbuf, sizeof (errbuf)));
        close (cb->sock_fd);
        return (-1);
    }

    wg_reset_buffer (cb);

    return (0);
}