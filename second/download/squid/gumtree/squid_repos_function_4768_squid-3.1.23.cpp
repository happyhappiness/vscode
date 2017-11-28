void
AuthUser::lock()
{
    debugs(29, 9, "authenticateAuthUserLock auth_user '" << this << "'.");
    assert(this != NULL);
    references++;
    debugs(29, 9, "authenticateAuthUserLock auth_user '" << this << "' now at '" << references << "'.");
}