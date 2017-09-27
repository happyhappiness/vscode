                    (p2 == NULL && strcasecmp(scheme, ents[i].scheme) == 0) ||
                    (p2 != NULL &&
                    strncasecmp(url, ents[i].scheme,
                                strlen(ents[i].scheme)) == 0)) {

                    /* handle the scheme */
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "Trying to run scheme_handler against proxy");
                    access_status = proxy_run_scheme_handler(r, worker,
                                                             conf, url,
                                                             ents[i].hostname,
                                                             ents[i].port);

                    /* Did the scheme handler process the request? */
