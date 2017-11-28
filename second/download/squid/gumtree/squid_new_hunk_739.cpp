}

#endif /* CURRENTLY_UNUSED */
#endif /* USE_WCCPv2 */

static void
parsePortSpecification(const AnyP::PortCfgPointer &s, char *token)
{
    char *host = NULL;
    unsigned short port = 0;
    char *t = NULL;
    char *junk = NULL;

    s->disable_pmtu_discovery = DISABLE_PMTU_OFF;
    s->name = xstrdup(token);
    s->connection_auth_disabled = false;

    const char *portType = AnyP::UriScheme(s->transport.protocol).c_str();

    if (*token == '[') {
        /* [ipv6]:port */
        host = token + 1;
        t = strchr(host, ']');
        if (!t) {
            debugs(3, DBG_CRITICAL, "FATAL: " << portType << "_port: missing ']' on IPv6 address: " << token);
            self_destruct();
        }
        *t = '\0';
        ++t;
        if (*t != ':') {
            debugs(3, DBG_CRITICAL, "FATAL: " << portType << "_port: missing Port in: " << token);
            self_destruct();
        }
        if (!Ip::EnableIpv6) {
            debugs(3, DBG_CRITICAL, "FATAL: " << portType << "_port: IPv6 is not available.");
            self_destruct();
        }
        port = xatos(t + 1);
    } else if ((t = strchr(token, ':'))) {
        /* host:port */
        /* ipv4:port */
        host = token;
        *t = '\0';
        port = xatos(t + 1);

    } else if (strtol(token, &junk, 10) && !*junk) {
        port = xatos(token);
        debugs(3, 3, portType << "_port: found Listen on Port: " << port);
    } else {
        debugs(3, DBG_CRITICAL, "FATAL: " << portType << "_port: missing Port: " << token);
        self_destruct();
    }

    if (port == 0 && host != NULL) {
        debugs(3, DBG_CRITICAL, "FATAL: " << portType << "_port: Port cannot be 0: " << token);
        self_destruct();
    }

    if (NULL == host) {
        s->s.setAnyAddr();
        s->s.port(port);
        if (!Ip::EnableIpv6)
            s->s.setIPv4();
        debugs(3, 3, portType << "_port: found Listen on wildcard address: *:" << s->s.port());
    } else if ( (s->s = host) ) { /* check/parse numeric IPA */
        s->s.port(port);
        if (!Ip::EnableIpv6)
            s->s.setIPv4();
        debugs(3, 3, portType << "_port: Listen on Host/IP: " << host << " --> " << s->s);
    } else if ( s->s.GetHostByName(host) ) { /* check/parse for FQDN */
        /* dont use ipcache */
        s->defaultsite = xstrdup(host);
        s->s.port(port);
        if (!Ip::EnableIpv6)
            s->s.setIPv4();
        debugs(3, 3, portType << "_port: found Listen as Host " << s->defaultsite << " on IP: " << s->s);
    } else {
        debugs(3, DBG_CRITICAL, "FATAL: " << portType << "_port: failed to resolve Host/IP: " << host);
        self_destruct();
    }
}

/// parses the protocol= option of the *_port directive, returning parsed value
/// unsupported option values result in a fatal error message
/// upper case values required; caller may convert for backward compatibility
static AnyP::ProtocolVersion
parsePortProtocol(const SBuf &value)
{
    // HTTP/1.0 not supported because we are version 1.1 which contains a superset of 1.0
    // and RFC 2616 requires us to upgrade 1.0 to 1.1
    if (value.cmp("HTTP") == 0 || value.cmp("HTTP/1.1") == 0)
        return AnyP::ProtocolVersion(AnyP::PROTO_HTTP, 1,1);

    if (value.cmp("HTTPS") == 0 || value.cmp("HTTPS/1.1") == 0)
        return AnyP::ProtocolVersion(AnyP::PROTO_HTTPS, 1,1);

    if (value.cmp("FTP") == 0)
        return Ftp::ProtocolVersion();

    fatalf("%s directive does not support protocol=" SQUIDSBUFPH "\n", cfg_directive, SQUIDSBUFPRINT(value));
    return AnyP::ProtocolVersion(); // not reached
}

