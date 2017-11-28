void
AuthDigestUserRequest::module_start(RH * handler, void *data)
{
    DigestAuthenticateStateData *r = NULL;
    char buf[8192];
    digest_user_h *digest_user;
    assert(user()->auth_type == AUTH_DIGEST);
    digest_user = dynamic_cast < digest_user_h * >(user());
    assert(digest_user != NULL);
    debugs(29, 9, "authenticateStart: '\"" << digest_user->username() << "\":\"" << realm << "\"'");

    if (digestConfig.authenticate == NULL) {
        handler(data, NULL);
        return;
    }

    r = cbdataAlloc(DigestAuthenticateStateData);
    r->handler = handler;
    r->data = cbdataReference(data);
    r->auth_user_request = this;
    AUTHUSERREQUESTLOCK(r->auth_user_request, "r");
    if (digestConfig.utf8) {
        char userstr[1024];
        latin1_to_utf8(userstr, sizeof(userstr), digest_user->username());
        snprintf(buf, 8192, "\"%s\":\"%s\"\n", userstr, realm);
    } else {
        snprintf(buf, 8192, "\"%s\":\"%s\"\n", digest_user->username(), realm);
    }

    helperSubmit(digestauthenticators, buf, authenticateDigestHandleReply, r);
}