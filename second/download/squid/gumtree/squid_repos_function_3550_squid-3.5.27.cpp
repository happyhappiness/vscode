void
ClientSocketContext::removeFromConnectionList(ConnStateData * conn)
{
    ClientSocketContext::Pointer *tempContextPointer;
    assert(conn != NULL && cbdataReferenceValid(conn));
    assert(conn->getCurrentContext() != NULL);
    /* Unlink us from the connection request list */
    tempContextPointer = & conn->currentobject;

    while (tempContextPointer->getRaw()) {
        if (*tempContextPointer == this)
            break;

        tempContextPointer = &(*tempContextPointer)->next;
    }

    assert(tempContextPointer->getRaw() != NULL);
    *tempContextPointer = next;
    next = NULL;
}