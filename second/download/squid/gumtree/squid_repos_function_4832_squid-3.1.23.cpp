void
authenticateFixHeader(HttpReply * rep, AuthUserRequest * auth_user_request, HttpRequest * request, int accelerated, int internal)
{
    AuthUserRequest::addReplyAuthHeader(rep, auth_user_request, request, accelerated, internal);
}