void
HttpRequest::clean()
{
    // we used to assert that the pipe is NULL, but now the request only
    // points to a pipe that is owned and initiated by another object.
    body_pipe = NULL;

    AUTHUSERREQUESTUNLOCK(auth_user_request, "request");

    safe_free(canonical);

    safe_free(vary_headers);

    urlpath.clean();

    header.clean();

    if (cache_control) {
        httpHdrCcDestroy(cache_control);
        cache_control = NULL;
    }

    if (range) {
        delete range;
        range = NULL;
    }

    if (pinned_connection)
        cbdataReferenceDone(pinned_connection);

    myportname.clean();

    tag.clean();

    extacl_user.clean();

    extacl_passwd.clean();

    extacl_log.clean();

    extacl_message.clean();

#if USE_ADAPTATION
    adaptHistory_ = NULL;
#endif
#if ICAP_CLIENT
    icapHistory_ = NULL;
#endif
}