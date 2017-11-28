static void
make_pub_auth(cachemgr_request * req)
{
    static char buf[1024];
    safe_free(req->pub_auth);
    debug(3) fprintf(stderr, "cmgr: encoding for pub...\n");

    if (!req->passwd || !strlen(req->passwd))
        return;

    /* host | time | user | passwd */
    snprintf(buf, sizeof(buf), "%s|%d|%s|%s",
             req->hostname,
             (int) now,
             req->user_name ? req->user_name : "",
             req->passwd);

    debug(3) fprintf(stderr, "cmgr: pre-encoded for pub: %s\n", buf);

    debug(3) fprintf(stderr, "cmgr: encoded: '%s'\n", base64_encode(buf));

    req->pub_auth = xstrdup(base64_encode(buf));
}