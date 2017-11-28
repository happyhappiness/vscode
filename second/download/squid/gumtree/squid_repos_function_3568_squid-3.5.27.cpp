bool
ConnStateData::areAllContextsForThisConnection() const
{
    ClientSocketContext::Pointer context = getCurrentContext();

    while (context.getRaw()) {
        if (context->http->getConn() != this)
            return false;

        context = context->next;
    }

    return true;
}