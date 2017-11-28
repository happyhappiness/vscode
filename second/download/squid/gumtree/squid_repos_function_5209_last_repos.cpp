void
Client::handleMoreRequestBodyAvailable()
{
    if (!requestSender)
        sendMoreRequestBody();
    else
        debugs(9,3, HERE << "waiting for request body write to complete");
}