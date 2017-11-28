int
AuthUserRequest::direction()
{
    if (authenticateUserAuthenticated(this))
        return 0;

    return module_direction();

    return -2;
}