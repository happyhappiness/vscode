void
Client::handleRequestBodyProductionEnded()
{
    receivedWholeRequestBody = true;
    if (!requestSender)
        doneSendingRequestBody();
    else
        debugs(9,3, HERE << "waiting for request body write to complete");
}