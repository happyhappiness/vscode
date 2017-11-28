void
Ftp::Relay::handleControlReply()
{
    if (!request->clientConnectionManager.valid()) {
        debugs(9, 5, "client connection gone");
        closeServer();
        return;
    }

    Ftp::Client::handleControlReply();
    if (ctrl.message == NULL)
        return; // didn't get complete reply yet

    assert(state < END);
    assert(this->SM_FUNCS[state] != NULL);
    (this->*SM_FUNCS[state])();
}