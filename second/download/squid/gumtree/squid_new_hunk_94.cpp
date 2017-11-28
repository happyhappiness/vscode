    } else if (strcmp(token, "generate-host-certificates=on") == 0) {
        s->generateHostCertificates = true;
    } else if (strcmp(token, "generate-host-certificates=off") == 0) {
        s->generateHostCertificates = false;
    } else if (strncmp(token, "dynamic_cert_mem_cache_size=", 28) == 0) {
        parseBytesOptionValue(&s->dynamicCertMemCacheSize, B_BYTES_STR, token + 28);
#endif
    } else {
        self_destruct();
    }
}

void
add_http_port(char *portspec)
{
    AnyP::PortCfg *s = new AnyP::PortCfg("http_port");
    parsePortSpecification(s, portspec);
    // we may need to merge better if the above returns a list with clones
    assert(s->next == NULL);
    s->next = cbdataReference(Config.Sockaddr.http);
    cbdataReferenceDone(Config.Sockaddr.http);
    Config.Sockaddr.http = cbdataReference(s);
}

static void
parsePortCfg(AnyP::PortCfg ** head, const char *optionName)
{
    const char *protocol = NULL;
    if (strcmp(optionName, "http_port") == 0 ||
            strcmp(optionName, "ascii_port") == 0)
        protocol = "http";
    else if (strcmp(optionName, "https_port") == 0)
        protocol = "https";
    if (!protocol) {
        self_destruct();
        return;
    }

    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    AnyP::PortCfg *s = new AnyP::PortCfg(protocol);
    parsePortSpecification(s, token);

    /* parse options ... */
    while ((token = strtok(NULL, w_space))) {
        parse_port_option(s, token);
    }

    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && s->s.IsAnyAddr()) {
        // clone the port options from *s to *(s->next)
        s->next = cbdataReference(s->clone());
        s->next->s.SetIPv4();
        debugs(3, 3, protocol << "_port: clone wildcard address for split-stack: " << s->s << " and " << s->next->s);
    }

    while (*head)
        head = &(*head)->next;

    *head = cbdataReference(s);
}

static void
dump_generic_port(StoreEntry * e, const char *n, const AnyP::PortCfg * s)
{
    char buf[MAX_IPSTRLEN];

    storeAppendPrintf(e, "%s %s",
                      n,
                      s->s.ToURL(buf,MAX_IPSTRLEN));
