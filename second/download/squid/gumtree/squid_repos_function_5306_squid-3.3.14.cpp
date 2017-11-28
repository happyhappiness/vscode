static Auth::UserRequest::Pointer
authDigestLogUsername(char *username, Auth::UserRequest::Pointer auth_user_request)
{
    assert(auth_user_request != NULL);

    /* log the username */
    debugs(29, 9, "Creating new user for logging '" << (username?username:"[no username]") << "'");
    Auth::User::Pointer digest_user = new Auth::Digest::User(static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest")));
    /* save the credentials */
    digest_user->username(username);
    /* set the auth_user type */
    digest_user->auth_type = Auth::AUTH_BROKEN;
    /* link the request to the user */
    auth_user_request->user(digest_user);
    return auth_user_request;
}