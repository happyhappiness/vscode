static int
process_request(cachemgr_request * req)
{

    char ipbuf[MAX_IPSTRLEN];
    struct addrinfo *AI = NULL;
    Ip::Address S;
    int s;
    int l;

    static char buf[2 * 1024];

    if (req == NULL) {
        auth_html(CACHEMGR_HOSTNAME, CACHE_HTTP_PORT, "");
        return 1;
    }

    if (req->hostname == NULL) {
        req->hostname = xstrdup(CACHEMGR_HOSTNAME);
    }

    if (req->port == 0) {
        req->port = CACHE_HTTP_PORT;
    }

    if (req->action == NULL) {
        req->action = xstrdup("");
    }

    if (strcmp(req->action, "authenticate") == 0) {
        auth_html(req->hostname, req->port, req->user_name);
        return 0;
    }

    if (!check_target_acl(req->hostname, req->port)) {
        snprintf(buf, sizeof(buf), "target %s:%d not allowed in cachemgr.conf\n", req->hostname, req->port);
        error_html(buf);
        return 1;
    }

    S = *gethostbyname(req->hostname);

    if ( !S.isAnyAddr() ) {
        (void) 0;
    } else if ((S = req->hostname))
        (void) 0;
    else {
        snprintf(buf, sizeof(buf), "Unknown host: %s\n", req->hostname);
        error_html(buf);
        return 1;
    }

    S.port(req->port);

    S.getAddrInfo(AI);

#if USE_IPV6
    if ((s = socket( AI->ai_family, SOCK_STREAM, 0)) < 0) {
#else
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
#endif
        snprintf(buf, sizeof(buf), "socket: %s\n", xstrerror());
        error_html(buf);
        Ip::Address::FreeAddrInfo(AI);
        return 1;
    }

    if (connect(s, AI->ai_addr, AI->ai_addrlen) < 0) {
        snprintf(buf, sizeof(buf), "connect %s: %s\n",
                 S.toUrl(ipbuf,MAX_IPSTRLEN),
                 xstrerror());
        error_html(buf);
        Ip::Address::FreeAddrInfo(AI);
        close(s);
        return 1;
    }

    Ip::Address::FreeAddrInfo(AI);

    l = snprintf(buf, sizeof(buf),
                 "GET cache_object://%s/%s%s%s HTTP/1.0\r\n"
                 "User-Agent: cachemgr.cgi/%s\r\n"
                 "Accept: */*\r\n"
                 "%s"			/* Authentication info or nothing */
                 "\r\n",
                 req->hostname,
                 req->action,
                 req->workers? "?workers=" : (req->processes ? "?processes=" : ""),
                 req->workers? req->workers : (req->processes ? req->processes: ""),
                 VERSION,
                 make_auth_header(req));
    if (write(s, buf, l) < 0) {
        fprintf(stderr,"ERROR: (%d) writing request: '%s'\n", errno, buf);
    } else {
        debug("wrote request: '%s'\n", buf);
    }
    return read_reply(s, req);
}

int
main(int argc, char *argv[])
{
    char *s;
    cachemgr_request *req;

    now = time(NULL);
#if _SQUID_WINDOWS_

    Win32SockInit();
    atexit(Win32SockCleanup);
    _setmode( _fileno( stdin ), _O_BINARY );
    _setmode( _fileno( stdout ), _O_BINARY );
    _fmode = _O_BINARY;

    if ((s = strrchr(argv[0], '\\')))
#else

    if ((s = strrchr(argv[0], '/')))
#endif

        progname = xstrdup(s + 1);
    else
        progname = xstrdup(argv[0]);

    if ((s = getenv("SCRIPT_NAME")) != NULL)
        script_name = xstrdup(s);

    char **args = argv;
    while (argc > 1 && args[1][0] == '-') {
//        const char *value = "";
        char option = args[1][1];
        switch (option) {
        case 'd':
            debug_enabled = 1;
            break;
        default:
#if 0 // unused for now.
            if (strlen(args[1]) > 2) {
                value = args[1] + 2;
            } else if (argc > 2) {
                value = args[2];
                ++args;
                --argc;
            } else
                value = "";
#endif
            break;
        }
        ++args;
        --argc;
    }

    req = read_request();

    return process_request(req);
}

