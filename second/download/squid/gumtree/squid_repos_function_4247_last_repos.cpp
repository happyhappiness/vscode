void
ACLFilledChecklist::syncAle() const
{
    // make sure the ALE fields used by Format::assemble to
    // fill the old external_acl_type codes are set if any
    // data on them exists in the Checklist

    if (!al->cache.port && conn()) {
        showDebugWarning("listening port");
        al->cache.port = conn()->port;
    }

    if (request) {
        if (!al->request) {
            showDebugWarning("HttpRequest object");
            al->request = request;
            HTTPMSGLOCK(al->request);
        }

        if (!al->adapted_request) {
            showDebugWarning("adapted HttpRequest object");
            al->adapted_request = request;
            HTTPMSGLOCK(al->adapted_request);
        }

        if (al->url.isEmpty()) {
            showDebugWarning("URL");
            al->url = request->url.absolute();
        }
    }

    if (reply && !al->reply) {
        showDebugWarning("HttpReply object");
        al->reply = reply;
        HTTPMSGLOCK(al->reply);
    }

#if USE_IDENT
    if (*rfc931 && !al->cache.rfc931) {
        showDebugWarning("IDENT");
        al->cache.rfc931 = xstrdup(rfc931);
    }
#endif
}