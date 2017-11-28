void
authenticateAddTrailer(HttpReply * rep, Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, int accelerated)
{
    if (auth_user_request != NULL)
        auth_user_request->addAuthenticationInfoTrailer(rep, accelerated);
}