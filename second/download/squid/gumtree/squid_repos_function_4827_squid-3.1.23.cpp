static AuthUserRequest *
authTryGetUser (AuthUserRequest **auth_user_request, ConnStateData * conn, HttpRequest * request)
{
    if (*auth_user_request)
        return *auth_user_request;
    else if (request != NULL && request->auth_user_request)
        return request->auth_user_request;
    else if (conn != NULL)
        return conn->auth_user_request;
    else
        return NULL;
}