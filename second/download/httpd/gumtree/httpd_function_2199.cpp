static int proxy_ftp_handler(request_rec *r, proxy_worker *worker,
                             proxy_server_conf *conf, char *url,
                             const char *proxyhost, apr_port_t proxyport)
{
    apr_pool_t *p = r->pool;
    conn_rec *c = r->connection;
    proxy_conn_rec *backend;
    apr_socket_t *sock, *local_sock, *data_sock = NULL;
    apr_sockaddr_t *connect_addr = NULL;
    apr_status_t rv;
    conn_rec *origin, *data = NULL;
    apr_status_t err = APR_SUCCESS;
    apr_status_t uerr = APR_SUCCESS;
    apr_bucket_brigade *bb = apr_brigade_create(p, c->bucket_alloc);
    char *buf, *connectname;
    apr_port_t connectport;
    char buffer[MAX_STRING_LEN];
    char *ftpmessage = NULL;
    char *path, *strp, *type_suffix, *cwd = NULL;
    apr_uri_t uri;
    char *user = NULL;
/*    char *account = NULL; how to supply an account in a URL? */
    const char *password = NULL;
    int len, rc;
    int one = 1;
    char *size = NULL;
    char xfer_type = 'A'; /* after ftp login, the default is ASCII */
    int  dirlisting = 0;
#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
    apr_time_t mtime = 0L;
#endif

    /* stuff for PASV mode */
    int connect = 0, use_port = 0;
    char dates[APR_RFC822_DATE_LEN];
    int status;
    apr_pool_t *address_pool;

    /* is this for us? */
    if (proxyhost) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: declining URL %s - proxyhost %s specified:", url, proxyhost);
        return DECLINED;        /* proxy connections are via HTTP */
    }
    if (strncasecmp(url, "ftp:", 4)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: declining URL %s - not ftp:", url);
        return DECLINED;        /* only interested in FTP */
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: serving URL %s", url);


    /*
     * I: Who Do I Connect To? -----------------------
     *
     * Break up the URL to determine the host to connect to
     */

    /* we only support GET and HEAD */
    if (r->method_number != M_GET)
        return HTTP_NOT_IMPLEMENTED;

    /* We break the URL into host, port, path-search */
    if (r->parsed_uri.hostname == NULL) {
        if (APR_SUCCESS != apr_uri_parse(p, url, &uri)) {
            return ap_proxyerror(r, HTTP_BAD_REQUEST,
                apr_psprintf(p, "URI cannot be parsed: %s", url));
        }
        connectname = uri.hostname;
        connectport = uri.port;
        path = apr_pstrdup(p, uri.path);
    }
    else {
        connectname = r->parsed_uri.hostname;
        connectport = r->parsed_uri.port;
        path = apr_pstrdup(p, r->parsed_uri.path);
    }
    if (connectport == 0) {
        connectport = apr_uri_port_of_scheme("ftp");
    }
    path = (path != NULL && path[0] != '\0') ? &path[1] : "";

    type_suffix = strchr(path, ';');
    if (type_suffix != NULL)
        *(type_suffix++) = '\0';

    if (type_suffix != NULL && strncmp(type_suffix, "type=", 5) == 0
        && apr_isalpha(type_suffix[5])) {
        /* "type=d" forces a dir listing.
         * The other types (i|a|e) are directly used for the ftp TYPE command
         */
        if ( ! (dirlisting = (apr_tolower(type_suffix[5]) == 'd')))
            xfer_type = apr_toupper(type_suffix[5]);

        /* Check valid types, rather than ignoring invalid types silently: */
        if (strchr("AEI", xfer_type) == NULL)
            return ap_proxyerror(r, HTTP_BAD_REQUEST, apr_pstrcat(r->pool,
                                    "ftp proxy supports only types 'a', 'i', or 'e': \"",
                                    type_suffix, "\" is invalid.", NULL));
    }
    else {
        /* make binary transfers the default */
        xfer_type = 'I';
    }


    /*
     * The "Authorization:" header must be checked first. We allow the user
     * to "override" the URL-coded user [ & password ] in the Browsers'
     * User&Password Dialog. NOTE that this is only marginally more secure
     * than having the password travel in plain as part of the URL, because
     * Basic Auth simply uuencodes the plain text password. But chances are
     * still smaller that the URL is logged regularly.
     */
    if ((password = apr_table_get(r->headers_in, "Authorization")) != NULL
        && strcasecmp(ap_getword(r->pool, &password, ' '), "Basic") == 0
        && (password = ap_pbase64decode(r->pool, password))[0] != ':') {
        /*
         * Note that this allocation has to be made from r->connection->pool
         * because it has the lifetime of the connection.  The other
         * allocations are temporary and can be tossed away any time.
         */
        user = ap_getword_nulls(r->connection->pool, &password, ':');
        r->ap_auth_type = "Basic";
        r->user = r->parsed_uri.user = user;
    }
    else if ((user = r->parsed_uri.user) != NULL) {
        user = apr_pstrdup(p, user);
        decodeenc(user);
        if ((password = r->parsed_uri.password) != NULL) {
            char *tmp = apr_pstrdup(p, password);
            decodeenc(tmp);
            password = tmp;
        }
    }
    else {
        user = "anonymous";
        password = "apache-proxy@";
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
       "proxy: FTP: connecting %s to %s:%d", url, connectname, connectport);

    if (worker->is_address_reusable) {
        if (!worker->cp->addr) {
            if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server,
                             "proxy: FTP: lock");
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        connect_addr = worker->cp->addr;
        address_pool = worker->cp->pool;
    }
    else
        address_pool = r->pool;

    /* do a DNS lookup for the destination host */
    if (!connect_addr)
        err = apr_sockaddr_info_get(&(connect_addr),
                                    connectname, APR_UNSPEC,
                                    connectport, 0,
                                    address_pool);
    if (worker->is_address_reusable && !worker->cp->addr) {
        worker->cp->addr = connect_addr;
        if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, uerr, r->server,
                         "proxy: FTP: unlock");
        }
    }
    /*
     * get all the possible IP addresses for the destname and loop through
     * them until we get a successful connection
     */
    if (APR_SUCCESS != err) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY, apr_pstrcat(p,
                                                 "DNS lookup failure for: ",
                                                        connectname, NULL));
    }

    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, connect_addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }

    /* create space for state information */
    backend = (proxy_conn_rec *) ap_get_module_config(c->conn_config, &proxy_ftp_module);
    if (!backend) {
        status = ap_proxy_acquire_connection("FTP", &backend, worker, r->server);
        if (status != OK) {
            if (backend) {
                backend->close_on_recycle = 1;
                ap_proxy_release_connection("FTP", backend, r->server);
            }
            return status;
        }
        /* TODO: see if ftp could use determine_connection */
        backend->addr = connect_addr;
        ap_set_module_config(c->conn_config, &proxy_ftp_module, backend);
    }


    /*
     * II: Make the Connection -----------------------
     *
     * We have determined who to connect to. Now make the connection.
     */


    if (ap_proxy_connect_backend("FTP", backend, worker, r->server)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: an error occurred creating a new connection to %pI (%s)",
                     connect_addr, connectname);
        proxy_ftp_cleanup(r, backend);
        return HTTP_SERVICE_UNAVAILABLE;
    }

    if (!backend->connection) {
        status = ap_proxy_connection_create("FTP", backend, c, r->server);
        if (status != OK) {
            proxy_ftp_cleanup(r, backend);
            return status;
        }
    }

    /* Use old naming */
    origin = backend->connection;
    sock = backend->sock;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: control connection complete");


    /*
     * III: Send Control Request -------------------------
     *
     * Log into the ftp server, send the username & password, change to the
     * correct directory...
     */


    /* possible results: */
    /* 120 Service ready in nnn minutes. */
    /* 220 Service ready for new user. */
    /* 421 Service not available, closing control connection. */
    rc = proxy_ftp_command(NULL, r, origin, bb, &ftpmessage);
    if (rc == -1 || rc == 421) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, "Error reading from remote server");
    }
    if (rc == 120) {
        /*
         * RFC2616 states: 14.37 Retry-After
         *
         * The Retry-After response-header field can be used with a 503 (Service
         * Unavailable) response to indicate how long the service is expected
         * to be unavailable to the requesting client. [...] The value of
         * this field can be either an HTTP-date or an integer number of
         * seconds (in decimal) after the time of the response. Retry-After
         * = "Retry-After" ":" ( HTTP-date | delta-seconds )
         */
        char *secs_str = ftpmessage;
        time_t secs;

        /* Look for a number, preceded by whitespace */
        while (*secs_str)
            if ((secs_str==ftpmessage || apr_isspace(secs_str[-1])) &&
                apr_isdigit(secs_str[0]))
                break;
        if (*secs_str != '\0') {
            secs = atol(secs_str);
            apr_table_add(r->headers_out, "Retry-After",
                          apr_psprintf(p, "%lu", (unsigned long)(60 * secs)));
        }
        return ftp_proxyerror(r, backend, HTTP_SERVICE_UNAVAILABLE, ftpmessage);
    }
    if (rc != 220) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
    }

    rc = proxy_ftp_command(apr_pstrcat(p, "USER ", user, CRLF, NULL),
                           r, origin, bb, &ftpmessage);
    /* possible results; 230, 331, 332, 421, 500, 501, 530 */
    /* states: 1 - error, 2 - success; 3 - send password, 4,5 fail */
    /* 230 User logged in, proceed. */
    /* 331 User name okay, need password. */
    /* 332 Need account for login. */
    /* 421 Service not available, closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    /* (This may include errors such as command line too long.) */
    /* 501 Syntax error in parameters or arguments. */
    /* 530 Not logged in. */
    if (rc == -1 || rc == 421) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, "Error reading from remote server");
    }
    if (rc == 530) {
        proxy_ftp_cleanup(r, backend);
        return ftp_unauthorized(r, 1);  /* log it: user name guessing
                                         * attempt? */
    }
    if (rc != 230 && rc != 331) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
    }

    if (rc == 331) {            /* send password */
        if (password == NULL) {
            proxy_ftp_cleanup(r, backend);
            return ftp_unauthorized(r, 0);
        }

        rc = proxy_ftp_command(apr_pstrcat(p, "PASS ", password, CRLF, NULL),
                           r, origin, bb, &ftpmessage);
        /* possible results 202, 230, 332, 421, 500, 501, 503, 530 */
        /* 230 User logged in, proceed. */
        /* 332 Need account for login. */
        /* 421 Service not available, closing control connection. */
        /* 500 Syntax error, command unrecognized. */
        /* 501 Syntax error in parameters or arguments. */
        /* 503 Bad sequence of commands. */
        /* 530 Not logged in. */
        if (rc == -1 || rc == 421) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
        }
        if (rc == 332) {
            return ftp_proxyerror(r, backend, HTTP_UNAUTHORIZED,
                  apr_pstrcat(p, "Need account for login: ", ftpmessage, NULL));
        }
        /* @@@ questionable -- we might as well return a 403 Forbidden here */
        if (rc == 530) {
            proxy_ftp_cleanup(r, backend);
            return ftp_unauthorized(r, 1);      /* log it: passwd guessing
                                                 * attempt? */
        }
        if (rc != 230 && rc != 202) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }
    }
    apr_table_set(r->notes, "Directory-README", ftpmessage);


    /* Special handling for leading "%2f": this enforces a "cwd /"
     * out of the $HOME directory which was the starting point after login
     */
    if (strncasecmp(path, "%2f", 3) == 0) {
        path += 3;
        while (*path == '/') /* skip leading '/' (after root %2f) */
            ++path;

        rc = proxy_ftp_command("CWD /" CRLF, r, origin, bb, &ftpmessage);
        if (rc == -1 || rc == 421)
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
    }

    /*
     * set the directory (walk directory component by component): this is
     * what we must do if we don't know the OS type of the remote machine
     */
    for (;;) {
        strp = strchr(path, '/');
        if (strp == NULL)
            break;
        *strp = '\0';

        len = decodeenc(path); /* Note! This decodes a %2f -> "/" */

        if (strchr(path, '/')) { /* are there now any '/' characters? */
            return ftp_proxyerror(r, backend, HTTP_BAD_REQUEST,
                                  "Use of /%2f is only allowed at the base directory");
        }

        /* NOTE: FTP servers do globbing on the path.
         * So we need to escape the URI metacharacters.
         * We use a special glob-escaping routine to escape globbing chars.
         * We could also have extended gen_test_char.c with a special T_ESCAPE_FTP_PATH
         */
        rc = proxy_ftp_command(apr_pstrcat(p, "CWD ",
                           ftp_escape_globbingchars(p, path), CRLF, NULL),
                           r, origin, bb, &ftpmessage);
        *strp = '/';
        /* responses: 250, 421, 500, 501, 502, 530, 550 */
        /* 250 Requested file action okay, completed. */
        /* 421 Service not available, closing control connection. */
        /* 500 Syntax error, command unrecognized. */
        /* 501 Syntax error in parameters or arguments. */
        /* 502 Command not implemented. */
        /* 530 Not logged in. */
        /* 550 Requested action not taken. */
        if (rc == -1 || rc == 421) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
        }
        if (rc == 550) {
            return ftp_proxyerror(r, backend, HTTP_NOT_FOUND, ftpmessage);
        }
        if (rc != 250) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }

        path = strp + 1;
    }

    /*
     * IV: Make Data Connection? -------------------------
     *
     * Try EPSV, if that fails... try PASV, if that fails... try PORT.
     */
