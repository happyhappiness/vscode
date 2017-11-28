void
HttpRequest::clean()
{
    // we used to assert that the pipe is NULL, but now the request only
    // points to a pipe that is owned and initiated by another object.
    body_pipe = NULL;
#if USE_AUTH
    auth_user_request = NULL;
#endif
    safe_free(canonical);

    safe_free(vary_headers);

    urlpath.clean();

    header.clean();

    if (cache_control) {
        delete cache_control;
        cache_control = NULL;
    }

    if (range) {
        delete range;
        range = NULL;
    }

    myportname.clean();

    notes = NULL;

    tag.clean();
#if USE_AUTH
    extacl_user.clean();
    extacl_passwd.clean();
#endif
    extacl_log.clean();

    extacl_message.clean();

    etag.clean();

#if USE_ADAPTATION
    adaptHistory_ = NULL;
#endif
#if ICAP_CLIENT
    icapHistory_ = NULL;
#endif
}