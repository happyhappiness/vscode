void
AuthUserRequest::start(RH * handler, void *data)
{
    assert(handler);
    debugs(29, 9, "authenticateStart: auth_user_request '" << this << "'");
    module_start(handler, data);
}