/* this temporarily switches off EPSV/PASV */
/*goto bypass;*/

    /* set up data connection - EPSV */
    {
        apr_sockaddr_t *data_addr;
        char *data_ip;
        apr_port_t data_port;

        /*
         * The EPSV command replaces PASV where both IPV4 and IPV6 is
         * supported. Only the port is returned, the IP address is always the
         * same as that on the control connection. Example: Entering Extended
         * Passive Mode (|||6446|)
         */
        rc = proxy_ftp_command("EPSV" CRLF,
                           r, origin, bb, &ftpmessage);
        /* possible results: 227, 421, 500, 501, 502, 530 */
        /* 227 Entering Passive Mode (h1,h2,h3,h4,p1,p2). */
        /* 421 Service not available, closing control connection. */
        /* 500 Syntax error, command unrecognized. */
        /* 501 Syntax error in parameters or arguments. */
        /* 502 Command not implemented. */
        /* 530 Not logged in. */
        if (rc == -1 || rc == 421) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
        }
        if (rc != 229 && rc != 500 && rc != 501 && rc != 502) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }
        else if (rc == 229) {
            char *pstr;
            char *tok_cntx;

            pstr = ftpmessage;
            pstr = apr_strtok(pstr, " ", &tok_cntx);    /* separate result code */
            if (pstr != NULL) {
                if (*(pstr + strlen(pstr) + 1) == '=') {
                    pstr += strlen(pstr) + 2;
                }
                else {
                    pstr = apr_strtok(NULL, "(", &tok_cntx);    /* separate address &
                                                                 * port params */
                    if (pstr != NULL)
                        pstr = apr_strtok(NULL, ")", &tok_cntx);
                }
            }

            if (pstr) {
                apr_sockaddr_t *epsv_addr;
                data_port = atoi(pstr + 3);

                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                       "proxy: FTP: EPSV contacting remote host on port %d",
                             data_port);

                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: error creating EPSV socket");
                    proxy_ftp_cleanup(r, backend);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

#if !defined (TPF) && !defined(BEOS)
                if (conf->recv_buffer_size > 0
                        && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }
#endif

                /* make the connection */
                apr_socket_addr_get(&data_addr, APR_REMOTE, sock);
                apr_sockaddr_ip_get(&data_ip, data_addr);
                apr_sockaddr_info_get(&epsv_addr, data_ip, connect_addr->family, data_port, 0, p);
                rv = apr_socket_connect(data_sock, epsv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                                 "proxy: FTP: EPSV attempt to connect to %pI failed - Firewall/NAT?", epsv_addr);
                    return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "EPSV attempt to connect to %pI failed - firewall/NAT?", epsv_addr));
                }
                else {
                    connect = 1;
                }
            }
            else {
                /* and try the regular way */
                apr_socket_close(data_sock);
            }
        }
    }

    /* set up data connection - PASV */
    if (!connect) {
        rc = proxy_ftp_command("PASV" CRLF,
                           r, origin, bb, &ftpmessage);
        /* possible results: 227, 421, 500, 501, 502, 530 */
        /* 227 Entering Passive Mode (h1,h2,h3,h4,p1,p2). */
        /* 421 Service not available, closing control connection. */
        /* 500 Syntax error, command unrecognized. */
        /* 501 Syntax error in parameters or arguments. */
        /* 502 Command not implemented. */
        /* 530 Not logged in. */
        if (rc == -1 || rc == 421) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
        }
        if (rc != 227 && rc != 502) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }
        else if (rc == 227) {
            unsigned int h0, h1, h2, h3, p0, p1;
            char *pstr;
            char *tok_cntx;

/* FIXME: Check PASV against RFC1123 */

            pstr = ftpmessage;
            pstr = apr_strtok(pstr, " ", &tok_cntx);    /* separate result code */
            if (pstr != NULL) {
                if (*(pstr + strlen(pstr) + 1) == '=') {
                    pstr += strlen(pstr) + 2;
                }
                else {
                    pstr = apr_strtok(NULL, "(", &tok_cntx);    /* separate address &
                                                                 * port params */
                    if (pstr != NULL)
                        pstr = apr_strtok(NULL, ")", &tok_cntx);
                }
            }

/* FIXME: Only supports IPV4 - fix in RFC2428 */

            if (pstr != NULL && (sscanf(pstr,
                 "%d,%d,%d,%d,%d,%d", &h3, &h2, &h1, &h0, &p1, &p0) == 6)) {

                apr_sockaddr_t *pasv_addr;
                apr_port_t pasvport = (p1 << 8) + p0;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: FTP: PASV contacting host %d.%d.%d.%d:%d",
                             h3, h2, h1, h0, pasvport);

                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: error creating PASV socket");
                    proxy_ftp_cleanup(r, backend);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

#if !defined (TPF) && !defined(BEOS)
                if (conf->recv_buffer_size > 0
                        && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }
#endif

                /* make the connection */
                apr_sockaddr_info_get(&pasv_addr, apr_psprintf(p, "%d.%d.%d.%d", h3, h2, h1, h0), connect_addr->family, pasvport, 0, p);
                rv = apr_socket_connect(data_sock, pasv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                                 "proxy: FTP: PASV attempt to connect to %pI failed - Firewall/NAT?", pasv_addr);
                    return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "PASV attempt to connect to %pI failed - firewall/NAT?", pasv_addr));
                }
                else {
                    connect = 1;
                }
            }
            else {
                /* and try the regular way */
                apr_socket_close(data_sock);
            }
        }
    }
