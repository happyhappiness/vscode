void
AuthNegotiateUserRequest::onConnectionClose(ConnStateData *conn)
{
    assert(conn != NULL);

    debugs(29, 8, "AuthNegotiateUserRequest::onConnectionClose: closing connection '" << conn << "' (this is '" << this << "')");

    if (conn->auth_user_request == NULL) {
        debugs(29, 8, "AuthNegotiateUserRequest::onConnectionClose: no auth_user_request");
        return;
    }

    releaseAuthServer();

    /* unlock the connection based lock */
    debugs(29, 9, "AuthNegotiateUserRequest::onConnectionClose: Unlocking auth_user from the connection '" << conn << "'.");

    AUTHUSERREQUESTUNLOCK(conn->auth_user_request, "conn");
}