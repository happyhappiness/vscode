int
authenticateUserAuthenticated(AuthUserRequest * auth_user_request)
{
    if (!authenticateValidateUser(auth_user_request))
        return 0;

    return auth_user_request->authenticated();
}