/*bypass:*/

    /* set up data connection - PORT */
    if (!connect) {
        apr_sockaddr_t *local_addr;
        char *local_ip;
        apr_port_t local_port;
        unsigned int h0, h1, h2, h3, p0, p1;

        if ((rv = apr_socket_create(&local_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FTP: error creating local socket");
            proxy_ftp_cleanup(r, backend);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_socket_addr_get(&local_addr, APR_LOCAL, sock);
        local_port = local_addr->port;
        apr_sockaddr_ip_get(&local_ip, local_addr);

        if ((rv = apr_socket_opt_set(local_sock, APR_SO_REUSEADDR, one))
                != APR_SUCCESS) {
#ifndef _OSD_POSIX              /* BS2000 has this option "always on" */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FTP: error setting reuseaddr option");
            proxy_ftp_cleanup(r, backend);
            return HTTP_INTERNAL_SERVER_ERROR;
#endif                          /* _OSD_POSIX */
        }

        apr_sockaddr_info_get(&local_addr, local_ip, APR_UNSPEC, local_port, 0, r->pool);

        if ((rv = apr_socket_bind(local_sock, local_addr)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
            "proxy: FTP: error binding to ftp data socket %pI", local_addr);
            proxy_ftp_cleanup(r, backend);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        /* only need a short queue */
        if ((rv = apr_socket_listen(local_sock, 2)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FTP: error listening to ftp data socket %pI", local_addr);
            proxy_ftp_cleanup(r, backend);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

/* FIXME: Sent PORT here */

        if (local_ip && (sscanf(local_ip,
                                "%d.%d.%d.%d", &h3, &h2, &h1, &h0) == 4)) {
            p1 = (local_port >> 8);
            p0 = (local_port & 0xFF);

            rc = proxy_ftp_command(apr_psprintf(p, "PORT %d,%d,%d,%d,%d,%d" CRLF, h3, h2, h1, h0, p1, p0),
                           r, origin, bb, &ftpmessage);
            /* possible results: 200, 421, 500, 501, 502, 530 */
            /* 200 Command okay. */
            /* 421 Service not available, closing control connection. */
            /* 500 Syntax error, command unrecognized. */
            /* 501 Syntax error in parameters or arguments. */
            /* 502 Command not implemented. */
            /* 530 Not logged in. */
            if (rc == -1 || rc == 421) {
                return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                      "Error reading from remote server");
            }
            if (rc != 200) {
                return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, buffer);
            }

            /* signal that we must use the EPRT/PORT loop */
            use_port = 1;
        }
        else {
/* IPV6 FIXME:
 * The EPRT command replaces PORT where both IPV4 and IPV6 is supported. The first
 * number (1,2) indicates the protocol type. Examples:
 *   EPRT |1|132.235.1.2|6275|
 *   EPRT |2|1080::8:800:200C:417A|5282|
 */
            return ftp_proxyerror(r, backend, HTTP_NOT_IMPLEMENTED,
                                  "Connect to IPV6 ftp server using EPRT not supported. Enable EPSV.");
        }
    }


    /*
     * V: Set The Headers -------------------
     *
     * Get the size of the request, set up the environment for HTTP.
     */

    /* set request; "path" holds last path component */
    len = decodeenc(path);

    if (strchr(path, '/')) { /* are there now any '/' characters? */
       return ftp_proxyerror(r, backend, HTTP_BAD_REQUEST,
                             "Use of /%2f is only allowed at the base directory");
    }

    /* If len == 0 then it must be a directory (you can't RETR nothing)
     * Also, don't allow to RETR by wildcard. Instead, create a dirlisting
     */
    if (len == 0 || ftp_check_globbingchars(path)) {
        dirlisting = 1;
    }
    else {
        /* (from FreeBSD ftpd):
         * SIZE is not in RFC959, but Postel has blessed it and
         * it will be in the updated RFC.
         *
         * Return size of file in a format suitable for
         * using with RESTART (we just count bytes).
         */
        /* from draft-ietf-ftpext-mlst-14.txt:
         * This value will
         * change depending on the current STRUcture, MODE and TYPE of the data
         * connection, or a data connection which would be created were one
         * created now.  Thus, the result of the SIZE command is dependent on
         * the currently established STRU, MODE and TYPE parameters.
         */
        /* Therefore: switch to binary if the user did not specify ";type=a" */
        ftp_set_TYPE(xfer_type, r, origin, bb, &ftpmessage);
        rc = proxy_ftp_command(apr_pstrcat(p, "SIZE ",
                           ftp_escape_globbingchars(p, path), CRLF, NULL),
                           r, origin, bb, &ftpmessage);
        if (rc == -1 || rc == 421) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
        }
        else if (rc == 213) {/* Size command ok */
            int j;
            for (j = 0; apr_isdigit(ftpmessage[j]); j++)
                ;
            ftpmessage[j] = '\0';
            if (ftpmessage[0] != '\0')
                 size = ftpmessage; /* already pstrdup'ed: no copy necessary */
        }
        else if (rc == 550) {    /* Not a regular file */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: FTP: SIZE shows this is a directory");
            dirlisting = 1;
            rc = proxy_ftp_command(apr_pstrcat(p, "CWD ",
                           ftp_escape_globbingchars(p, path), CRLF, NULL),
                           r, origin, bb, &ftpmessage);
            /* possible results: 250, 421, 500, 501, 502, 530, 550 */
            /* 250 Requested file action okay, completed. */
            /* 421 Service not available, closing control connection. */
            /* 500 Syntax error, command unrecognized. */
            /* 501 Syntax error in parameters or arguments. */
            /* 502 Command not implemented. */
            /* 530 Not logged in. */
            /* 550 Requested action not taken. */
            if (rc == -1 || rc == 421) {
                return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                      "Error reading from remote server");
            }
            if (rc == 550) {
                return ftp_proxyerror(r, backend, HTTP_NOT_FOUND, ftpmessage);
            }
            if (rc != 250) {
                return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
            }
            path = "";
            len = 0;
        }
    }

    cwd = ftp_get_PWD(r, origin, bb);
    if (cwd != NULL) {
        apr_table_set(r->notes, "Directory-PWD", cwd);
    }

    if (dirlisting) {
        ftp_set_TYPE('A', r, origin, bb, NULL);
        /* If the current directory contains no slash, we are talking to
         * a non-unix ftp system. Try LIST instead of "LIST -lag", it
         * should return a long listing anyway (unlike NLST).
         * Some exotic FTP servers might choke on the "-lag" switch.
         */
        /* Note that we do not escape the path here, to allow for
         * queries like: ftp://user@host/apache/src/server/http_*.c
         */
        if (len != 0)
            buf = apr_pstrcat(p, "LIST ", path, CRLF, NULL);
        else if (cwd == NULL || strchr(cwd, '/') != NULL)
            buf = apr_pstrcat(p, "LIST -lag", CRLF, NULL);
        else
            buf = "LIST" CRLF;
    }
    else {
        /* switch to binary if the user did not specify ";type=a" */
        ftp_set_TYPE(xfer_type, r, origin, bb, &ftpmessage);
#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
        /* from draft-ietf-ftpext-mlst-14.txt:
         *   The FTP command, MODIFICATION TIME (MDTM), can be used to determine
         *   when a file in the server NVFS was last modified.     <..>
         *   The syntax of a time value is:
         *           time-val       = 14DIGIT [ "." 1*DIGIT ]      <..>
         *     Symbolically, a time-val may be viewed as
         *           YYYYMMDDHHMMSS.sss
         *     The "." and subsequent digits ("sss") are optional. <..>
         *     Time values are always represented in UTC (GMT)
         */
        rc = proxy_ftp_command(apr_pstrcat(p, "MDTM ", ftp_escape_globbingchars(p, path), CRLF, NULL),
                               r, origin, bb, &ftpmessage);
        /* then extract the Last-Modified time from it (YYYYMMDDhhmmss or YYYYMMDDhhmmss.xxx GMT). */
        if (rc == 213) {
        struct {
            char YYYY[4+1];
        char MM[2+1];
        char DD[2+1];
        char hh[2+1];
        char mm[2+1];
        char ss[2+1];
        } time_val;
        if (6 == sscanf(ftpmessage, "%4[0-9]%2[0-9]%2[0-9]%2[0-9]%2[0-9]%2[0-9]",
            time_val.YYYY, time_val.MM, time_val.DD, time_val.hh, time_val.mm, time_val.ss)) {
                struct tm tms;
        memset (&tms, '\0', sizeof tms);
        tms.tm_year = atoi(time_val.YYYY) - 1900;
        tms.tm_mon  = atoi(time_val.MM)   - 1;
        tms.tm_mday = atoi(time_val.DD);
        tms.tm_hour = atoi(time_val.hh);
        tms.tm_min  = atoi(time_val.mm);
        tms.tm_sec  = atoi(time_val.ss);
#ifdef HAVE_TIMEGM /* Does system have timegm()? */
        mtime = timegm(&tms);
        mtime *= APR_USEC_PER_SEC;
#elif HAVE_GMTOFF /* does struct tm have a member tm_gmtoff? */
                /* mktime will subtract the local timezone, which is not what we want.
         * Add it again because the MDTM string is GMT
         */
        mtime = mktime(&tms);
        mtime += tms.tm_gmtoff;
        mtime *= APR_USEC_PER_SEC;
#else
        mtime = 0L;
#endif
            }
    }
#endif /* USE_MDTM */
/* FIXME: Handle range requests - send REST */
        buf = apr_pstrcat(p, "RETR ", ftp_escape_globbingchars(p, path), CRLF, NULL);
    }
    rc = proxy_ftp_command(buf, r, origin, bb, &ftpmessage);
    /* rc is an intermediate response for the LIST or RETR commands */

    /*
     * RETR: 110, 125, 150, 226, 250, 421, 425, 426, 450, 451, 500, 501, 530,
     * 550 NLST: 125, 150, 226, 250, 421, 425, 426, 450, 451, 500, 501, 502,
     * 530
     */
    /* 110 Restart marker reply. */
    /* 125 Data connection already open; transfer starting. */
    /* 150 File status okay; about to open data connection. */
    /* 226 Closing data connection. */
    /* 250 Requested file action okay, completed. */
    /* 421 Service not available, closing control connection. */
    /* 425 Can't open data connection. */
    /* 426 Connection closed; transfer aborted. */
    /* 450 Requested file action not taken. */
    /* 451 Requested action aborted. Local error in processing. */
    /* 500 Syntax error, command unrecognized. */
    /* 501 Syntax error in parameters or arguments. */
    /* 530 Not logged in. */
    /* 550 Requested action not taken. */
    if (rc == -1 || rc == 421) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                              "Error reading from remote server");
    }
    if (rc == 550) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: RETR failed, trying LIST instead");

        /* Directory Listings should always be fetched in ASCII mode */
        dirlisting = 1;
        ftp_set_TYPE('A', r, origin, bb, NULL);

        rc = proxy_ftp_command(apr_pstrcat(p, "CWD ",
                               ftp_escape_globbingchars(p, path), CRLF, NULL),
                               r, origin, bb, &ftpmessage);
        /* possible results: 250, 421, 500, 501, 502, 530, 550 */
        /* 250 Requested file action okay, completed. */
        /* 421 Service not available, closing control connection. */
        /* 500 Syntax error, command unrecognized. */
        /* 501 Syntax error in parameters or arguments. */
        /* 502 Command not implemented. */
        /* 530 Not logged in. */
        /* 550 Requested action not taken. */
        if (rc == -1 || rc == 421) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
        }
        if (rc == 550) {
            return ftp_proxyerror(r, backend, HTTP_NOT_FOUND, ftpmessage);
        }
        if (rc != 250) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }

        /* Update current directory after CWD */
        cwd = ftp_get_PWD(r, origin, bb);
        if (cwd != NULL) {
            apr_table_set(r->notes, "Directory-PWD", cwd);
        }

        /* See above for the "LIST" vs. "LIST -lag" discussion. */
        rc = proxy_ftp_command((cwd == NULL || strchr(cwd, '/') != NULL)
                               ? "LIST -lag" CRLF : "LIST" CRLF,
                               r, origin, bb, &ftpmessage);

        /* rc is an intermediate response for the LIST command (125 transfer starting, 150 opening data connection) */
        if (rc == -1 || rc == 421)
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
    }
    if (rc != 125 && rc != 150 && rc != 226 && rc != 250) {
        return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
    }

    r->status = HTTP_OK;
    r->status_line = "200 OK";

    apr_rfc822_date(dates, r->request_time);
    apr_table_setn(r->headers_out, "Date", dates);
    apr_table_setn(r->headers_out, "Server", ap_get_server_banner());

    /* set content-type */
    if (dirlisting) {
        ap_set_content_type(r, "text/html");
    }
    else {
        if (r->content_type) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: Content-Type set to %s", r->content_type);
        }
        else {
            ap_set_content_type(r, ap_default_type(r));
        }
        if (xfer_type != 'A' && size != NULL) {
            /* We "trust" the ftp server to really serve (size) bytes... */
            apr_table_setn(r->headers_out, "Content-Length", size);
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: FTP: Content-Length set to %s", size);
        }
    }
    apr_table_setn(r->headers_out, "Content-Type", r->content_type);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: Content-Type set to %s", r->content_type);

