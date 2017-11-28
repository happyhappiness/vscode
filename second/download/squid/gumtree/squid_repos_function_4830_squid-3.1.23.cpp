int
authenticateDirection(AuthUserRequest * auth_user_request)
{
    if (!auth_user_request)
        return -2;

    return auth_user_request->direction();
}