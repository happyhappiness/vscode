bool
Adaptation::ServiceConfig::grokUri(const char *value)
{
    // TODO: find core code that parses URLs and extracts various parts
    // AYJ: most of this is duplicate of URL::parse() in src/url.cc

    if (!value || !*value) {
        debugs(3, DBG_CRITICAL, HERE << cfg_filename << ':' << config_lineno << ": " <<
               "empty adaptation service URI");
        return false;
    }

    uri = value;

    // extract scheme and use it as the service_configConfig protocol
    const char *schemeSuffix = "://";
    const String::size_type schemeEnd = uri.find(schemeSuffix);
    if (schemeEnd != String::npos)
        protocol=uri.substr(0,schemeEnd);

    debugs(3, 5, HERE << cfg_filename << ':' << config_lineno << ": " <<
           "service protocol is " << protocol);

    if (protocol.size() == 0)
        return false;

    // skip scheme
    const char *s = uri.termedBuf() + protocol.size() + strlen(schemeSuffix);

    const char *e;

    bool have_port = false;

    int len = 0;
    if (*s == '[') {
        const char *t;
        if ((t = strchr(s, ']')) == NULL)
            return false;

        ++s;
        len = t - s;
        if ((e = strchr(t, ':')) != NULL) {
            have_port = true;
        } else if ((e = strchr(t, '/')) != NULL) {
            have_port = false;
        } else {
            return false;
        }
    } else {
        if ((e = strchr(s, ':')) != NULL) {
            have_port = true;
        } else if ((e = strchr(s, '/')) != NULL) {
            have_port = false;
        } else {
            return false;
        }
        len = e - s;
    }

    host.limitInit(s, len);
#if USE_OPENSSL
    if (secure.sslDomain.isEmpty())
        secure.sslDomain.assign(host.rawBuf(), host.size());
#endif
    s = e;

    port = -1;
    if (have_port) {
        ++s;

        if ((e = strchr(s, '/')) != NULL) {
            char *t;
            const unsigned long p = strtoul(s, &t, 0);

            if (p > 65535) // port value is too high
                return false;

            port = static_cast<int>(p);

            if (t != e) // extras after the port
                return false;

            s = e;

            if (s[0] != '/')
                return false;
        }
    }

    // if no port, the caller may use service_configConfigs or supply the default if neeeded

    ++s;
    e = strchr(s, '\0');
    len = e - s;

    if (len > 1024) {
        debugs(3, DBG_CRITICAL, HERE << cfg_filename << ':' << config_lineno << ": " <<
               "long resource name (>1024), probably wrong");
    }

    resource.limitInit(s, len + 1);
    return true;
}