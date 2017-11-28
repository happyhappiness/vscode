static void
configDoConfigure(void)
{
    memset(&Config2, '\0', sizeof(SquidConfig2));
    /* init memory as early as possible */
    memConfigure();
    /* Sanity checks */

    Config.cacheSwap.n_strands = 0; // no diskers by default
    if (Config.cacheSwap.swapDirs == NULL) {
        /* Memory-only cache probably in effect. */
        /* turn off the cache rebuild delays... */
        StoreController::store_dirs_rebuilding = 0;
    } else if (InDaemonMode()) { // no diskers in non-daemon mode
        for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
            const RefCount<SwapDir> sd = Config.cacheSwap.swapDirs[i];
            if (sd->needsDiskStrand())
                sd->disker = Config.workers + (++Config.cacheSwap.n_strands);
        }
    }

    if (Debug::rotateNumber < 0) {
        Debug::rotateNumber = Config.Log.rotateNumber;
    }

#if SIZEOF_OFF_T <= 4
    if (Config.Store.maxObjectSize > 0x7FFF0000) {
        debugs(3, DBG_CRITICAL, "WARNING: This Squid binary can not handle files larger than 2GB. Limiting maximum_object_size to just below 2GB");
        Config.Store.maxObjectSize = 0x7FFF0000;
    }
#endif

    if (Config.Announce.period > 0) {
        Config.onoff.announce = 1;
    } else {
        Config.Announce.period = 86400 * 365;	/* one year */
        Config.onoff.announce = 0;
    }

    if (Config.onoff.httpd_suppress_version_string)
        visible_appname_string = (char *)appname_string;
    else
        visible_appname_string = (char const *)APP_FULLNAME;

#if USE_DNSHELPER
    if (Config.dnsChildren.n_max < 1)
        fatal("No DNS helpers allocated");
#endif

    if (Config.Program.redirect) {
        if (Config.redirectChildren.n_max < 1) {
            Config.redirectChildren.n_max = 0;
            wordlistDestroy(&Config.Program.redirect);
        }
    }

    if (Config.Program.store_id) {
        if (Config.storeIdChildren.n_max < 1) {
            Config.storeIdChildren.n_max = 0;
            wordlistDestroy(&Config.Program.store_id);
        }
    }

    if (Config.appendDomain)
        if (*Config.appendDomain != '.')
            fatal("append_domain must begin with a '.'");

    if (Config.errHtmlText == NULL)
        Config.errHtmlText = xstrdup(null_string);

#if !HAVE_SETRLIMIT || !defined(RLIMIT_NOFILE)
    if (Config.max_filedescriptors > 0) {
        debugs(0, DBG_IMPORTANT, "WARNING: max_filedescriptors disabled. Operating System setrlimit(RLIMIT_NOFILE) is missing.");
    }
#elif USE_SELECT || USE_SELECT_WIN32
    if (Config.max_filedescriptors > FD_SETSIZE) {
        debugs(0, DBG_IMPORTANT, "WARNING: max_filedescriptors limited to " << FD_SETSIZE << " by select() algorithm.");
    }
#endif

    storeConfigure();
    update_maxobjsize(); // check for late maximum_object_size directive

    snprintf(ThisCache, sizeof(ThisCache), "%s (%s)",
             uniqueHostname(),
             visible_appname_string);

    /*
     * the extra space is for loop detection in client_side.c -- we search
     * for substrings in the Via header.
     */
    snprintf(ThisCache2, sizeof(ThisCache), " %s (%s)",
             uniqueHostname(),
             visible_appname_string);

    /* Use visible_hostname as default surrogate_id */
    if (!Config.Accel.surrogate_id) {
        const char *t = getMyHostname();
        Config.Accel.surrogate_id = xstrdup( (t?t:"unset-id") );
    }

    if (!Config.udpMaxHitObjsz || Config.udpMaxHitObjsz > SQUID_UDP_SO_SNDBUF)
        Config.udpMaxHitObjsz = SQUID_UDP_SO_SNDBUF;

    if (Config.appendDomain)
        Config.appendDomainLen = strlen(Config.appendDomain);
    else
        Config.appendDomainLen = 0;

    if (Config.connect_retries > 10) {
        debugs(0,DBG_CRITICAL, "WARNING: connect_retries cannot be larger than 10. Resetting to 10.");
        Config.connect_retries = 10;
    }

    requirePathnameExists("MIME Config Table", Config.mimeTablePathname);
