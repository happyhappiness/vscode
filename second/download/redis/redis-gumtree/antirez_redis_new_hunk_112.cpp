     * as this would add latency to every connect. Otherwise a more sensible
     * route could be: Use IPv6 if both addresses are available and there is IPv6
     * connectivity. */
    if ((rv = getaddrinfo(c->tcp.host,_port,&hints,&servinfo)) != 0) {
         hints.ai_family = AF_INET6;
         if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
            __redisSetError(c,REDIS_ERR_OTHER,gai_strerror(rv));
            return REDIS_ERR;
        }
    }
    for (p = servinfo; p != NULL; p = p->ai_next) {
addrretry:
        if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
            continue;

        c->fd = s;
        if (redisSetBlocking(c,0) != REDIS_OK)
            goto error;
        if (c->tcp.source_addr) {
            int bound = 0;
            /* Using getaddrinfo saves us from self-determining IPv4 vs IPv6 */
            if ((rv = getaddrinfo(c->tcp.source_addr, NULL, &hints, &bservinfo)) != 0) {
                char buf[128];
                snprintf(buf,sizeof(buf),"Can't get addr: %s",gai_strerror(rv));
                __redisSetError(c,REDIS_ERR_OTHER,buf);
                goto error;
            }

            if (reuseaddr) {
                n = 1;
                if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*) &n,
                               sizeof(n)) < 0) {
                    goto error;
                }
            }

            for (b = bservinfo; b != NULL; b = b->ai_next) {
                if (bind(s,b->ai_addr,b->ai_addrlen) != -1) {
                    bound = 1;
