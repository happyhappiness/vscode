void
Auth::UserRequest::start(AUTHCB * handler, void *data)
{
    assert(handler);
    assert(data);
    debugs(29, 9, HERE << "auth_user_request '" << this << "'");
    module_start(handler, data);
}