#if USE_DNSHELPER
    requirePathnameExists("cache_dns_program", Config.Program.dnsserver);
#endif
#if USE_UNLINKD

    requirePathnameExists("unlinkd_program", Config.Program.unlinkd);
#endif
    requirePathnameExists("logfile_daemon", Log::TheConfig.logfile_daemon);
    if (Config.Program.redirect)
        requirePathnameExists("redirect_program", Config.Program.redirect->key);

    if (Config.Program.store_id)
        requirePathnameExists("store_id_program", Config.Program.store_id->key);

    requirePathnameExists("Icon Directory", Config.icons.directory);

    if (Config.errorDirectory)
        requirePathnameExists("Error Directory", Config.errorDirectory);

#if USE_HTTP_VIOLATIONS

    {
        const RefreshPattern *R;

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.override_expire)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'override-expire' in 'refresh_pattern' violates HTTP");

            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.override_lastmod)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'override-lastmod' in 'refresh_pattern' violates HTTP");

            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.reload_into_ims)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'reload-into-ims' in 'refresh_pattern' violates HTTP");

            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.ignore_reload)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'ignore-reload' in 'refresh_pattern' violates HTTP");

            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.ignore_no_store)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'ignore-no-store' in 'refresh_pattern' violates HTTP");

            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.ignore_must_revalidate)
                continue;
            debugs(22, DBG_IMPORTANT, "WARNING: use of 'ignore-must-revalidate' in 'refresh_pattern' violates HTTP");
            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.ignore_private)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'ignore-private' in 'refresh_pattern' violates HTTP");

            break;
        }

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.ignore_auth)
                continue;

            debugs(22, DBG_IMPORTANT, "WARNING: use of 'ignore-auth' in 'refresh_pattern' violates HTTP");

            break;
        }

    }
#endif
#if !USE_HTTP_VIOLATIONS
    Config.onoff.via = 1;
#else

    if (!Config.onoff.via)
        debugs(22, DBG_IMPORTANT, "WARNING: HTTP requires the use of Via");

#endif

    // we enable runtime PURGE checks if there is at least one PURGE method ACL
    // TODO: replace with a dedicated "purge" ACL option?
    Config2.onoff.enable_purge = (ACLMethodData::ThePurgeCount > 0);

    Config2.onoff.mangle_request_headers = (Config.request_header_access != NULL);

    if (geteuid() == 0) {
        if (NULL != Config.effectiveUser) {

            struct passwd *pwd = getpwnam(Config.effectiveUser);

            if (NULL == pwd) {
                /*
                 * Andres Kroonmaa <andre@online.ee>:
                 * Some getpwnam() implementations (Solaris?) require
                 * an available FD < 256 for opening a FILE* to the
                 * passwd file.
                 * DW:
                 * This should be safe at startup, but might still fail
                 * during reconfigure.
                 */
                fatalf("getpwnam failed to find userid for effective user '%s'",
                       Config.effectiveUser);
                return;
            }

            Config2.effectiveUserID = pwd->pw_uid;

            Config2.effectiveGroupID = pwd->pw_gid;

#if HAVE_PUTENV
            if (pwd->pw_dir && *pwd->pw_dir) {
                // putenv() leaks by design; avoid leaks when nothing changes
                static String lastDir;
                if (!lastDir.size() || lastDir != pwd->pw_dir) {
                    lastDir = pwd->pw_dir;
                    int len = strlen(pwd->pw_dir) + 6;
                    char *env_str = (char *)xcalloc(len, 1);
                    snprintf(env_str, len, "HOME=%s", pwd->pw_dir);
                    putenv(env_str);
                }
            }
#endif
        }
    } else {
        Config2.effectiveUserID = geteuid();
        Config2.effectiveGroupID = getegid();
    }

    if (NULL != Config.effectiveGroup) {

        struct group *grp = getgrnam(Config.effectiveGroup);

        if (NULL == grp) {
            fatalf("getgrnam failed to find groupid for effective group '%s'",
                   Config.effectiveGroup);
            return;
        }

        Config2.effectiveGroupID = grp->gr_gid;
    }

