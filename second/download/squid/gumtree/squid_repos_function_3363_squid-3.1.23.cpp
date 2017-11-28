void
clientReplyContext::ProcessReplyAccessResult (int rv, void *voidMe)
{
    clientReplyContext *me = static_cast<clientReplyContext *>(voidMe);
    me->processReplyAccessResult(rv);
}