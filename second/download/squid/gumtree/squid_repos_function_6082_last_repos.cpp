void
AsyncCall::dequeue(AsyncCall::Pointer &head, AsyncCall::Pointer &prev)
{
    if (prev != NULL)
        prev->setNext(Next());
    else
        head = Next();
    setNext(NULL);
}