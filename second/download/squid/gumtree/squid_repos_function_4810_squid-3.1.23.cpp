int
authenticateValidateUser(AuthUserRequest * auth_user_request)
{
    debugs(29, 9, "authenticateValidateUser: Validating Auth_user request '" << auth_user_request << "'.");

    if (auth_user_request == NULL) {
        debugs(29, 4, "authenticateValidateUser: Auth_user_request was NULL!");
        return 0;
    }

    if (auth_user_request->user() == NULL) {
        debugs(29, 4, "authenticateValidateUser: No associated auth_user structure");
        return 0;
    }

    if (auth_user_request->user()->auth_type == AUTH_UNKNOWN) {
        debugs(29, 4, "authenticateValidateUser: Auth_user '" << auth_user_request->user() << "' uses unknown scheme.");
        return 0;
    }

    if (auth_user_request->user()->auth_type == AUTH_BROKEN) {
        debugs(29, 4, "authenticateValidateUser: Auth_user '" << auth_user_request->user() << "' is broken for it's scheme.");
        return 0;
    }

    /* any other sanity checks that we need in the future */

    /* Thus should a module call to something like authValidate */

    /* finally return ok */
    debugs(29, 5, "authenticateValidateUser: Validated Auth_user request '" << auth_user_request << "'.");

    return 1;

}