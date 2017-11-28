void
AsyncCallQueue::fireNext()
{
    AsyncCall::Pointer call = theHead;
    theHead = call->theNext;
    call->theNext = NULL;
    if (theTail == call)
        theTail = NULL;

    debugs(call->debugSection, call->debugLevel, "entering " << *call);
    call->make();
    debugs(call->debugSection, call->debugLevel, "leaving " << *call);
}