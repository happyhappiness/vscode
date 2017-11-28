void
AuthNegotiateUserRequest::module_start(RH * handler, void *data)
{
    authenticateStateData *r = NULL;
    static char buf[MAX_AUTHTOKEN_LEN];
    AuthUser *auth_user = user();

    assert(data);
    assert(handler);
    assert(auth_user);
    assert(auth_user->auth_type == AUTH_NEGOTIATE);

    debugs(29, 8, "AuthNegotiateUserRequest::module_start: auth state is '" << auth_state << "'");

    if (negotiateConfig.authenticate == NULL) {
        debugs(29, 0, "AuthNegotiateUserRequest::module_start: no Negotiate program specified.");
        handler(data, NULL);
        return;
    }

    r = cbdataAlloc(authenticateStateData);
    r->handler = handler;
    r->data = cbdataReference(data);
    r->auth_user_request = this;
    AUTHUSERREQUESTLOCK(r->auth_user_request, "r");

    if (auth_state == AUTHENTICATE_STATE_INITIAL) {
        snprintf(buf, MAX_AUTHTOKEN_LEN, "YR %s\n", client_blob); //CHECKME: can ever client_blob be 0 here?
    } else {
        snprintf(buf, MAX_AUTHTOKEN_LEN, "KK %s\n", client_blob);
    }

    waiting = 1;

    safe_free(client_blob);
    helperStatefulSubmit(negotiateauthenticators, buf, authenticateNegotiateHandleReply, r, authserver);
}