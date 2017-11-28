static void
authenticateAuthenticateUser(Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, ConnStateData * conn, Http::HdrType type)
{
    assert(auth_user_request.getRaw() != NULL);

    auth_user_request->authenticate(request, conn, type);
}