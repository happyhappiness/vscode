Auth::Direction
Auth::UserRequest::direction()
{
    if (user() == NULL)
        return Auth::CRED_ERROR; // No credentials. Should this be a CHALLENGE instead?

    if (authenticateUserAuthenticated(this))
        return Auth::CRED_VALID;

    return module_direction();
}