void
clientReplyContext::sendNotModifiedOrPreconditionFailedError()
{
    if (http->request->method == METHOD_GET ||
            http->request->method == METHOD_HEAD)
        sendNotModified();
    else
        sendPreconditionFailedError();
}