int
authenticateAuthUserInuse(AuthUser * auth_user)
{
    assert(auth_user != NULL);
    return auth_user->references;
}