void AsyncCallQueue::schedule(AsyncCall::Pointer &call)
{
    assert(call != NULL);
    assert(!call->theNext);
    if (theHead != NULL) { // append
        assert(!theTail->theNext);
        theTail->theNext = call;
        theTail = call;
    } else { // create queue from cratch
        theHead = theTail = call;
    }
}