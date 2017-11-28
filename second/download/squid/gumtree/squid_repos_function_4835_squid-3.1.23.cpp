void
AuthUserRequest::_unlock()
{
    assert(this != NULL);

    if (references > 0) {
        debugs(29, 9, "AuthUserRequest::unlock: auth_user request '" << this << " " << references << "->" << references-1);
        --references;
    } else {
        debugs(29, 1, "Attempt to lower Auth User request " << this << " refcount below 0!");
    }

    if (references == 0) {
        debugs(29, 9, "AuthUserRequest::unlock: deleting auth_user_request '" << this << "'.");
        /* not locked anymore */
        delete this;
    }
}