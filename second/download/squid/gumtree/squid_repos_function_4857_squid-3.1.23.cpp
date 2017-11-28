int
AuthNegotiateUserRequest::module_direction()
{
    /* null auth_user is checked for by authenticateDirection */

    if (waiting || client_blob)
        return -1; /* need helper response to continue */

    switch (auth_state) {

        /* no progress at all. */

    case AUTHENTICATE_STATE_NONE:
        debugs(29, 1, "AuthNegotiateUserRequest::direction: called before Negotiate Authenticate for request " << this << "!. Report a bug to squid-dev.");
        return -2; /* error */

    case AUTHENTICATE_STATE_FAILED:
        return -2; /* error */


    case AUTHENTICATE_STATE_IN_PROGRESS:
        assert(server_blob);
        return 1; /* send to client */

    case AUTHENTICATE_STATE_DONE:
        return 0; /* do nothing */

    case AUTHENTICATE_STATE_INITIAL:
        debugs(29, 1, "AuthNegotiateUserRequest::direction: Unexpected AUTHENTICATE_STATE_INITIAL");
        return -2;
    }

    return -2;
}