int
AuthBasicUserRequest::module_direction()
{
    /* null auth_user is checked for by authenticateDirection */
    basic_data *basic_auth = dynamic_cast<BasicUser *>(user());
    assert (basic_auth);

    switch (basic_auth->flags.credentials_ok) {

    case 0:			/* not checked */
        return -1;

    case 1:			/* checked & ok */

        if (basic_auth->credentials_checkedtime + basicConfig.credentialsTTL <= squid_curtime)
            return -1;

        return 0;

    case 2:			/* paused while waiting for a username:password check on another request */
        return -1;

    case 3:			/* authentication process failed. */
        return 0;
    }

    return -2;
}