static void
authenticateAuthenticateUser(AuthUserRequest * auth_user_request, HttpRequest * request, ConnStateData * conn, http_hdr_type type)
{
    assert(auth_user_request != NULL);

    auth_user_request->authenticate(request, conn, type);
}