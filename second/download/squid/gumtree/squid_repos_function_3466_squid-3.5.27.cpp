void
clientReplyContext::HandleIMSReply(void *data, StoreIOBuffer result)
{
    clientReplyContext *context = (clientReplyContext *)data;
    context->handleIMSReply(result);
}