static cachemgr_request *
read_request(void)
{
    char *buf;

    cachemgr_request *req;
    char *s;
    char *t;
    char *q;

    if ((buf = read_post_request()) != NULL)
        (void) 0;
    else if ((buf = read_get_request()) != NULL)
        (void) 0;
    else
        return NULL;

#ifdef _SQUID_MSWIN_

    if (strlen(buf) == 0 || strlen(buf) == 4000)
#else

    if (strlen(buf) == 0)
#endif
    {
        free(buf);
        return NULL;
    }

    req = (cachemgr_request *)xcalloc(1, sizeof(cachemgr_request));

    for (s = strtok(buf, "&"); s != NULL; s = strtok(NULL, "&")) {
        t = xstrdup(s);

        if ((q = strchr(t, '=')) == NULL)
            continue;

        *q++ = '\0';

        rfc1738_unescape(t);

        rfc1738_unescape(q);

        if (0 == strcasecmp(t, "server") && strlen(q))
            req->server = xstrdup(q);
        else if (0 == strcasecmp(t, "host") && strlen(q))
            req->hostname = xstrdup(q);
        else if (0 == strcasecmp(t, "port") && strlen(q))
            req->port = atoi(q);
        else if (0 == strcasecmp(t, "user_name") && strlen(q))
            req->user_name = xstrdup(q);
        else if (0 == strcasecmp(t, "passwd") && strlen(q))
            req->passwd = xstrdup(q);
        else if (0 == strcasecmp(t, "auth") && strlen(q))
            req->pub_auth = xstrdup(q), decode_pub_auth(req);
        else if (0 == strcasecmp(t, "operation"))
            req->action = xstrdup(q);
    }

    if (req->server && !req->hostname) {
        char *p;
        req->hostname = strtok(req->server, ":");

        if ((p = strtok(NULL, ":")))
            req->port = atoi(p);
    }

    make_pub_auth(req);
    debug(1) fprintf(stderr, "cmgr: got req: host: '%s' port: %d uname: '%s' passwd: '%s' auth: '%s' oper: '%s'\n",
                     safe_str(req->hostname), req->port, safe_str(req->user_name), safe_str(req->passwd), safe_str(req->pub_auth), safe_str(req->action));
    return req;
}