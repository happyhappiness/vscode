static void
parse_http_port_option(http_port_list * s, char *token)
{
    if (strncmp(token, "defaultsite=", 12) == 0) {
        safe_free(s->defaultsite);
        s->defaultsite = xstrdup(token + 12);
        s->accel = 1;
    } else if (strncmp(token, "name=", 5) == 0) {
        safe_free(s->name);
        s->name = xstrdup(token + 5);
    } else if (strcmp(token, "vhost") == 0) {
        s->vhost = 1;
        s->accel = 1;
    } else if (strcmp(token, "vport") == 0) {
        s->vport = -1;
        s->accel = 1;
    } else if (strncmp(token, "vport=", 6) == 0) {
        s->vport = xatos(token + 6);
        s->accel = 1;
    } else if (strncmp(token, "protocol=", 9) == 0) {
        s->protocol = xstrdup(token + 9);
        s->accel = 1;
    } else if (strcmp(token, "accel") == 0) {
        s->accel = 1;
    } else if (strcmp(token, "allow-direct") == 0) {
        s->allow_direct = 1;
    } else if (strcmp(token, "ignore-cc") == 0) {
        s->ignore_cc = 1;
#if !HTTP_VIOLATIONS
        if (!s->accel) {
            debugs(3, DBG_CRITICAL, "FATAL: ignore-cc is only valid in accelerator mode");
            self_destruct();
        }
#endif
    } else if (strcmp(token, "no-connection-auth") == 0) {
        s->connection_auth_disabled = true;
    } else if (strcmp(token, "connection-auth=off") == 0) {
        s->connection_auth_disabled = true;
    } else if (strcmp(token, "connection-auth") == 0) {
        s->connection_auth_disabled = false;
    } else if (strcmp(token, "connection-auth=on") == 0) {
        s->connection_auth_disabled = false;
    } else if (strncmp(token, "disable-pmtu-discovery=", 23) == 0) {
        if (!strcasecmp(token + 23, "off"))
            s->disable_pmtu_discovery = DISABLE_PMTU_OFF;
        else if (!strcasecmp(token + 23, "transparent"))
            s->disable_pmtu_discovery = DISABLE_PMTU_TRANSPARENT;
        else if (!strcasecmp(token + 23, "always"))
            s->disable_pmtu_discovery = DISABLE_PMTU_ALWAYS;
        else
            self_destruct();

    } else if (strcmp(token, "transparent") == 0 || strcmp(token, "intercept") == 0) {
        s->intercepted = 1;
        IpInterceptor.StartInterception();
        /* Log information regarding the port modes under interception. */
        debugs(3, DBG_IMPORTANT, "Starting Authentication on port " << s->s);
        debugs(3, DBG_IMPORTANT, "Disabling Authentication on port " << s->s << " (interception enabled)");

        /* INET6: until transparent REDIRECT works on IPv6 SOCKET, force wildcard to IPv4 */
        if (Ip::EnableIpv6)
            debugs(3, DBG_IMPORTANT, "Disabling IPv6 on port " << s->s << " (interception enabled)");
        if ( !s->s.SetIPv4() ) {
            debugs(3, DBG_CRITICAL, "http(s)_port: IPv6 addresses cannot be transparent (protocol does not provide NAT)" << s->s );
            self_destruct();
        }
    } else if (strcmp(token, "tproxy") == 0) {
        if (s->intercepted || s->accel) {
            debugs(3,DBG_CRITICAL, "http(s)_port: TPROXY option requires its own interception port. It cannot be shared.");
            self_destruct();
        }
        s->spoof_client_ip = 1;
        IpInterceptor.StartTransparency();
        /* Log information regarding the port modes under transparency. */
        debugs(3, DBG_IMPORTANT, "Starting IP Spoofing on port " << s->s);
        debugs(3, DBG_IMPORTANT, "Disabling Authentication on port " << s->s << " (IP spoofing enabled)");

        if (!IpInterceptor.ProbeForTproxy(s->s)) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: TPROXY support in the system does not work.");
            self_destruct();
        }

    } else if (strcmp(token, "ipv4") == 0) {
        if ( !s->s.SetIPv4() ) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: IPv6 addresses cannot be used as IPv4-Only. " << s->s );
            self_destruct();
        }
    } else if (strcmp(token, "tcpkeepalive") == 0) {
        s->tcp_keepalive.enabled = 1;
    } else if (strncmp(token, "tcpkeepalive=", 13) == 0) {
        char *t = token + 13;
        s->tcp_keepalive.enabled = 1;
        s->tcp_keepalive.idle = atoi(t);
        t = strchr(t, ',');
        if (t) {
            t++;
            s->tcp_keepalive.interval = atoi(t);
            t = strchr(t, ',');
        }
        if (t) {
            t++;
            s->tcp_keepalive.timeout = atoi(t);
            t = strchr(t, ',');
        }
#if USE_SSL
    } else if (strncmp(token, "cert=", 5) == 0) {
        safe_free(s->cert);
        s->cert = xstrdup(token + 5);
    } else if (strncmp(token, "key=", 4) == 0) {
        safe_free(s->key);
        s->key = xstrdup(token + 4);
    } else if (strncmp(token, "version=", 8) == 0) {
        s->version = xatoi(token + 8);

        if (s->version < 1 || s->version > 4)
            self_destruct();
    } else if (strncmp(token, "options=", 8) == 0) {
        safe_free(s->options);
        s->options = xstrdup(token + 8);
    } else if (strncmp(token, "cipher=", 7) == 0) {
        safe_free(s->cipher);
        s->cipher = xstrdup(token + 7);
    } else if (strncmp(token, "clientca=", 9) == 0) {
        safe_free(s->clientca);
        s->clientca = xstrdup(token + 9);
    } else if (strncmp(token, "cafile=", 7) == 0) {
        safe_free(s->cafile);
        s->cafile = xstrdup(token + 7);
    } else if (strncmp(token, "capath=", 7) == 0) {
        safe_free(s->capath);
        s->capath = xstrdup(token + 7);
    } else if (strncmp(token, "crlfile=", 8) == 0) {
        safe_free(s->crlfile);
        s->crlfile = xstrdup(token + 8);
    } else if (strncmp(token, "dhparams=", 9) == 0) {
        safe_free(s->dhfile);
        s->dhfile = xstrdup(token + 9);
    } else if (strncmp(token, "sslflags=", 9) == 0) {
        safe_free(s->sslflags);
        s->sslflags = xstrdup(token + 9);
    } else if (strncmp(token, "sslcontext=", 11) == 0) {
        safe_free(s->sslContextSessionId);
        s->sslContextSessionId = xstrdup(token + 11);
    } else if (strcmp(token, "generate-host-certificates") == 0) {
        s->generateHostCertificates = true;
    } else if (strcmp(token, "generate-host-certificates=on") == 0) {
        s->generateHostCertificates = true;
    } else if (strcmp(token, "generate-host-certificates=off") == 0) {
        s->generateHostCertificates = false;
    } else if (strncmp(token, "dynamic_cert_mem_cache_size=", 28) == 0) {
        parseBytesOptionValue(&s->dynamicCertMemCacheSize, B_BYTES_STR, token + 28);
    } else if (strcasecmp(token, "sslBump") == 0) {
        debugs(3, DBG_CRITICAL, "WARNING: '" << token << "' is deprecated " <<
               "in http_port. Use 'ssl-bump' instead.");
        s->sslBump = 1; // accelerated when bumped, otherwise not
    } else if (strcmp(token, "ssl-bump") == 0) {
        s->sslBump = 1; // accelerated when bumped, otherwise not
#endif
    } else {
        self_destruct();
    }

    if ( s->spoof_client_ip && (s->intercepted || s->accel) ) {
        debugs(3,DBG_CRITICAL, "http(s)_port: TPROXY option requires its own interception port. It cannot be shared.");
        self_destruct();
    }
}