static Auth::UserRequest::Pointer
authTryGetUser(Auth::UserRequest::Pointer auth_user_request, ConnStateData * conn, HttpRequest * request)
{
    Auth::UserRequest::Pointer res;

    if (auth_user_request != NULL)
        res = auth_user_request;
    else if (request != NULL && request->auth_user_request != NULL)
        res = request->auth_user_request;
    else if (conn != NULL)
        res = conn->getAuth();

    // attach the credential notes from helper to the transaction
    if (request != NULL && res != NULL && res->user() != NULL) {
        // XXX: we have no access to the transaction / AccessLogEntry so cant SyncNotes().
        // workaround by using anything already set in HttpRequest
        // OR use new and rely on a later Sync copying these to AccessLogEntry

        UpdateRequestNotes(conn, *request, res->user()->notes);
    }

    return res;
}