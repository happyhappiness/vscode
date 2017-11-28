static void
make_pub_auth(cachemgr_request * req)
{
    static char buf[1024];
    safe_free(req->pub_auth);
    debug("cmgr: encoding for pub...\n");

    if (!req->passwd || !strlen(req->passwd))
        return;

    /* host | time | user | passwd */
    const int bufLen = snprintf(buf, sizeof(buf), "%s|%d|%s|%s",
                                req->hostname,
                                (int) now,
                                req->user_name ? req->user_name : "",
                                req->passwd);
    debug("cmgr: pre-encoded for pub: %s\n", buf);

    const int encodedLen = base64_encode_len(bufLen);
    req->pub_auth = (char *) xmalloc(encodedLen);
    base64_encode_str(req->pub_auth, encodedLen, buf, bufLen);
    debug("cmgr: encoded: '%s'\n", req->pub_auth);
}