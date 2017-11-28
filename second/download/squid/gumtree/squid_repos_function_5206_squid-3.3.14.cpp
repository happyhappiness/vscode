void
Auth::Negotiate::UserRequest::onConnectionClose(ConnStateData *conn)
{
    assert(conn != NULL);

    debugs(29, 8, HERE << "closing connection '" << conn << "' (this is '" << this << "')");

    if (conn->auth_user_request == NULL) {
        debugs(29, 8, HERE << "no auth_user_request");
        return;
    }

    releaseAuthServer();

    /* unlock the connection based lock */
    debugs(29, 9, HERE << "Unlocking auth_user from the connection '" << conn << "'.");

    conn->auth_user_request = NULL;
}