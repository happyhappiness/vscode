void
authenticateAddTrailer(HttpReply * rep, AuthUserRequest * auth_user_request, HttpRequest * request, int accelerated)
{
    if (auth_user_request != NULL)
        auth_user_request->addTrailer(rep, accelerated);
}