void
BasicUser::submitRequest(AuthUserRequest * auth_user_request, RH * handler, void *data)
{
    /* mark the user as haveing verification in progress */
    flags.credentials_ok = 2;
    AuthenticateStateData *r = NULL;
    char buf[8192];
    char user[1024], pass[1024];
    r = cbdataAlloc(AuthenticateStateData);
    r->handler = handler;
    r->data = cbdataReference(data);
    r->auth_user_request = auth_user_request;
    if (basicConfig.utf8) {
        latin1_to_utf8(user, sizeof(user), username());
        latin1_to_utf8(pass, sizeof(pass), passwd);
        xstrncpy(user, rfc1738_escape(user), sizeof(user));
        xstrncpy(pass, rfc1738_escape(pass), sizeof(pass));
    } else {
        xstrncpy(user, rfc1738_escape(username()), sizeof(user));
        xstrncpy(pass, rfc1738_escape(passwd), sizeof(pass));
    }
    snprintf(buf, sizeof(buf), "%s %s\n", user, pass);
    helperSubmit(basicauthenticators, buf, authenticateBasicHandleReply, r);
}