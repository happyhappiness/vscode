void

AuthUserRequest::_lock()
{
    assert(this);
    debugs(29, 9, "AuthUserRequest::lock: auth_user request '" << this << " " << references << "->" << references+1);
    ++references;
}