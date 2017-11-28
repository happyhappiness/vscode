static int
fqdncacheParse(fqdncache_entry *f, const char *inbuf)
{
    LOCAL_ARRAY(char, buf, DNS_INBUF_SZ);
    char *token;
    int ttl;
    const char *name = (const char *)f->hash.key;
    f->expires = squid_curtime + Config.negativeDnsTtl;
    f->flags.negcached = 1;

    if (inbuf == NULL) {
        debugs(35, DBG_IMPORTANT, "fqdncacheParse: Got <NULL> reply in response to '" << name << "'");
        f->error_message = xstrdup("Internal Error");
        return -1;
    }

    xstrncpy(buf, inbuf, DNS_INBUF_SZ);
    debugs(35, 5, "fqdncacheParse: parsing: {" << buf << "}");
    token = strtok(buf, w_space);

    if (NULL == token) {
        debugs(35, DBG_IMPORTANT, "fqdncacheParse: Got <NULL>, expecting '$name' in response to '" << name << "'");
        f->error_message = xstrdup("Internal Error");
        return -1;
    }

    if (0 == strcmp(token, "$fail")) {
        token = strtok(NULL, "\n");
        assert(NULL != token);
        f->error_message = xstrdup(token);
        return 0;
    }

    if (0 != strcmp(token, "$name")) {
        debugs(35, DBG_IMPORTANT, "fqdncacheParse: Got '" << inbuf << "', expecting '$name' in response to '" << name << "'");
        f->error_message = xstrdup("Internal Error");
        return -1;
    }

    token = strtok(NULL, w_space);

    if (NULL == token) {
        debugs(35, DBG_IMPORTANT, "fqdncacheParse: Got '" << inbuf << "', expecting TTL in response to '" << name << "'");
        f->error_message = xstrdup("Internal Error");
        return -1;
    }

    ttl = atoi(token);

    token = strtok(NULL, w_space);

    if (NULL == token) {
        debugs(35, DBG_IMPORTANT, "fqdncacheParse: Got '" << inbuf << "', expecting hostname in response to '" << name << "'");
        f->error_message = xstrdup("Internal Error");
        return -1;
    }

    f->names[0] = xstrdup(token);
    f->name_count = 1;

    if (ttl == 0 || ttl > Config.positiveDnsTtl)
        ttl = Config.positiveDnsTtl;

    if (ttl < Config.negativeDnsTtl)
        ttl = Config.negativeDnsTtl;

    f->expires = squid_curtime + ttl;

    f->flags.negcached = 0;

    return f->name_count;
}