void
BasicUser::makeLoggingInstance(AuthBasicUserRequest *auth_user_request)
{
    if (username()) {
        /* log the username */
        debugs(29, 9, HERE << "Creating new user for logging '" << username() << "'");
        /* new scheme data */
        BasicUser *basic_auth = new BasicUser(& basicConfig);
        auth_user_request->user(basic_auth);
        /* save the credentials */
        basic_auth->username(username());
        username(NULL);
        /* set the auth_user type */
        basic_auth->auth_type = AUTH_BROKEN;
        /* link the request to the user */
        basic_auth->addRequest(auth_user_request);
    }
}