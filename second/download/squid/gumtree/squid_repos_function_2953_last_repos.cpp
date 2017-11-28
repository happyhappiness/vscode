void
clientReplyContext::ProcessReplyAccessResult(allow_t rv, void *voidMe)
{
    clientReplyContext *me = static_cast<clientReplyContext *>(voidMe);
    me->processReplyAccessResult(rv);
}