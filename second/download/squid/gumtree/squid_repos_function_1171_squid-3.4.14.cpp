static void
parse_port_option(AnyP::PortCfg * s, char *token)
{
    /* modes first */

    if (strcmp(token, "accel") == 0) {
        if (s->flags.isIntercepted()) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: Accelerator mode requires its own port. It cannot be shared with other modes.");
            self_destruct();
        }
        s->flags.accelSurrogate = true;
        s->vhost = true;
    } else if (strcmp(token, "transparent") == 0 || strcmp(token, "intercept") == 0) {
        if (s->flags.accelSurrogate || s->flags.tproxyIntercept) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: Intercept mode requires its own interception port. It cannot be shared with other modes.");
            self_destruct();
        }
        s->flags.natIntercept = true;
        Ip::Interceptor.StartInterception();
        /* Log information regarding the port modes under interception. */
        debugs(3, DBG_IMPORTANT, "Starting Authentication on port " << s->s);
        debugs(3, DBG_IMPORTANT, "Disabling Authentication on port " << s->s << " (interception enabled)");
    } else if (strcmp(token, "tproxy") == 0) {
        if (s->flags.natIntercept || s->flags.accelSurrogate) {
            debugs(3,DBG_CRITICAL, "FATAL: http(s)_port: TPROXY option requires its own interception port. It cannot be shared with other modes.");
            self_destruct();
        }
        s->flags.tproxyIntercept = true;
        Ip::Interceptor.StartTransparency();
        /* Log information regarding the port modes under transparency. */
        debugs(3, DBG_IMPORTANT, "Disabling Authentication on port " << s->s << " (TPROXY enabled)");

        if (!Ip::Interceptor.ProbeForTproxy(s->s)) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: TPROXY support in the system does not work.");
            self_destruct();
        }

    } else if (strncmp(token, "defaultsite=", 12) == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: defaultsite option requires Acceleration mode flag.");
            self_destruct();
        }
        safe_free(s->defaultsite);
        s->defaultsite = xstrdup(token + 12);
    } else if (strcmp(token, "vhost") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "WARNING: http(s)_port: vhost option is deprecated. Use 'accel' mode flag instead.");
        }
        s->flags.accelSurrogate = true;
        s->vhost = true;
    } else if (strcmp(token, "no-vhost") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_IMPORTANT, "ERROR: http(s)_port: no-vhost option requires Acceleration mode flag.");
        }
        s->vhost = false;
    } else if (strcmp(token, "vport") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: vport option requires Acceleration mode flag.");
            self_destruct();
        }
        s->vport = -1;
    } else if (strncmp(token, "vport=", 6) == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: vport option requires Acceleration mode flag.");
            self_destruct();
        }
        s->vport = xatos(token + 6);
    } else if (strncmp(token, "protocol=", 9) == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: protocol option requires Acceleration mode flag.");
            self_destruct();
        }
        s->protocol = xstrdup(token + 9);
    } else if (strcmp(token, "allow-direct") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: allow-direct option requires Acceleration mode flag.");
            self_destruct();
        }
        s->allow_direct = true;
    } else if (strcmp(token, "act-as-origin") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_IMPORTANT, "ERROR: http(s)_port: act-as-origin option requires Acceleration mode flag.");
        } else
            s->actAsOrigin = true;
    } else if (strcmp(token, "ignore-cc") == 0) {
#if !USE_HTTP_VIOLATIONS
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: ignore-cc option requires Acceleration mode flag.");
            self_destruct();
        }
#endif
        s->ignore_cc = true;
    } else if (strncmp(token, "name=", 5) == 0) {
        safe_free(s->name);
        s->name = xstrdup(token + 5);
    } else if (strcmp(token, "no-connection-auth") == 0) {
        s->connection_auth_disabled = true;
    } else if (strcmp(token, "connection-auth=off") == 0) {
        s->connection_auth_disabled = true;
    } else if (strcmp(token, "connection-auth") == 0) {
        s->connection_auth_disabled = false;
    } else if (strcmp(token, "connection-auth=on") == 0) {
        s->connection_auth_disabled = false;
    } else if (strncmp(token, "disable-pmtu-discovery=", 23) == 0) {
        if (!strcmp(token + 23, "off"))
            s->disable_pmtu_discovery = DISABLE_PMTU_OFF;
        else if (!strcmp(token + 23, "transparent"))
            s->disable_pmtu_discovery = DISABLE_PMTU_TRANSPARENT;
        else if (!strcmp(token + 23, "always"))
            s->disable_pmtu_discovery = DISABLE_PMTU_ALWAYS;
        else
            self_destruct();
    } else if (strcmp(token, "ipv4") == 0) {
        if ( !s->s.setIPv4() ) {
            debugs(3, DBG_CRITICAL, "FATAL: http(s)_port: IPv6 addresses cannot be used as IPv4-Only. " << s->s );
            self_destruct();
        }
    } else if (strcmp(token, "tcpkeepalive") == 0) {
        s->tcp_keepalive.enabled = true;
    } else if (strncmp(token, "tcpkeepalive=", 13) == 0) {
        char *t = token + 13;
        s->tcp_keepalive.enabled = true;
        s->tcp_keepalive.idle = xatoui(t,',');
        t = strchr(t, ',');
        if (t) {
            ++t;
            s->tcp_keepalive.interval = xatoui(t,',');
            t = strchr(t, ',');
        }
        if (t) {
            ++t;
            s->tcp_keepalive.timeout = xatoui(t);
        }
#if USE_SSL
    } else if (strcmp(token, "sslBump") == 0) {
        debugs(3, DBG_CRITICAL, "WARNING: '" << token << "' is deprecated " <<
               "in http_port. Use 'ssl-bump' instead.");
        s->flags.tunnelSslBumping = true;
    } else if (strcmp(token, "ssl-bump") == 0) {
        s->flags.tunnelSslBumping = true;
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
#endif
    } else {
        debugs(3, DBG_CRITICAL, "FATAL: Unknown http(s)_port option '" << token << "'.");
        self_destruct();
    }
}