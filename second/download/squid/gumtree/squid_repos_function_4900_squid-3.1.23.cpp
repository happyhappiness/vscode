AuthUserRequest *
AuthBasicConfig::decode(char const *proxy_auth)
{
    AuthBasicUserRequest *auth_user_request = new AuthBasicUserRequest();
    /* decode the username */
    /* trim BASIC from string */

    while (xisgraph(*proxy_auth))
        proxy_auth++;

    BasicUser *basic_auth, local_basic(&basicConfig);

    /* Trim leading whitespace before decoding */
    while (xisspace(*proxy_auth))
        proxy_auth++;

    local_basic.decode(proxy_auth, auth_user_request);

    if (!local_basic.valid()) {
        local_basic.makeLoggingInstance(auth_user_request);
        return auth_user_request;
    }

    /* now lookup and see if we have a matching auth_user structure in
     * memory. */

    AuthUser *auth_user;

    if ((auth_user = authBasicAuthUserFindUsername(local_basic.username())) == NULL) {
        auth_user = local_basic.makeCachedFrom();
        basic_auth = dynamic_cast<BasicUser *>(auth_user);
        assert (basic_auth);
    } else {
        basic_auth = dynamic_cast<BasicUser *>(auth_user);
        assert (basic_auth);
        basic_auth->updateCached (&local_basic);
    }

    /* link the request to the in-cache user */
    auth_user_request->user(basic_auth);

    basic_auth->addRequest(auth_user_request);

    return auth_user_request;
}