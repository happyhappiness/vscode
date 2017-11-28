static int
MainSafe(int argc, char **argv)
{
    char bufa[EDUI_MAXLEN], bufb[EDUI_MAXLEN], *p = NULL;
    char bufc[EDUI_MAXLEN];
    char sfmod[EDUI_MAXLEN];
    int x;
    size_t i, j, s, k;
    time_t t;
    struct sigaction sv;

    /* Init */
    k = (size_t) argc;
    memset(bufa, '\0', sizeof(bufa));
    memset(bufb, '\0', sizeof(bufb));
    memset(bufc, '\0', sizeof(bufc));
    memset(sfmod, '\0', sizeof(sfmod));

    InitConf();
    xstrncpy(edui_conf.program, argv[0], sizeof(edui_conf.program));
    edui_now = -1;
    t = -1;

    /* Scan args */
    if (k > 1) {
        for (i = 1; i < k; ++i) {
            /* Classic / novelty usage schemes */
            if (!strcmp(argv[i], "--help")) {
                DisplayUsage();
                return 1;
            } else if (!strcmp(argv[i], "--usage")) {
                DisplayUsage();
                return 1;
            } else if (!strcmp(argv[i], "--version")) {
                DisplayVersion();
                return 1;
            } else if (argv[i][0] == '-') {
                s = strlen(argv[i]);
                for (j = 1; j < s; ++j) {
                    switch (argv[i][j]) {
                    case 'h':
                        DisplayUsage();
                        return 1;
                    case 'V':
                        DisplayVersion();
                        return 1;
                    case 'd':
                        if (!(edui_conf.mode & EDUI_MODE_DEBUG))
                            edui_conf.mode |= EDUI_MODE_DEBUG;		/* Don't set mode more than once */
                        debug_enabled = 1;				/* Official Squid-3 Debug Mode */
                        break;
                    case '4':
                        if (!(edui_conf.mode & EDUI_MODE_IPV4) || !(edui_conf.mode & EDUI_MODE_IPV6))
                            edui_conf.mode |= EDUI_MODE_IPV4;		/* Don't set mode more than once */
                        break;
                    case '6':
                        if (!(edui_conf.mode & EDUI_MODE_IPV4) || !(edui_conf.mode & EDUI_MODE_IPV6))
                            edui_conf.mode |= EDUI_MODE_IPV6;		/* Don't set mode more than once */
                        break;
                    case 'Z':
                        if (!(edui_conf.mode & EDUI_MODE_TLS))
                            edui_conf.mode |= EDUI_MODE_TLS;		/* Don't set mode more than once */
                        break;
                    case 'P':
                        if (!(edui_conf.mode & EDUI_MODE_PERSIST))
                            edui_conf.mode |= EDUI_MODE_PERSIST;	/* Don't set mode more than once */
                        break;
                    case 'v':
                        ++i;						/* Set LDAP version */
                        if (argv[i] != NULL) {
                            edui_conf.ver = atoi(argv[i]);
                            if (edui_conf.ver < 1)
                                edui_conf.ver = 1;
                            else if (edui_conf.ver > 3)
                                edui_conf.ver = 3;
                        } else {
                            local_printfx("No parameters given for 'v'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 't':
                        ++i;						/* Set Persistent timeout */
                        if (argv[i] != NULL) {
                            edui_conf.persist_timeout = atoi(argv[i]);
                            if (edui_conf.persist_timeout < 0)
                                edui_conf.persist_timeout = 0;
                        } else {
                            local_printfx("No parameters given for 't'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'b':
                        ++i;						/* Set Base DN */
                        if (argv[i] != NULL)
                            xstrncpy(edui_conf.basedn, argv[i], sizeof(edui_conf.basedn));
                        else {
                            local_printfx("No parameters given for 'b'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'H':
                        ++i;						/* Set Hostname */
                        if (argv[i] != NULL)
                            xstrncpy(edui_conf.host, argv[i], sizeof(edui_conf.host));
                        else {
                            local_printfx("No parameters given for 'H'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'p':
                        ++i;						/* Set port */
                        if (argv[i] != NULL)
                            edui_conf.port = atoi(argv[i]);
                        else {
                            local_printfx("No parameters given for 'p'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'D':
                        ++i;						/* Set Bind DN */
                        if (argv[i] != NULL)
                            xstrncpy(edui_conf.dn, argv[i], sizeof(edui_conf.dn));
                        else {
                            local_printfx("No parameters given for 'D'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'W':
                        ++i;						/* Set Bind PWD */
                        if (argv[i] != NULL)
                            xstrncpy(edui_conf.passwd, argv[i], sizeof(edui_conf.passwd));
                        else {
                            local_printfx("No parameters given for 'W'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'F':
                        ++i;						/* Set Search Filter */
                        if (argv[i] != NULL)
                            xstrncpy(edui_conf.search_filter, argv[i], sizeof(edui_conf.search_filter));
                        else {
                            local_printfx("No parameters given for 'F'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'G':
                        if (!(edui_conf.mode & EDUI_MODE_GROUP))
                            edui_conf.mode |= EDUI_MODE_GROUP;		/* Don't set mode more than once */
                        break;
                    case 's':
                        ++i;						/* Set Scope Level */
                        if (argv[i] != NULL) {
                            if (!strncmp(argv[i], "base", 4))
                                edui_conf.scope = 0;
                            else if (!strncmp(argv[i], "one", 4))
                                edui_conf.scope = 1;
                            else if (!strncmp(argv[i], "sub", 4))
                                edui_conf.scope = 2;
                            else
                                edui_conf.scope = 1;			/* Default is 'one' */
                        } else {
                            local_printfx("No parameters given for 's'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case 'u':
                        ++i;						/* Set Search Attribute */
                        if (argv[i] != NULL) {
                            xstrncpy(edui_conf.attrib, argv[i], sizeof(edui_conf.attrib));
                        } else {
                            local_printfx("No parameters given for 'u'.\n");
                            DisplayUsage();
                            return 1;
                        }
                        break;
                    case '-':						/* We got a second '-' ... ignore */
                        break;
                    default:
                        local_printfx("Invalid parameter - '%c'.\n", argv[i][j]);
                        break;
                    }
                }
            } else {
                /* Incorrect parameter, display usage */
                DisplayUsage();
                return 1;
            }
        }
    }

    /* Set predefined required paremeters if none are given, localhost:LDAP_PORT, etc */
    if (edui_conf.host[0] == '\0')				/* Default to localhost */
        xstrncpy(edui_conf.host, "localhost", sizeof(edui_conf.host));
    if (edui_conf.port < 0)
        edui_conf.port = LDAP_PORT;				/* Default: LDAP_PORT */
    if ((edui_conf.mode & EDUI_MODE_IPV4) && (edui_conf.mode & EDUI_MODE_IPV6))
        edui_conf.mode &= ~(EDUI_MODE_IPV6);			/* Default to IPv4 */
    if (edui_conf.ver < 0)
        edui_conf.ver = 2;
    if (!(edui_conf.mode & EDUI_MODE_TLS))
        edui_conf.mode |= EDUI_MODE_TLS;			/* eDirectory requires TLS mode */
    if ((edui_conf.mode & EDUI_MODE_TLS) && (edui_conf.ver < 3))
        edui_conf.ver = 3;					/* TLS requires version 3 */
    if (edui_conf.persist_timeout < 0)
        edui_conf.persist_timeout = 600;			/* Default: 600 seconds (10 minutes) */
    if (edui_conf.scope < 0)
        edui_conf.scope = 1;					/* Default: one */
    if (edui_conf.search_filter[0] == '\0')
        xstrncpy(edui_conf.search_filter, "(&(objectclass=User)(networkAddress=*))", sizeof(edui_conf.search_filter));
    if (edui_conf.attrib[0] == '\0')
        xstrncpy(edui_conf.attrib, "cn", sizeof(edui_conf.attrib));
    if (edui_conf.basedn[0] == '\0') {
        local_printfx("FATAL: No '-b' option provided (Base DN).\n");
        DisplayUsage();
        return 1;
    }
    /* Trap the following signals */
    sigemptyset(&sv.sa_mask);
    sv.sa_handler = SigTrap;
    sigaction(SIGTERM, &sv, NULL);
    sv.sa_handler = SigTrap;
    sigaction(SIGHUP, &sv, NULL);
    sv.sa_handler = SigTrap;
    sigaction(SIGABRT, &sv, NULL);
    sv.sa_handler = SigTrap;
    sigaction(SIGINT, &sv, NULL);
    sv.sa_handler = SigTrap;
    sigaction(SIGSEGV, &sv, NULL);

    DisplayConf();
    /* Done with arguments */

    /* Set elap timer */
    time(&edui_now);
    t = edui_now;
    /* Main loop -- Waits for stdin input before action */
    while (fgets(bufa, sizeof(bufa), stdin) != NULL) {
        if (edui_conf.mode & EDUI_MODE_KILL)
            break;
        time(&edui_now);
        if (t < edui_now) {
            /* Elapse seconds */
            edui_elap = edui_now - t;
            t = edui_now;
        } else
            edui_elap = 0;
        k = strlen(bufa);
        /* BINARY DEBUGGING *
                    local_printfx("while() -> bufa[%" PRIuSIZE "]: %s", k, bufa);
                    for (i = 0; i < k; ++i)
                      local_printfx("%02X", bufa[i]);
                    local_printfx("\n");
        * BINARY DEBUGGING */
        /* Check for CRLF */
        p = strchr(bufa, '\n');
        if (p != NULL)
            *p = '\0';
        p = strchr(bufa, '\r');
        if (p != NULL)
            *p = '\0';
        p = strchr(bufa, ' ');

        /* No space given, but group string is required --> ERR */
        if ((edui_conf.mode & EDUI_MODE_GROUP) && (p == NULL)) {
            debug("while() -> Search group is missing. (required)\n");
            local_printfx("ERR message=\"(Search Group Required)\"\n");
            continue;
        }
        x = 0;

        /* Open LDAP connection */
        if (!(edui_ldap.status & LDAP_INIT_S)) {
            InitLDAP(&edui_ldap);
            debug("InitLDAP() -> %s\n", ErrLDAP(LDAP_ERR_SUCCESS));
            if (edui_conf.mode & EDUI_MODE_PERSIST)					/* Setup persistant mode */
                edui_ldap.status |= LDAP_PERSIST_S;
        }
        if ((edui_ldap.status & LDAP_IDLE_S) && (edui_elap > 0)) {
            edui_ldap.idle_time = edui_ldap.idle_time + edui_elap;
        }
        if ((edui_ldap.status & LDAP_PERSIST_S) && (edui_ldap.status & LDAP_IDLE_S) && (edui_ldap.idle_time > edui_conf.persist_timeout)) {
            debug("while() -> Connection timed out after %d seconds\n", (int)(edui_ldap.idle_time));
            x = CloseLDAP(&edui_ldap);
            debug("CloseLDAP(-) -> %s\n", ErrLDAP(x));
        }
        edui_ldap.err = -1;
        if (!(edui_ldap.status & LDAP_OPEN_S)) {
            x = OpenLDAP(&edui_ldap, edui_conf.host, edui_conf.port);
            if (x != LDAP_ERR_SUCCESS) {
                /* Failed to connect */
                debug("OpenLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
            } else {
                debug("OpenLDAP(-, %s, %d) -> %s\n", edui_conf.host, edui_conf.port, ErrLDAP(x));
                x = SetVerLDAP(&edui_ldap, edui_conf.ver);
                if (x != LDAP_ERR_SUCCESS) {
                    /* Failed to set version */
                    debug("SetVerLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                } else
                    debug("SetVerLDAP(-, %d) -> %s\n", edui_conf.ver, ErrLDAP(x));
            }
        }
        edui_ldap.err = -1;
        if (!(edui_ldap.status & LDAP_BIND_S) && (edui_conf.mode & EDUI_MODE_TLS)) {
            /* TLS binding */
            x = BindLDAP(&edui_ldap, edui_conf.dn, edui_conf.passwd, LDAP_AUTH_TLS);
            if (x != LDAP_ERR_SUCCESS) {
                /* Unable to bind */
                debug("BindLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                local_printfx("ERR message=\"(BindLDAP: %s - %s)\"\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                continue;
            } else
                debug("BindLDAP(-, %s, %s, (LDAP_AUTH_TLS)) -> %s\n", edui_conf.dn, edui_conf.passwd, ErrLDAP(x));
        } else if (!(edui_ldap.status & LDAP_BIND_S)) {
            if (edui_conf.dn[0] != '\0') {
                /* Simple binding - using dn / passwd for authorization */
                x = BindLDAP(&edui_ldap, edui_conf.dn, edui_conf.passwd, LDAP_AUTH_SIMPLE);
                if (x != LDAP_ERR_SUCCESS) {
                    /* Unable to bind */
                    debug("BindLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                    local_printfx("ERR message=\"(BindLDAP: %s - %s)\"\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                    continue;
                } else
                    debug("BindLDAP(-, %s, %s, (LDAP_AUTH_SIMPLE)) -> %s\n", edui_conf.dn, edui_conf.passwd, ErrLDAP(x));
            } else {
                /* Anonymous binding */
                x = BindLDAP(&edui_ldap, edui_conf.dn, edui_conf.passwd, LDAP_AUTH_NONE);
                if (x != LDAP_ERR_SUCCESS) {
                    /* Unable to bind */
                    debug("BindLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                    local_printfx("ERR message=\"(BindLDAP: %s - %s)\"\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                    continue;
                } else
                    debug("BindLDAP(-, -, -, (LDAP_AUTH_NONE)) -> %s\n", ErrLDAP(x));
            }
        }
        edui_ldap.err = -1;
        if (edui_ldap.status & LDAP_PERSIST_S) {
            x = ResetLDAP(&edui_ldap);
            if (x != LDAP_ERR_SUCCESS) {
                /* Unable to reset */
                debug("ResetLDAP() -> %s\n", ErrLDAP(x));
            } else
                debug("ResetLDAP() -> %s\n", ErrLDAP(x));
        }
        if (x != LDAP_ERR_SUCCESS) {
            /* Everything failed --> ERR */
            debug("while() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
            CloseLDAP(&edui_ldap);
            local_printfx("ERR message=\"(General Failure: %s)\"\n", ErrLDAP(x));
            continue;
        }
        edui_ldap.err = -1;
        /* If we got a group string, split it */
        if (p != NULL) {
            /* Split string */
            debug("StringSplit(%s, ' ', %s, %" PRIuSIZE ")\n", bufa, bufb, sizeof(bufb));
            i = StringSplit(bufa, ' ', bufb, sizeof(bufb));
            if (i > 0) {
                debug("StringSplit(%s, %s) done.  Result: %" PRIuSIZE "\n", bufa, bufb, i);
                /* Got a group to match against */
                x = ConvertIP(&edui_ldap, bufb);
                if (x < 0) {
                    debug("ConvertIP() -> %s\n", ErrLDAP(x));
                    local_printfx("ERR message=\"(ConvertIP: %s)\"\n", ErrLDAP(x));
                } else {
                    edui_ldap.err = -1;
                    debug("ConvertIP(-, %s) -> Result[%d]: %s\n", bufb, x, edui_ldap.search_ip);
                    x = SearchFilterLDAP(&edui_ldap, bufa);
                    if (x < 0) {
                        debug("SearchFilterLDAP() -> %s\n", ErrLDAP(x));
                        local_printfx("ERR message=\"(SearchFilterLDAP: %s)\"\n", ErrLDAP(x));
                    } else {
                        /* Do Search */
                        edui_ldap.err = -1;
                        debug("SearchFilterLDAP(-, %s) -> Length: %u\n", bufa, x);
                        x = SearchLDAP(&edui_ldap, edui_ldap.scope, edui_ldap.search_filter, (char **) &search_attrib);
                        if (x != LDAP_ERR_SUCCESS) {
                            debug("SearchLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                            local_printfx("ERR message=\"(SearchLDAP: %s)\"\n", ErrLDAP(x));
                        } else {
                            edui_ldap.err = -1;
                            debug("SearchLDAP(-, %d, %s, -) -> %s\n", edui_conf.scope, edui_ldap.search_filter, ErrLDAP(x));
                            x = SearchIPLDAP(&edui_ldap);
                            if (x != LDAP_ERR_SUCCESS) {
                                debug("SearchIPLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                                local_printfx("ERR message=\"(SearchIPLDAP: %s)\"\n", ErrLDAP(x));
                            } else {
                                debug("SearchIPLDAP(-, %s) -> %s\n", edui_ldap.userid, ErrLDAP(x));
                                local_printfx("OK user=%s\n", edui_ldap.userid);			/* Got userid --> OK user=<userid> */
                            }
                        }
                        /* Clear for next query */
                        memset(bufc, '\0', sizeof(bufc));
                    }
                }
            } else {
                debug("StringSplit() -> Error: %" PRIuSIZE "\n", i);
                local_printfx("ERR message=\"(StringSplit Error %" PRIuSIZE ")\"\n", i);
            }
        } else {
            /* No group to match against, only an IP */
            x = ConvertIP(&edui_ldap, bufa);
            if (x < 0) {
                debug("ConvertIP() -> %s\n", ErrLDAP(x));
                local_printfx("ERR message=\"(ConvertIP: %s)\"\n", ErrLDAP(x));
            } else {
                debug("ConvertIP(-, %s) -> Result[%d]: %s\n", bufa, x, edui_ldap.search_ip);
                /* Do search */
                x = SearchFilterLDAP(&edui_ldap, NULL);
                if (x < 0) {
                    debug("SearchFilterLDAP() -> %s\n", ErrLDAP(x));
                    local_printfx("ERR message=\"(SearchFilterLDAP: %s)\"\n", ErrLDAP(x));
                } else {
                    edui_ldap.err = -1;
                    debug("SearchFilterLDAP(-, NULL) -> Length: %u\n", x);
                    x = SearchLDAP(&edui_ldap, edui_ldap.scope, edui_ldap.search_filter, (char **) &search_attrib);
                    if (x != LDAP_ERR_SUCCESS) {
                        debug("SearchLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(x));
                        local_printfx("ERR message=\"(SearchLDAP: %s)\"\n", ErrLDAP(x));
                    } else {
                        edui_ldap.err = -1;
                        debug("SearchLDAP(-, %d, %s, -) -> %s\n", edui_conf.scope, edui_ldap.search_filter, ErrLDAP(x));
                        x = SearchIPLDAP(&edui_ldap);
                        if (x != LDAP_ERR_SUCCESS) {
                            debug("SearchIPLDAP() -> %s (LDAP: %s)\n", ErrLDAP(x), ldap_err2string(edui_ldap.err));
                            local_printfx("ERR message=\"(SearchIPLDAP: %s)\"\n", ErrLDAP(x));
                        } else {
                            debug("SearchIPLDAP(-, %s) -> %s\n", edui_ldap.userid, ErrLDAP(x));
                            local_printfx("OK user=%s\n", edui_ldap.userid);				/* Got a userid --> OK user=<userid> */
                        }
                    }
                }
                /* Clear for next query */
                memset(bufc, '\0', sizeof(bufc));
            }
        }

        /* Clear buffer and close for next data, if not persistent */
        edui_ldap.err = -1;
        memset(bufa, '\0', sizeof(bufa));
        if (!(edui_ldap.status & LDAP_PERSIST_S)) {
            x = CloseLDAP(&edui_ldap);
            debug("CloseLDAP(-) -> %s\n", ErrLDAP(x));
        }
    }

    debug("Terminating.\n");
    return 1;
}