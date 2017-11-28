void
clientReplyContext::sendNotModifiedOrPreconditionFailedError()
{
    if (http->request->method == Http::METHOD_GET ||
            http->request->method == Http::METHOD_HEAD)
        sendNotModified();
    else
        sendPreconditionFailedError();
}