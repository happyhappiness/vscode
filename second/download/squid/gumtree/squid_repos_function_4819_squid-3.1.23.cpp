int
authenticateAuthUserRequestIPCount(AuthUserRequest * auth_user_request)
{
    assert(auth_user_request);
    assert(auth_user_request->user());
    return auth_user_request->user()->ipcount;
}