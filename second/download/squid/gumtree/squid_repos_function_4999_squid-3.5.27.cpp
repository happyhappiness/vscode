void
Ftp::Server::resetLogin(const char *reason)
{
    debugs(33, 5, "will need to re-login due to " << reason);
    master->clientReadGreeting = false;
    changeState(fssBegin, reason);
}