static char *
read_post_request(void)
{
    char *s;

    if ((s = getenv("REQUEST_METHOD")) == NULL)
        return NULL;

    if (0 != strcasecmp(s, "POST"))
        return NULL;

    if ((s = getenv("CONTENT_LENGTH")) == NULL)
        return NULL;

    if (*s == '-') // negative length content huh?
        return NULL;

    uint64_t len;

    char *endptr = s+ strlen(s);
    if ((len = strtoll(s, &endptr, 10)) <= 0)
        return NULL;

    // limit the input to something reasonable.
    // 4KB should be enough for the GET/POST data length, but may be extended.
    size_t bufLen = (len < 4096 ? len : 4095);
    char *buf = (char *)xmalloc(bufLen + 1);

    size_t readLen = fread(buf, 1, bufLen, stdin);
    if (readLen == 0) {
        xfree(buf);
        return NULL;
    }
    buf[readLen] = '\0';
    len -= readLen;

    // purge the remainder of the request entity
    while (len > 0 && readLen) {
        char temp[65535];
        readLen = fread(temp, 1, 65535, stdin);
        len -= readLen;
    }

    return buf;
}

static char *
read_get_request(void)
{
    char *s;

    if ((s = getenv("QUERY_STRING")) == NULL)
        return NULL;

    return xstrdup(s);
}

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

#if _SQUID_WINDOWS_

    if (strlen(buf) == 0 || strlen(buf) == 4000)
#else

    if (strlen(buf) == 0)
#endif
    {
        xfree(buf);
        return NULL;
    }

    req = (cachemgr_request *)xcalloc(1, sizeof(cachemgr_request));

    for (s = strtok(buf, "&"); s != NULL; s = strtok(NULL, "&")) {
        t = xstrdup(s);

        if ((q = strchr(t, '=')) == NULL)
            continue;

        *q = '\0';
        ++q;

        rfc1738_unescape(t);

        rfc1738_unescape(q);

        if (0 == strcmp(t, "server") && strlen(q))
            req->server = xstrdup(q);
        else if (0 == strcmp(t, "host") && strlen(q))
            req->hostname = xstrdup(q);
        else if (0 == strcmp(t, "port") && strlen(q))
            req->port = atoi(q);
        else if (0 == strcmp(t, "user_name") && strlen(q))
            req->user_name = xstrdup(q);
        else if (0 == strcmp(t, "passwd") && strlen(q))
            req->passwd = xstrdup(q);
        else if (0 == strcmp(t, "auth") && strlen(q))
            req->pub_auth = xstrdup(q), decode_pub_auth(req);
        else if (0 == strcmp(t, "operation"))
            req->action = xstrdup(q);
        else if (0 == strcmp(t, "workers") && strlen(q))
            req->workers = xstrdup(q);
        else if (0 == strcmp(t, "processes") && strlen(q))
            req->processes = xstrdup(q);
        safe_free(t);
    }

    if (req->server && !req->hostname) {
        char *p;
        req->hostname = strtok(req->server, ":");

        if ((p = strtok(NULL, ":")))
            req->port = atoi(p);
    }

    make_pub_auth(req);
    debug("cmgr: got req: host: '%s' port: %d uname: '%s' passwd: '%s' auth: '%s' oper: '%s' workers: '%s' processes: '%s'\n",
          safe_str(req->hostname), req->port, safe_str(req->user_name), safe_str(req->passwd), safe_str(req->pub_auth), safe_str(req->action), safe_str(req->workers), safe_str(req->processes));
    return req;
}

/* Routines to support authentication */

/*
 * Encodes auth info into a "public" form.
 * Currently no powerful encryption is used.
 */
static void
make_pub_auth(cachemgr_request * req)
{
    static char buf[1024];
    safe_free(req->pub_auth);
    debug("cmgr: encoding for pub...\n");

    if (!req->passwd || !strlen(req->passwd))
        return;

    /* host | time | user | passwd */
    const int bufLen = snprintf(buf, sizeof(buf), "%s|%d|%s|%s",
                                req->hostname,
                                (int) now,
                                req->user_name ? req->user_name : "",
                                req->passwd);
    debug("cmgr: pre-encoded for pub: %s\n", buf);

    const int encodedLen = base64_encode_len(bufLen);
    req->pub_auth = (char *) xmalloc(encodedLen);
    base64_encode_str(req->pub_auth, encodedLen, buf, bufLen);
    debug("cmgr: encoded: '%s'\n", req->pub_auth);
}

