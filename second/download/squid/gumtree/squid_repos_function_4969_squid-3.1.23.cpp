static AuthUserRequest *
authDigestLogUsername(char *username, AuthDigestUserRequest *auth_user_request)
{
    assert(auth_user_request != NULL);

    /* log the username */
    debugs(29, 9, "authDigestLogUsername: Creating new user for logging '" << username << "'");
    digest_user_h *digest_user = new DigestUser(&digestConfig);
    /* save the credentials */
    digest_user->username(username);
    /* set the auth_user type */
    digest_user->auth_type = AUTH_BROKEN;
    /* link the request to the user */
    auth_user_request->user(digest_user);
    digest_user->addRequest (auth_user_request);
    return auth_user_request;
}