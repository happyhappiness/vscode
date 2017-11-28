void
parse_obsolete(const char *name)
{
    // Directives which have been radically changed rather than removed
    if (!strcmp(name, "url_rewrite_concurrency")) {
        int cval;
        parse_int(&cval);
        debugs(3, DBG_CRITICAL, "WARNING: url_rewrite_concurrency upgrade overriding url_rewrite_children settings.");
        Config.redirectChildren.concurrency = cval;
    }

    if (!strcmp(name, "log_access")) {
        self_destruct();
        return;
    }

    if (!strcmp(name, "log_icap")) {
        self_destruct();
        return;
    }

    if (!strcmp(name, "ignore_ims_on_miss")) {
        // the replacement directive cache_revalidate_on_miss has opposite meanings for ON/OFF value
        // than the 2.7 directive. We need to parse and invert the configured value.
        int temp = 0;
        parse_onoff(&temp);
        Config.onoff.cache_miss_revalidate = !temp;
    }

    if (!strncmp(name, "sslproxy_", 9)) {
        // the replacement directive tls_outgoing_options uses options instead of whole-line input
        SBuf tmp;
        if (!strcmp(name, "sslproxy_cafile"))
            tmp.append("cafile=");
        else if (!strcmp(name, "sslproxy_capath"))
            tmp.append("capath=");
        else if (!strcmp(name, "sslproxy_cipher"))
            tmp.append("cipher=");
        else if (!strcmp(name, "sslproxy_client_certificate"))
            tmp.append("cert=");
        else if (!strcmp(name, "sslproxy_client_key"))
            tmp.append("key=");
        else if (!strcmp(name, "sslproxy_flags"))
            tmp.append("flags=");
        else if (!strcmp(name, "sslproxy_options"))
            tmp.append("options=");
        else if (!strcmp(name, "sslproxy_version"))
            tmp.append("version=");
        else {
            debugs(3, DBG_CRITICAL, "ERROR: unknown directive: " << name);
            self_destruct();
            return;
        }

        // add the value as unquoted-string because the old values did not support whitespace
        const char *token = ConfigParser::NextQuotedOrToEol();
        tmp.append(token, strlen(token));
        Security::ProxyOutgoingConfig.parse(tmp.c_str());
    }
}