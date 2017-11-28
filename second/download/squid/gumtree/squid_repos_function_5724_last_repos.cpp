void
authenticateFixHeader(HttpReply * rep, Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, int accelerated, int internal)
{
    Auth::UserRequest::addReplyAuthHeader(rep, auth_user_request, request, accelerated, internal);
}