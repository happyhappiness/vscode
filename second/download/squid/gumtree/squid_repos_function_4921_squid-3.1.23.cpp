void
AuthNTLMUserRequest::module_start(RH * handler, void *data)
{
    authenticateStateData *r = NULL;
    static char buf[8192];
    AuthUser *auth_user = user();

    assert(data);
    assert(handler);
    assert(auth_user);
    assert(auth_user->auth_type == AUTH_NTLM);

    debugs(29, 8, "AuthNTLMUserRequest::module_start: auth state is '" << auth_state << "'");

    if (ntlmConfig.authenticate == NULL) {
        debugs(29, 0, "AuthNTLMUserRequest::module_start: no NTLM program specified.");
        handler(data, NULL);
        return;
    }

    r = cbdataAlloc(authenticateStateData);
    r->handler = handler;
    r->data = cbdataReference(data);
    r->auth_user_request = this;
    AUTHUSERREQUESTLOCK(r->auth_user_request, "r");

    if (auth_state == AUTHENTICATE_STATE_INITIAL) {
        snprintf(buf, 8192, "YR %s\n", client_blob); //CHECKME: can ever client_blob be 0 here?
    } else {
        snprintf(buf, 8192, "KK %s\n", client_blob);
    }

    waiting = 1;

    safe_free(client_blob);
    helperStatefulSubmit(ntlmauthenticators, buf, authenticateNTLMHandleReply, r, authserver);
}