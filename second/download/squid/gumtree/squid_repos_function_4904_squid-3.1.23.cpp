void
AuthBasicUserRequest::module_start(RH * handler, void *data)
{
    basic_data *basic_auth;
    assert(user()->auth_type == AUTH_BASIC);
    basic_auth = dynamic_cast<basic_data *>(user());
    assert(basic_auth != NULL);
    debugs(29, 9, HERE << "'" << basic_auth->username() << ":" << basic_auth->passwd << "'");

    if (basicConfig.authenticate == NULL) {
        handler(data, NULL);
        return;
    }

    /* check to see if the auth_user already has a request outstanding */
    if (basic_auth->flags.credentials_ok == 2) {
        /* there is a request with the same credentials already being verified */
        basic_auth->queueRequest(this, handler, data);
        return;
    }

    basic_auth->submitRequest (this, handler, data);
}