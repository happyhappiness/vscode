AuthScheme *
AuthUserRequest::scheme() const
{
    /* TODO: this should be overriden by the child and be essentially a no-op */
    return AuthScheme::Find(user()->config->type());
}