#if USE_SSL

    debugs(3, DBG_IMPORTANT, "Initializing https proxy context");

    Config.ssl_client.sslContext = sslCreateClientContext(Config.ssl_client.cert, Config.ssl_client.key, Config.ssl_client.version, Config.ssl_client.cipher, Config.ssl_client.options, Config.ssl_client.flags, Config.ssl_client.cafile, Config.ssl_client.capath, Config.ssl_client.crlfile);

    for (CachePeer *p = Config.peers; p != NULL; p = p->next) {
        if (p->use_ssl) {
            debugs(3, DBG_IMPORTANT, "Initializing cache_peer " << p->name << " SSL context");
            p->sslContext = sslCreateClientContext(p->sslcert, p->sslkey, p->sslversion, p->sslcipher, p->ssloptions, p->sslflags, p->sslcafile, p->sslcapath, p->sslcrlfile);
        }
    }

    for (AnyP::PortCfg *s = Config.Sockaddr.http; s != NULL; s = s->next) {
        if (!s->flags.tunnelSslBumping)
            continue;

        debugs(3, DBG_IMPORTANT, "Initializing http_port " << s->s << " SSL context");
        s->configureSslServerContext();
    }

    for (AnyP::PortCfg *s = Config.Sockaddr.https; s != NULL; s = s->next) {
        debugs(3, DBG_IMPORTANT, "Initializing https_port " << s->s << " SSL context");
        s->configureSslServerContext();
    }

#endif

    // prevent infinite fetch loops in the request parser
    // due to buffer full but not enough data recived to finish parse
    if (Config.maxRequestBufferSize <= Config.maxRequestHeaderSize) {
        fatalf("Client request buffer of %u bytes cannot hold a request with %u bytes of headers." \
               " Change client_request_buffer_max or request_header_max_size limits.",
               (uint32_t)Config.maxRequestBufferSize, (uint32_t)Config.maxRequestHeaderSize);
    }

    /*
     * Disable client side request pipelining if client_persistent_connections OFF.
     * Waste of resources queueing any pipelined requests when the first will close the connection.
     */
    if (Config.pipeline_max_prefetch > 0 && !Config.onoff.client_pconns) {
        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: pipeline_prefetch " << Config.pipeline_max_prefetch <<
               " requires client_persistent_connections ON. Forced pipeline_prefetch 0.");
        Config.pipeline_max_prefetch = 0;
    }

#if USE_AUTH
    /*
     * disable client side request pipelining. There is a race with
     * Negotiate and NTLM when the client sends a second request on an
     * connection before the authenticate challenge is sent. With
     * pipelining OFF, the client may fail to authenticate, but squid's
     * state will be preserved.
     */
    if (Config.pipeline_max_prefetch > 0) {
        Auth::Config *nego = Auth::Config::Find("Negotiate");
        Auth::Config *ntlm = Auth::Config::Find("NTLM");
        if ((nego && nego->active()) || (ntlm && ntlm->active())) {
            debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: pipeline_prefetch breaks NTLM and Negotiate authentication. Forced pipeline_prefetch 0.");
            Config.pipeline_max_prefetch = 0;
        }
    }
#endif
}