void
ConnStateData::addContextToQueue(ClientSocketContext * context)
{
    ClientSocketContext::Pointer *S;

    for (S = (ClientSocketContext::Pointer *) & currentobject; S->getRaw();
            S = &(*S)->next);
    *S = context;

    ++nrequests;
}