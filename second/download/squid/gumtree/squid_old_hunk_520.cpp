
    helperSubmit(digestauthenticators, buf, Auth::Digest::UserRequest::HandleReply,
                 new Auth::StateData(this, handler, data));
}

void
Auth::Digest::UserRequest::HandleReply(void *data, char *reply)
{
    Auth::StateData *replyData = static_cast<Auth::StateData *>(data);
    char *t = NULL;
    void *cbdata;
    debugs(29, 9, HERE << "{" << (reply ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' '))) {
            *t = '\0';
            ++t;
        }

        if (*reply == '\0' || *reply == '\n')
            reply = NULL;
    }

    assert(replyData->auth_user_request != NULL);
    Auth::UserRequest::Pointer auth_user_request = replyData->auth_user_request;

    if (reply && (strncasecmp(reply, "ERR", 3) == 0)) {
        /* allow this because the digest_request pointer is purely local */
        Auth::Digest::UserRequest *digest_request = dynamic_cast<Auth::Digest::UserRequest *>(auth_user_request.getRaw());
        assert(digest_request);

        digest_request->user()->credentials(Auth::Failed);
        digest_request->flags.invalid_password = 1;

        if (t && *t)
            digest_request->setDenyMessage(t);
    } else if (reply) {
        /* allow this because the digest_request pointer is purely local */
        Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User *>(auth_user_request->user().getRaw());
        assert(digest_user != NULL);

        CvtBin(reply, digest_user->HA1);
        digest_user->HA1created = 1;
    }

    if (cbdataReferenceValidDone(replyData->data, &cbdata))
        replyData->handler(cbdata);

    delete replyData;
}
