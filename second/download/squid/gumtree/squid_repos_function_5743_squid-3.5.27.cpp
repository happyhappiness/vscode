bool
Auth::UserRequest::valid() const
{
    debugs(29, 9, HERE << "Validating Auth::UserRequest '" << this << "'.");

    if (user() == NULL) {
        debugs(29, 4, HERE << "No associated Auth::User data");
        return false;
    }

    if (user()->auth_type == Auth::AUTH_UNKNOWN) {
        debugs(29, 4, HERE << "Auth::User '" << user() << "' uses unknown scheme.");
        return false;
    }

    if (user()->auth_type == Auth::AUTH_BROKEN) {
        debugs(29, 4, HERE << "Auth::User '" << user() << "' is broken for it's scheme.");
        return false;
    }

    /* any other sanity checks that we need in the future */

    /* finally return ok */
    debugs(29, 5, HERE << "Validated. Auth::UserRequest '" << this << "'.");
    return true;
}