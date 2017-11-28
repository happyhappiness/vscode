static void
decode_pub_auth(cachemgr_request * req)
{
    char *buf;
    const char *host_name;
    const char *time_str;
    const char *user_name;
    const char *passwd;

    debug("cmgr: decoding pub: '%s'\n", safe_str(req->pub_auth));
    safe_free(req->passwd);

    if (!req->pub_auth || strlen(req->pub_auth) < 4 + strlen(safe_str(req->hostname)))
        return;

    size_t decodedLen = BASE64_DECODE_LENGTH(strlen(req->pub_auth));
    buf = (char*)xmalloc(decodedLen);
    struct base64_decode_ctx ctx;
    base64_decode_init(&ctx);
    if (!base64_decode_update(&ctx, &decodedLen, reinterpret_cast<uint8_t*>(buf), strlen(req->pub_auth), reinterpret_cast<const uint8_t*>(req->pub_auth)) ||
            !base64_decode_final(&ctx)) {
        debug("cmgr: base64 decode failure. Incomplete auth token string.\n");
        xfree(buf);
        return;
    }

    debug("cmgr: length ok\n");

    /* parse ( a lot of memory leaks, but that is cachemgr style :) */
    if ((host_name = strtok(buf, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded host: '%s'\n", host_name);

    if ((time_str = strtok(NULL, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded time: '%s' (now: %d)\n", time_str, (int) now);

    if ((user_name = strtok(NULL, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded uname: '%s'\n", user_name);

    if ((passwd = strtok(NULL, "|")) == NULL) {
        xfree(buf);
        return;
    }

    debug("cmgr: decoded passwd: '%s'\n", passwd);

    /* verify freshness and validity */
    if (atoi(time_str) + passwd_ttl < now) {
        xfree(buf);
        return;
    }

    if (strcasecmp(host_name, req->hostname)) {
        xfree(buf);
        return;
    }

    debug("cmgr: verified auth. info.\n");

    /* ok, accept */
    safe_free(req->user_name);

    req->user_name = xstrdup(user_name);

    req->passwd = xstrdup(passwd);

    xfree(buf);
}