static url_entry *
urnParseReply(const char *inbuf, const HttpRequestMethod& m)
{
    char *buf = xstrdup(inbuf);
    char *token;
    char *url;
    char *host;
    url_entry *list;
    url_entry *old;
    int n = 32;
    int i = 0;
    debugs(52, 3, "urnParseReply");
    list = (url_entry *)xcalloc(n + 1, sizeof(*list));

    for (token = strtok(buf, crlf); token; token = strtok(NULL, crlf)) {
        debugs(52, 3, "urnParseReply: got '" << token << "'");

        if (i == n) {
            old = list;
            n <<= 2;
            list = (url_entry *)xcalloc(n + 1, sizeof(*list));
            memcpy(list, old, i * sizeof(*list));
            safe_free(old);
        }

        url = xstrdup(token);
        host = urlHostname(url);

        if (NULL == host)
            continue;

#if USE_ICMP
        list[i].rtt = netdbHostRtt(host);

        if (0 == list[i].rtt) {
            debugs(52, 3, "urnParseReply: Pinging " << host);
            netdbPingSite(host);
        }
#else
        list[i].rtt = 0;
#endif

        list[i].url = url;
        list[i].host = xstrdup(host);
        // TODO: Use storeHas() or lock/unlock entry to avoid creating unlocked
        // ones.
        list[i].flags.cached = storeGetPublic(url, m) ? 1 : 0;
        ++i;
    }

    debugs(52, 3, "urnParseReply: Found " << i << " URLs");
    return list;
}