static void
parse_port_option(AnyP::PortCfgPointer &s, char *token)
{
    /* modes first */

    if (strcmp(token, "accel") == 0) {
        if (s->flags.isIntercepted()) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": Accelerator mode requires its own port. It cannot be shared with other modes.");
            self_destruct();
        }
        s->flags.accelSurrogate = true;
        s->vhost = true;
    } else if (strcmp(token, "transparent") == 0 || strcmp(token, "intercept") == 0) {
        if (s->flags.accelSurrogate || s->flags.tproxyIntercept) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": Intercept mode requires its own interception port. It cannot be shared with other modes.");
            self_destruct();
        }
        s->flags.natIntercept = true;
        Ip::Interceptor.StartInterception();
        /* Log information regarding the port modes under interception. */
        debugs(3, DBG_IMPORTANT, "Starting Authentication on port " << s->s);
        debugs(3, DBG_IMPORTANT, "Disabling Authentication on port " << s->s << " (interception enabled)");
    } else if (strcmp(token, "tproxy") == 0) {
        if (s->flags.natIntercept || s->flags.accelSurrogate) {
            debugs(3,DBG_CRITICAL, "FATAL: " << cfg_directive << ": TPROXY option requires its own interception port. It cannot be shared with other modes.");
            self_destruct();
        }
        s->flags.tproxyIntercept = true;
        Ip::Interceptor.StartTransparency();
        /* Log information regarding the port modes under transparency. */
        debugs(3, DBG_IMPORTANT, "Disabling Authentication on port " << s->s << " (TPROXY enabled)");

        if (s->flags.proxySurrogate) {
            debugs(3, DBG_IMPORTANT, "Disabling TPROXY Spoofing on port " << s->s << " (require-proxy-header enabled)");
        }

        if (!Ip::Interceptor.ProbeForTproxy(s->s)) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": TPROXY support in the system does not work.");
            self_destruct();
        }

    } else if (strcmp(token, "require-proxy-header") == 0) {
        s->flags.proxySurrogate = true;
        if (s->flags.tproxyIntercept) {
            // receiving is still permitted, so we do not unset the TPROXY flag
            // spoofing access control override takes care of the spoof disable later
            debugs(3, DBG_IMPORTANT, "Disabling TPROXY Spoofing on port " << s->s << " (require-proxy-header enabled)");
        }

    } else if (strncmp(token, "defaultsite=", 12) == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": defaultsite option requires Acceleration mode flag.");
            self_destruct();
        }
        safe_free(s->defaultsite);
        s->defaultsite = xstrdup(token + 12);
    } else if (strcmp(token, "vhost") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "WARNING: " << cfg_directive << ": vhost option is deprecated. Use 'accel' mode flag instead.");
        }
        s->flags.accelSurrogate = true;
        s->vhost = true;
    } else if (strcmp(token, "no-vhost") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_IMPORTANT, "ERROR: " << cfg_directive << ": no-vhost option requires Acceleration mode flag.");
        }
        s->vhost = false;
    } else if (strcmp(token, "vport") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": vport option requires Acceleration mode flag.");
            self_destruct();
        }
        s->vport = -1;
    } else if (strncmp(token, "vport=", 6) == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": vport option requires Acceleration mode flag.");
            self_destruct();
        }
        s->vport = xatos(token + 6);
    } else if (strncmp(token, "protocol=", 9) == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": protocol option requires Acceleration mode flag.");
            self_destruct();
        }
        s->transport = parsePortProtocol(ToUpper(SBuf(token + 9)));
    } else if (strcmp(token, "allow-direct") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": allow-direct option requires Acceleration mode flag.");
            self_destruct();
        }
        s->allow_direct = true;
    } else if (strcmp(token, "act-as-origin") == 0) {
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_IMPORTANT, "ERROR: " << cfg_directive << ": act-as-origin option requires Acceleration mode flag.");
        } else
            s->actAsOrigin = true;
    } else if (strcmp(token, "ignore-cc") == 0) {
#if !USE_HTTP_VIOLATIONS
        if (!s->flags.accelSurrogate) {
            debugs(3, DBG_CRITICAL, "FATAL: " << cfg_directive << ": ignore-cc option requires Acceleration mode flag.");
            self_destruct();
        }
#endif
        s->ignore_cc = true;
    } else if (strncmp(token, "name=", 5) == 0) {
        safe_free(s->name);
