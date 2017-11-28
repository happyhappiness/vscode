int
authenticateAuthUserRequestIPCount(Auth::UserRequest::Pointer auth_user_request)
{
    assert(auth_user_request != NULL);
    assert(auth_user_request->user() != NULL);
    return auth_user_request->user()->ipcount;
}