void
AuthUser::unlock()
{
    debugs(29, 9, "authenticateAuthUserUnlock auth_user '" << this << "'.");
    assert(this != NULL);

    if (references > 0) {
        references--;
    } else {
        debugs(29, 1, "Attempt to lower Auth User " << this << " refcount below 0!");
    }

    debugs(29, 9, "authenticateAuthUserUnlock auth_user '" << this << "' now at '" << references << "'.");

    if (references == 0)
        delete this;
}