#if defined(USE_MDTM) && (defined(HAVE_TIMEGM) || defined(HAVE_GMTOFF))
    if (mtime != 0L) {
        char datestr[APR_RFC822_DATE_LEN];
        apr_rfc822_date(datestr, mtime);
        apr_table_set(r->headers_out, "Last-Modified", datestr);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: Last-Modified set to %s", datestr);
    }
#endif /* USE_MDTM */

    /* If an encoding has been set by mistake, delete it.
     * @@@ FIXME (e.g., for ftp://user@host/file*.tar.gz,
     * @@@        the encoding is currently set to x-gzip)
     */
    if (dirlisting && r->content_encoding != NULL)
        r->content_encoding = NULL;

    /* set content-encoding (not for dir listings, they are uncompressed)*/
    if (r->content_encoding != NULL && r->content_encoding[0] != '\0') {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
             "proxy: FTP: Content-Encoding set to %s", r->content_encoding);
        apr_table_setn(r->headers_out, "Content-Encoding", r->content_encoding);
    }

    /* wait for connection */
    if (use_port) {
        for (;;) {
            rv = apr_socket_accept(&data_sock, local_sock, r->pool);
            if (rv == APR_EINTR) {
                continue;
            }
            else if (rv == APR_SUCCESS) {
                break;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                            "proxy: FTP: failed to accept data connection");
                proxy_ftp_cleanup(r, backend);
                return HTTP_BAD_GATEWAY;
            }
        }
    }

    /* the transfer socket is now open, create a new connection */
    data = ap_run_create_connection(p, r->server, data_sock, r->connection->id,
                                    r->connection->sbh, c->bucket_alloc);
    if (!data) {
        /*
         * the peer reset the connection already; ap_run_create_connection() closed
         * the socket
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
          "proxy: FTP: an error occurred creating the transfer connection");
        proxy_ftp_cleanup(r, backend);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* set up the connection filters */
    rc = ap_run_pre_connection(data, data_sock);
    if (rc != OK && rc != DONE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: pre_connection setup failed (%d)",
                     rc);
        data->aborted = 1;
        proxy_ftp_cleanup(r, backend);
        return rc;
    }

    /*
     * VI: Receive the Response ------------------------
     *
     * Get response from the remote ftp socket, and pass it up the filter chain.
     */

    /* send response */
    r->sent_bodyct = 1;

    if (dirlisting) {
        /* insert directory filter */
        ap_add_output_filter("PROXY_SEND_DIR", NULL, r, r->connection);
    }

    /* send body */
    if (!r->header_only) {
        apr_bucket *e;
        int finish = FALSE;

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: start body send");

        /* read the body, pass it to the output filters */
        while (ap_get_brigade(data->input_filters,
                              bb,
                              AP_MODE_READBYTES,
                              APR_BLOCK_READ,
                              conf->io_buffer_size) == APR_SUCCESS) {
#if DEBUGGING
            {
                apr_off_t readbytes;
                apr_brigade_length(bb, 0, &readbytes);
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                             r->server, "proxy (PID %d): readbytes: %#x",
                             getpid(), readbytes);
            }
#endif
            /* sanity check */
            if (APR_BRIGADE_EMPTY(bb)) {
                apr_brigade_cleanup(bb);
                break;
            }

            /* found the last brigade? */
            if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
                /* if this is the last brigade, cleanup the
                 * backend connection first to prevent the
                 * backend server from hanging around waiting
                 * for a slow client to eat these bytes
                 */
                ap_flush_conn(data);
                apr_socket_close(data_sock);
                data_sock = NULL;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: FTP: data connection closed");
                /* signal that we must leave */
                finish = TRUE;
            }

            /* if no EOS yet, then we must flush */
            if (FALSE == finish) {
                e = apr_bucket_flush_create(c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
            }

            /* try send what we read */
            if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
                || c->aborted) {
                /* Ack! Phbtt! Die! User aborted! */
                finish = TRUE;
            }

            /* make sure we always clean up after ourselves */
            apr_brigade_cleanup(bb);

            /* if we are done, leave */
            if (TRUE == finish) {
                break;
            }
        }
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: end body send");

    }
    if (data_sock) {
        ap_flush_conn(data);
        apr_socket_close(data_sock);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: data connection closed");
    }

    /* Retrieve the final response for the RETR or LIST commands */
    rc = proxy_ftp_command(NULL, r, origin, bb, &ftpmessage);
    apr_brigade_cleanup(bb);

    /*
     * VII: Clean Up -------------
     *
     * If there are no KeepAlives, or if the connection has been signalled to
     * close, close the socket and clean up
     */

    /* finish */
    rc = proxy_ftp_command("QUIT" CRLF,
                           r, origin, bb, &ftpmessage);
    /* responses: 221, 500 */
    /* 221 Service closing control connection. */
    /* 500 Syntax error, command unrecognized. */
    ap_flush_conn(origin);
    proxy_ftp_cleanup(r, backend);

    apr_brigade_destroy(bb);
    return OK;
}