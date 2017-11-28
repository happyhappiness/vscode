void
ConnStateData::notifyAllContexts(int xerrno)
{
    typedef ClientSocketContext::Pointer CSCP;
    for (CSCP c = getCurrentContext(); c.getRaw(); c = c->next)
        c->noteIoError(xerrno);
}