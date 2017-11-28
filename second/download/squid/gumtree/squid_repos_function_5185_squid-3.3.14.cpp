static Auth::UserRequest::Pointer
authTryGetUser(Auth::UserRequest::Pointer auth_user_request, ConnStateData * conn, HttpRequest * request)
{
    if (auth_user_request != NULL)
        return auth_user_request;
    else if (request != NULL && request->auth_user_request != NULL)
        return request->auth_user_request;
    else if (conn != NULL)
        return conn->auth_user_request;
    else
        return NULL;
}