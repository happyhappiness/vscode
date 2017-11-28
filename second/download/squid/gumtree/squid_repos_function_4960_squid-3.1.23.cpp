static void
authenticateDigestHandleReply(void *data, char *reply)
{
    DigestAuthenticateStateData *replyData = static_cast < DigestAuthenticateStateData * >(data);
    AuthUserRequest *auth_user_request;
    AuthDigestUserRequest *digest_request;
    digest_user_h *digest_user;
    char *t = NULL;
    void *cbdata;
    debugs(29, 9, "authenticateDigestHandleReply: {" << (reply ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' ')))
            *t++ = '\0';

        if (*reply == '\0' || *reply == '\n')
            reply = NULL;
    }

    assert(replyData->auth_user_request != NULL);
    auth_user_request = replyData->auth_user_request;
    digest_request = dynamic_cast < AuthDigestUserRequest * >(auth_user_request);
    assert(digest_request);

    digest_user = dynamic_cast < digest_user_h * >(auth_user_request->user());
    assert(digest_user != NULL);

    if (reply && (strncasecmp(reply, "ERR", 3) == 0)) {
        digest_request->credentials(AuthDigestUserRequest::Failed);
        digest_request->flags.invalid_password = 1;

        if (t && *t)
            digest_request->setDenyMessage(t);
    } else if (reply) {
        CvtBin(reply, digest_user->HA1);
        digest_user->HA1created = 1;
    }

    if (cbdataReferenceValidDone(replyData->data, &cbdata))
        replyData->handler(cbdata, NULL);

    //we know replyData->auth_user_request != NULL, or we'd have asserted
    AUTHUSERREQUESTUNLOCK(replyData->auth_user_request, "replyData");

    cbdataFree(replyData);
}