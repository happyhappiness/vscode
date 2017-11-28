void
Pipeline::popMe(const Http::StreamPointer &which)
{
    if (requests.empty())
        return;

    debugs(33, 3, "Pipeline " << (void*)this << " drop " << requests.front());
    // in reality there may be multiple contexts doing processing in parallel.
    // XXX: pipeline still assumes HTTP/1 FIFO semantics are obeyed.
    assert(which == requests.front());
    requests.pop_front();
}