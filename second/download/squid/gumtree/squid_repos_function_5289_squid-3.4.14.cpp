void
Auth::Negotiate::UserRequest::releaseAuthServer()
{
    if (authserver) {
        debugs(29, 6, HERE << "releasing Negotiate auth server '" << authserver << "'");
        helperStatefulReleaseServer(authserver);
        authserver = NULL;
    } else
        debugs(29, 6, HERE << "No Negotiate auth server to release.");
}