static void
decode_pub_auth(cachemgr_request * req)
{
    char *buf;
    const char *host_name;
    const char *time_str;
    const char *user_name;
    const char *passwd;

    debug("cmgr: decoding pub: '%s'\n", safe_str(req->pub_auth));
    safe_free(req->passwd);

    if (!req->pub_auth || strlen(req->pub_auth) < 4 + strlen(safe_str(req->hostname)))
        return;

    const int decodedLen = base64_decode_len(req->pub_auth);
    buf = (char*)xmalloc(decodedLen);
    base64_decode(buf, decodedLen, req->pub_auth);

    debug("cmgr: length ok\n");

    /* parse ( a lot of memory leaks, but that is cachemgr style :) */
    if ((host_name = strtok(buf, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded host: '%s'\n", host_name);

    if ((time_str = strtok(NULL, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded time: '%s' (now: %d)\n", time_str, (int) now);

    if ((user_name = strtok(NULL, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded uname: '%s'\n", user_name);

    if ((passwd = strtok(NULL, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded passwd: '%s'\n", passwd);

    /* verify freshness and validity */
    if (atoi(time_str) + passwd_ttl < now) {
        xfree(buf);
        return;
    }

    if (strcasecmp(host_name, req->hostname)) {
        xfree(buf);
        return;
    }

    debug("cmgr: verified auth. info.\n");

    /* ok, accept */
    safe_free(req->user_name);

    req->user_name = xstrdup(user_name);

    req->passwd = xstrdup(passwd);

    xfree(buf);
}

static void
reset_auth(cachemgr_request * req)
{
    safe_free(req->passwd);
    safe_free(req->pub_auth);
}

static const char *
make_auth_header(const cachemgr_request * req)
{
    static char buf[1024];
    size_t stringLength = 0;

    if (!req->passwd)
        return "";

    int bufLen = snprintf(buf, sizeof(buf), "%s:%s",
                          req->user_name ? req->user_name : "",
                          req->passwd);

    int encodedLen = base64_encode_len(bufLen);
    if (encodedLen <= 0)
        return "";

    char *str64 = static_cast<char*>(xmalloc(encodedLen));
    base64_encode_str(str64, encodedLen, buf, bufLen);

    stringLength += snprintf(buf, sizeof(buf), "Authorization: Basic %s\r\n", str64);

    assert(stringLength < sizeof(buf));

    snprintf(&buf[stringLength], sizeof(buf) - stringLength, "Proxy-Authorization: Basic %s\r\n", str64);

    xfree(str64);
    return buf;
}

static int
check_target_acl(const char *hostname, int port)
{
    char config_line[BUFSIZ];
    FILE *fp = NULL;
    int ret = 0;
    fp = fopen("cachemgr.conf", "r");

    if (fp == NULL)
        fp = fopen(DEFAULT_CACHEMGR_CONFIG, "r");

    if (fp == NULL) {
#ifdef CACHEMGR_HOSTNAME_DEFINED

        if (strcmp(hostname, CACHEMGR_HOSTNAME) == 0 && port == CACHE_HTTP_PORT)
            return 1;

#else

        if (strcmp(hostname, "localhost") == 0)
            return 1;

        if (strcmp(hostname, getfullhostname()) == 0)
            return 1;

#endif

        return 0;
    }

    while (fgets(config_line, BUFSIZ, fp)) {
        char *token = NULL;
        strtok(config_line, " \r\n\t");

        if (config_line[0] == '#')
            continue;

        if (config_line[0] == '\0')
            continue;

        if ((token = strtok(config_line, ":")) == NULL)
            continue;

#if HAVE_FNMATCH_H

        if (fnmatch(token, hostname, 0) != 0)
            continue;

#else

        if (strcmp(token, hostname) != 0)
            continue;

#endif

        if ((token = strtok(NULL, ":")) != NULL) {
            int i;

            if (strcmp(token, "*") == 0)

                ;   /* Wildcard port specification */
            else if (strcmp(token, "any") == 0)

                ;   /* Wildcard port specification */
            else if (sscanf(token, "%d", &i) != 1)
                continue;

            else if (i != port)
                continue;
        } else if (port != CACHE_HTTP_PORT)
            continue;

        ret = 1;

        break;
    }

    fclose(fp);
    return ret;
}